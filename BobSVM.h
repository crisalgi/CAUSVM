/*
 * BobSVM.h
 *
 *  Created on: Jun 22, 2016
 *      Author: Cristian H. Alzate
 */

#ifndef BOBSVM_H_
#define BOBSVM_H_
#include <bob.learn.libsvm/machine.h>
#include <bob.learn.libsvm/trainer.h>
class BobSVM {
public:
	BobSVM();
	int process(double** input, unsigned int rows, unsigned int cols);
	int process(double* input, unsigned int cols);
	virtual ~BobSVM();
	double getConfidence() const;
	void setConfidence(double confidence);
	bool isAdaptive() const;
	void setAdaptive(bool adaptive);

private:
	bool adaptive;
	double confidence;
	unsigned int numClass;
	bob::learn::libsvm::Machine *SVMmachine;
	bob::learn::libsvm::Trainer *SVMtrainer;
	blitz::vector<blitz::Array<double, 2>> *input;
	float* max(float* input, int size);

	void toBlitzFormat(double* input, blitz::Array<double, 1>* output, unsigned int cols);
	void toBlitzFormat(double** input, blitz::Array<double, 2>* output, unsigned int rows, unsigned int cols);
	int calculateConfidence(blitz::vector<blitz::Array<double, 1>> input);
	void printBlitzArray(blitz::Array<double, 2> aux);
	void updateClass(blitz::Array<double, 2>* output, int cls);
	void updateClass(blitz::Array<double, 1>* output, int cls);
	void printData();

};

#endif /* BOBSVM_H_ */
