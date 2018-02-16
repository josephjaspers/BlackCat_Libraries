
/*


 * NeuralNetwork.cu
 *
 *  Created on: Jan 28, 2018
 *      Author: joseph
 */

#ifndef NEURALNETWORKT_CU_
#define NEURALNETWORKT_CU_

#include "Layer.cu"
#include <tuple>
#include <iostream>
#include <fstream>
#include <cstdio>

#include "BlackCat_Tuple.cu"

namespace BC {

template<class... set>
using LayerSet = Tuple<set...>;


template<class... layers>
struct NeuralNetwork {
	static constexpr int length = sizeof...(layers);
	template<int a, int b> struct min { static constexpr int value = a < b ? a : b; };
	template<int a, int b> struct max { static constexpr int value = a > b ? a : b; };


	template<int> struct N;
	template<int a, int b>
	static constexpr bool same = std::is_same<N<a>, N<b>>();



	LayerSet<layers...> network;
	NeuralNetwork(layers... l) : network(l...) {}

	template<class T> vec forwardPropagation		(const vec_expr<T>& param) 	   { return fp  <0, length>(param, std::is_same<N<0>, N<length>>()); }
	template<class T> vec forwardPropagation_express(const vec_expr<T>& param) 	   { return fpx <0, length>(param, std::is_same<N<0>, N<length>>()); }
	template<class T> vec backPropagation			(const vec_expr<T>& param) 	   { return bp  <length, 0>(param, std::is_same<N<length>, N<0>>()); }
	template<class T> vec backPropagationThroughTime(const vec_expr<T>& param) 	   { return bptt<length, 0>(param, std::is_same<N<length>, N<0>>()); }


	void updateWeights()   { update<0, length>(); }
	void updateWeights(const NeuralNetwork& n)   { update<0, length>(n); }
	void fastCopy(const NeuralNetwork& nn) { fCopy<0, length>(nn); }

	void clearBPStorage()  { clearStoredGradients<0,length>(); }

	void write(std::ofstream& os) {
		writeLayers<0, length>(os);
	}
	void read(std::ifstream& is) {
		readLayers<0, length>(is);
	}


	//Tuple iterator
private:

	template<int start, int end, class T> auto fp  (const vec_expr<T>& param, std::false_type) {
		if (start != end)
			return fp  <min<start + 1, end>::value, end, T>(network.get<min<start, end -1>::value>().forwardPropagation(param),  std::is_same<N<start + 1>, N<end>>());

	}
	template<int start, int end, class T> auto fpx  (const vec_expr<T>& param, std::false_type) {
		if (start != end)
			return fpx  <min<start + 1, end>::value, end, T>(network.get<min<start, end -1>::value>().forwardPropagation_express(param),  std::is_same<N<start + 1>, N<end>>());
	}
	template<int start, int end, class T> auto bp  (const vec_expr<T>& param, std::false_type) {
		if (start > end)
			return bp  <max<start - 1, end>::value, end, T>(network.get<max<start - 1, end>::value>().backPropagation(param),  std::is_same<N<start - 1>, N<end>>());
	}
	template<int start, int end, class T> auto bptt  (const vec_expr<T>& param, std::false_type) {
		if (start > end)
			return bptt  <max<start - 1, end>::value, end, T>(network.get<max<start - 1, end>::value>().backPropagationThroughTime(param),  std::is_same<N<start - 1>, N<end>>());
	}
	template<int start, int end, class T> vec fp  (const vec_expr<T>& param, std::true_type) {
		return param;
	}
	template<int start, int end, class T> vec fpx  (const vec_expr<T>& param, std::true_type) {
		return param;
	}
	template<int start, int end, class T> vec bp  (const vec_expr<T>& param, std::true_type) {
		return param;
	}
	template<int start, int end, class T> vec bptt  (const vec_expr<T>& param, std::true_type) {
		return param;
	}




	template<int start, int end> void update  () {
		if (start != end) {
			network.get<min<start, end -1>::value>().updateWeights();
			update<min<start + 1, end>::value, end>();
		}
	}
	//for multithreading
	template<int start, int end> void update  (const NeuralNetwork& cpy_net) {
		if (start != end) {
			network.get<min<start, end -1>::value>().updateWeights(cpy_net.network.get<min<start, end -1>::value>());
			update<min<start + 1, end>::value, end>();
		}
	}
	template<int start, int end> void clearStoredGradients  () {

		if (start != end) {
			network.get<min<start, end -1>::value>().clearBPStorage();
			clearStoredGradients<min<start + 1, end>::value, end>();
		}
	}

	template<int start, int end> void writeLayers(std::ofstream& os) {

		if (start != end) {
			writeLayers<min<start + 1, end>::value, end>(os);
			network.get<min<start, end -1>::value>().write(os);
		}
	}
	template<int start, int end> void readLayers(std::ifstream& is) {

		if (start != end) {
			readLayers<min<start + 1, end>::value, end>(is);
			network.get<min<start, end -1>::value>().read(is);
		}
	}	template<int start, int end> void fCopy(const NeuralNetwork& nn) {

		if (start != end) {
			network.get<min<start, end -1>::value>().fastCopy(nn.network.get<min<start, end -1>::value>());
		}
	}
};

template<class... layers>
static NeuralNetwork<layers&...> generateNetwork(layers&... l) {
	return NeuralNetwork<layers&...>(l...);
}
template<class... layers>
static NeuralNetwork<layers&...> generateNetworkRef(layers&... l) {
	return NeuralNetwork<layers&...>(l...);
}
template<class... layers>
static NeuralNetwork<layers...> generateNetworkCopy(layers... l) {
	return NeuralNetwork<layers...>(l...);
}
}

#endif /* NEURALNETWORK_CU_ */