/*
 * Main.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: Cristian H. Alzate
 */

#include <libsvm/svm.h>
#include <stdio.h>
#include"UnsupervisedSVM.h"
#include "BobSVM.h"

int main(int argc, char* argv[]) {

	BobSVM *svms = new BobSVM();
	//svms->setAdaptive(true);
	unsigned int rows = 3;
	unsigned int cols = 3;

	double** oneClass = new double*[3];
	for (unsigned int i = 0; i < 3; ++i) {
		oneClass[i] = new double[cols];
	}
	oneClass[0][0] = 1;
	oneClass[0][1] = -1;
	oneClass[0][2] = 1;

	oneClass[1][0] = 0.5;
	oneClass[1][1] = -0.5;
	oneClass[1][2] = 0.5;

	oneClass[2][0] = 0.75;
	oneClass[2][1] = -0.75;
	oneClass[2][2] = 0.8;
	printf("*************************\n");
	printf("Output : %d \n", svms->process(oneClass, 2, cols));

	oneClass[0][0] = 1;
	oneClass[0][1] = -1;
	oneClass[0][2] = 0.9;

	oneClass[1][0] = 0.5;
	oneClass[1][1] = -0.4;
	oneClass[1][2] = 0.4;

	oneClass[2][0] = 0.76;
	oneClass[2][1] = -0.8;
	oneClass[2][2] = 0.8;

	printf("*************************\n");
	printf("Output : %d \n", svms->process(oneClass, rows, cols));

	oneClass[0][0] = -1;
	oneClass[0][1] = 1;
	oneClass[0][2] = -0.75;

	oneClass[1][0] = -0.25;
	oneClass[1][1] = 0.5;
	oneClass[1][2] = -0.8;

	printf("*************************\n");
	printf("Output : %d \n", svms->process(oneClass, 2, cols));

	//	printf("Output : %d \n", svms->process(oneClass, 2, cols));

	oneClass[0][0] = 1.1;
	oneClass[0][1] = -1.2;
	oneClass[0][2] = 0.75;

	oneClass[1][0] = 0.6;
	oneClass[1][1] = -0.8;
	oneClass[1][2] = 0.8;

	printf("*************************\n");
	printf("Output : %d \n", svms->process(oneClass, 2, cols));
	printf("*************************\n");
	oneClass[0][0] = -1.1;
	oneClass[0][1] = 1.2;
	oneClass[0][2] = -0.75;

	oneClass[1][0] = -0.6;
	oneClass[1][1] = 0.8;
	oneClass[1][2] = -0.8;

	printf("Output : %d \n", svms->process(oneClass, 2, cols));
	printf("*************************\n");
	oneClass[0][0] = 5;
	oneClass[0][1] = 5;
	oneClass[0][2] = 5;

	oneClass[1][0] = 7;
	oneClass[1][1] = 8;
	oneClass[1][2] = 7;

	printf("Output : %d \n", svms->process(oneClass, 2, cols));
	printf("*************************\n");

	oneClass[0][0] = 4.5;
	oneClass[0][1] = 5.2;
	oneClass[0][2] = 4.7;

	oneClass[1][0] = 6.5;
	oneClass[1][1] = 8.2;
	oneClass[1][2] = 6.5;

	printf("Output : %d \n", svms->process(oneClass, 2, cols));
	printf("*************************\n");

	delete svms;
	for (unsigned int i = 0; i < rows; ++i) {
		delete[] oneClass[i];
	}
	delete[] oneClass;
	printf("good bye!\n");

	// with initialization
	//	double* gamma = new double[3];
	//		gamma[0] = 0.005; //min
	//		gamma[1] = 0.01; //steps
	//		gamma[2] = 0.2; //max

	//	double* gamma = new double[3];
	//	gamma[0] = 0.01; //min
	//	gamma[1] = 0.01; //steps
	//	gamma[2] = 0.05; //max
	//
	//	svm->setGammaRange(gamma);
	//
	//	double* nuRange = new double[3];
	//	nuRange[0] = 0.01; //min
	//	nuRange[1] = 0.01; //steps
	//	nuRange[2] = 0.5; //max
	//	svm->setNuRange(nuRange);

	//	double* test = new double[cols];
	//	test[0] = 0.8;
	//	test[1] = -0.8;
	//	test[2] = 0.9;

	//	printf("*************************\n");
	//	svm->processWithProbability(input[0], cols);
	//	printf("*************************\n");
	//	svm->processWithProbability(test, cols);
	//	printf("*************************\n");
	//	svm->processWithProbability(input[0], cols);
	//	printf("*************************\n");
	//
	//	svm->processWithProbability(input[1], cols);
	//	printf("*************************\n");
	//	svm->processWithProbability(input[2], cols);
	//	printf("*************************\n");
	//	svm->processWithProbability(input[3], cols);
	//	printf("*************************\n");
	//	svm->processWithProbability(input[3], cols);
	//	printf("*************************\n");
	//	svm->processWithProbability(input[4], cols);
	//	printf("*************************\n");
	//	svm->processWithProbability(input[5], cols);
	//	printf("*************************\n");
	//	svm->processWithProbability(input[6], cols);
	//	printf("*************************\n");
	//
	//	test[0] = 1;
	//	test[1] = -1;
	//	test[2] = 1;
	//
	//	svm->processWithProbability(test, cols);
	//
	//	//	test[0] = 100;
	//	//	test[1] = 100;
	//	//	test[2] = 100;
	//	//	svm->processWithProbability(test, cols);
	//
	//	delete[] labels;
	//
	//	for (unsigned int i = 0; i < row; ++i) {
	//		delete[] input[i];
	//	}
	//	delete[] input;
	//	delete[] test;
	//	delete svm;

	/*
	 unsigned int row = 7;
	 unsigned int cols = 3;

	 double** oneClass = new double*[2];
	 for (unsigned int i = 0; i < 2; ++i) {
	 oneClass[i] = new double[cols];
	 }
	 oneClass[0][0] = 1;
	 oneClass[0][1] = -1;
	 oneClass[0][2] = 1;

	 oneClass[1][0] = 0.5;
	 oneClass[1][1] = -0.5;
	 oneClass[1][2] = 0.5;
	 //
	 //	oneClass[2][0] = 0.75;
	 //	oneClass[2][1] = -0.75;
	 //	oneClass[2][2] = 0.8;

	 //	UnsupervisedSVM* svm = new UnsupervisedSVM();
	 svms->process(oneClass, 2, cols);

	 double** input = new double*[row];
	 for (unsigned int i = 0; i < row; ++i) {
	 input[i] = new double[cols];
	 }

	 input[0][0] = 1;
	 input[0][1] = -1;
	 input[0][2] = 1;

	 input[1][0] = 0.5;
	 input[1][1] = -0.5;
	 input[1][2] = 0.5;

	 input[2][0] = 0.75;
	 input[2][1] = -0.75;
	 input[2][2] = 0.8;

	 input[3][0] = -1;
	 input[3][1] = 1;
	 input[3][2] = -0.75;

	 input[4][0] = -0.25;
	 input[4][1] = 0.5;
	 input[4][2] = -0.8;

	 input[5][0] = 5;
	 input[5][1] = 5;
	 input[5][2] = 5;

	 input[6][0] = 5.5;
	 input[6][1] = 5.2;
	 input[6][2] = 5.1;

	 double* labels = new double[row];
	 labels[0] = 1;
	 labels[1] = 1;
	 labels[2] = 1;
	 labels[3] = 2;
	 labels[4] = 2;
	 labels[5] = 3;
	 labels[6] = 3;

	 //svm->initialize(labels, input, cols, 5, 3);
	 svm->initialize(labels, oneClass, cols, 2, 1);

	 // with initialization
	 //	double* gamma = new double[3];
	 //		gamma[0] = 0.005; //min
	 //		gamma[1] = 0.01; //steps
	 //		gamma[2] = 0.2; //max

	 //	double* gamma = new double[3];
	 //	gamma[0] = 0.01; //min
	 //	gamma[1] = 0.01; //steps
	 //	gamma[2] = 0.05; //max
	 //
	 //	svm->setGammaRange(gamma);
	 //
	 //	double* nuRange = new double[3];
	 //	nuRange[0] = 0.01; //min
	 //	nuRange[1] = 0.01; //steps
	 //	nuRange[2] = 0.5; //max
	 //	svm->setNuRange(nuRange);

	 double* test = new double[cols];
	 test[0] = 0.8;
	 test[1] = -0.8;
	 test[2] = 0.9;

	 printf("*************************\n");
	 svm->processWithProbability(input[0], cols);
	 printf("*************************\n");
	 svm->processWithProbability(test, cols);
	 printf("*************************\n");
	 svm->processWithProbability(input[0], cols);
	 printf("*************************\n");

	 svm->processWithProbability(input[1], cols);
	 printf("*************************\n");
	 svm->processWithProbability(input[2], cols);
	 printf("*************************\n");
	 svm->processWithProbability(input[3], cols);
	 printf("*************************\n");
	 svm->processWithProbability(input[3], cols);
	 printf("*************************\n");
	 svm->processWithProbability(input[4], cols);
	 printf("*************************\n");
	 svm->processWithProbability(input[5], cols);
	 printf("*************************\n");
	 svm->processWithProbability(input[6], cols);
	 printf("*************************\n");

	 test[0] = 1;
	 test[1] = -1;
	 test[2] = 1;

	 svm->processWithProbability(test, cols);

	 //	test[0] = 100;
	 //	test[1] = 100;
	 //	test[2] = 100;
	 //	svm->processWithProbability(test, cols);

	 delete[] labels;

	 for (unsigned int i = 0; i < row; ++i) {
	 delete[] input[i];
	 }
	 delete[] input;
	 delete[] test;
	 delete svm;
	 printf("good bye!\n");
	 */
}

