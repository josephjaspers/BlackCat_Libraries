/*
 * FeedForward.cu
 *
 *  Created on: Jan 28, 2018
 *      Author: joseph
 */

#ifndef OUTPUT_CU
#define OUTPUT_CU

#include "Layer.cu"

namespace BC {

struct OutputLayer : Layer<OutputLayer> {

public:
	int INPUTS;
	vec hypothesis;

	OutputLayer(int inputs) : INPUTS(inputs), hypothesis(inputs) {
	}

	template<class T> vec forwardPropagation(const vec_expr<T>& in) {
		return hypothesis == in;
	}
	template<class T> vec forwardPropagation_Express(const vec_expr<T>& x) const {
		return x;
	}

	template<class T> vec backPropagation(const vec_expr<T>& y) {
		return hypothesis - y;
	}

	void updateWeights() {
		//empty
	}
	void clearBPStorage() {
		//empty
	}

	int getClass() {
		return LAYER_TYPE::Output_;
	}
	void write(std::ofstream& is) {
		is << INPUTS << ' ';
		hypothesis.write(is);

	}
	void read(std::ifstream& os) {
		os >> INPUTS;
		hypothesis.read(os);
	}

};
}



#endif /* FEEDFORWARD_CU_ */