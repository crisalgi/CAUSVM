/*
 * BobSVM.cpp
 *
 *  Created on: Jun 22, 2016
 *      Author: Cristian H. Alzate
 */

#include "BobSVM.h"

BobSVM::BobSVM() {
	adaptive = false;
	confidence = 0.65;
	numClass = 0;
	SVMtrainer = new bob::learn::libsvm::Trainer;
	SVMmachine = NULL;
	input = new blitz::vector<blitz::Array<double, 2>>();
}

BobSVM::~BobSVM() {

	delete SVMmachine;
	delete SVMtrainer;
	input->clear();
	delete input;
}

int BobSVM::process(double** input, unsigned int rows, unsigned int cols) {
	blitz::Array<double, 2> *data = new blitz::Array<double, 2>(rows, cols);
	toBlitzFormat(input, data, rows, cols);
	if (numClass < 2) {
		SVMtrainer->setMachineType(bob::learn::libsvm::ONE_CLASS);
		if (SVMmachine != NULL) {
			int output = 0;
			blitz::Array<double, 1> b(cols);
			for (unsigned int j = 0; j < rows; ++j) {
				b = (*data)(j, blitz::Range(0, cols));
				int temp = SVMmachine->predictClass(b);
				if (temp == 1)
					output++;
			}

			double acc = (double) output / (double) rows;
			if (acc >= confidence) {
				if (adaptive)
					updateClass(data, 1);
				delete data;
				return 1;
			} else {
				SVMtrainer->setMachineType(bob::learn::libsvm::C_SVC);
				SVMtrainer->setProbabilityEstimates(true);
			}
		}
	} else {
		blitz::Array<double, 1> b(cols);
		int aux = 1;
		if (numClass > 2)
			aux = numClass;

		SVMtrainer->setProbabilityEstimates(true);

		blitz::vector<blitz::Array<double, 1>> predictions;
		for (unsigned int j = 0; j < rows; ++j) {
			b = (*data)(j, blitz::Range(0, blitz::toEnd));
			blitz::Array<double, 1> prob(aux);

			SVMmachine->predictClassAndProbabilities(b, prob);
			for (int p = 0; p < numClass; ++p) {
				printf("p[%d] = %f \n", p, prob(p));
			}
			predictions.push_back(prob);
		}
		int output = calculateConfidence(predictions);

		predictions.clear();
		if (output != 0) {
			if (adaptive)
				updateClass(data, output);
			delete data;
			return output;
		}
	}

	//adding a new class in the model
	printf("Adding the class to the model\n");
	(this->input)->push_back(*data);

	if (SVMmachine != NULL) {
		delete SVMmachine;
		SVMmachine = NULL;
	}

	SVMmachine = SVMtrainer->train(*(this->input));
	numClass++;
	delete data;
	return numClass;
}

void BobSVM::toBlitzFormat(double* input, blitz::Array<double, 1>* output, unsigned int cols) {
	for (unsigned int j = 0; j < cols; ++j) {
		(*output)(j) = input[j];
	}
}

int BobSVM::process(double* input, unsigned int cols) {
	if (SVMmachine == NULL) {
		printf("no model\n");
		return -1;
	}
	blitz::Array<double, 1> *data = new blitz::Array<double, 1>(cols);
	int output = SVMmachine->predictClass(*data);
	delete data;
	return output;
}

double BobSVM::getConfidence() const {
	return confidence;
}

void BobSVM::setConfidence(double confidence) {
	this->confidence = confidence;
}

void BobSVM::toBlitzFormat(double** input, blitz::Array<double, 2>* output, unsigned int rows, unsigned int cols) {
	for (unsigned int i = 0; i < rows; ++i) {
		for (unsigned int j = 0; j < cols; ++j) {
			(*output)((int) i, (int) j) = input[i][j];
		}
	}
}

int BobSVM::calculateConfidence(blitz::vector<blitz::Array<double, 1>> inputVec) {
	int output = 0;

	float* probs = new float[numClass];
	for (int j = 0; j < numClass; ++j) {
		probs[j] = 0;
	}

	for (int i = 0; i < inputVec.size(); ++i) {
		auto aux = inputVec.at(i);
		for (int j = 0; j < numClass; ++j) {
			probs[j] = probs[j] + aux(j);
		}
	}

	float *acc = max(probs, numClass);
	if (acc[0] / numClass >= confidence)
		output = acc[1] + 1;

	delete[] probs;
	delete[] acc;

	return output;
}

void BobSVM::printData() {
	for (unsigned int i = 0; i < input->size(); ++i) {
		auto aux = input->at(i);
		for (int j = 0; j < aux.rows(); ++j) {
			for (int z = 0; z < aux.cols(); ++z) {
				printf("input[%d] = data[%d][%d] = %f\n", i, j, z, aux(j, z));
			}
		}
	}
}

bool BobSVM::isAdaptive() const {
	return adaptive;
}

void BobSVM::setAdaptive(bool adaptive) {
	this->adaptive = adaptive;
}

void BobSVM::printBlitzArray(blitz::Array<double, 2> aux) {
	for (int j = 0; j < aux.rows(); ++j) {
		for (int z = 0; z < aux.cols(); ++z) {
			printf("data[%d][%d] = %f\n", j, z, aux(j, z));
		}
	}
}

void BobSVM::updateClass(blitz::Array<double, 2>* inputClass, int cls) {
	auto aux = input->at(cls - 1);
	blitz::Array<double, 2> newData(aux.rows() + inputClass->rows(), aux.cols());
	for (int i = 0; i < aux.rows(); ++i) {
		for (int j = 0; j < aux.cols(); ++j) {
			newData(i, j) = aux(i, j);
		}
	}

	for (int i = 0; i < inputClass->rows(); ++i) {
		for (int j = 0; j < inputClass->cols(); ++j) {
			newData(i + aux.rows(), j) = (*inputClass)(i, j);
		}
	}

	//updating input
	blitz::vector<blitz::Array<double, 2>> *input2 = new blitz::vector<blitz::Array<double, 2>>();
	for (int i = 0; i < input->size(); ++i) {
		if (i == (cls - 1)) {
			input2->push_back(newData);
		} else {
			input2->push_back(input->at(i));
		}
	}

	input->clear();
	delete input;
	input = input2;
}

void BobSVM::updateClass(blitz::Array<double, 1>* inputClass, int cls) {
	auto aux = input->at(cls - 1);
	blitz::Array<double, 2> newData(aux.rows() + inputClass->rows(), aux.cols());
	for (int i = 0; i < aux.rows(); ++i) {
		for (int j = 0; j < aux.cols(); ++j) {
			newData(i, j) = aux(i, j);
		}
	}

	for (int j = 0; j < inputClass->cols(); ++j) {
		newData(aux.rows(), j) = (*inputClass)(j);
	}

	//updating input
	blitz::vector<blitz::Array<double, 2>> *input2 = new blitz::vector<blitz::Array<double, 2>>();
	for (int i = 0; i < input->size(); ++i) {
		if (i == (cls - 1)) {
			input2->push_back(newData);
		} else {
			input2->push_back(input->at(i));
		}
	}

	input->clear();
	delete input;
	input = input2;
}

float* BobSVM::max(float* input, int size) {
	float* output = new float[2];
	output[0] = 0;
	output[1] = 0;
	float max = std::numeric_limits<float>::min();
	for (int i = 0; i < size; i++) {
		if (input[i] > max) {
			max = input[i];
			output[0] = max;
			output[1] = i;
		}
	}
	return output;
}
