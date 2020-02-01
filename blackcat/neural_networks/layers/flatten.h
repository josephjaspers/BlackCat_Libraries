/*
 * Flatten.cu
 *
 *  Created on: Jan 28, 2018
 *	  Author: joseph
 */

#ifndef BLACKCATTENSORS_NEURALNETWORKS_LAYERS_FLATTEN_H_
#define BLACKCATTENSORS_NEURALNETWORKS_LAYERS_FLATTEN_H_

#include "layer_base.h"

namespace bc {
namespace nn {

template<
	class SystemTag,
	class ValueType,
	class InputTensorDimension=bc::traits::Integer<3>>
struct Flatten:
		public Layer_Base<
				Flatten<SystemTag, ValueType, InputTensorDimension>> {

	using system_tag = SystemTag;
	using value_type = ValueType;
	using allocator_type = nn_default_allocator_type<SystemTag, ValueType>;
	using self_type = Flatten<SystemTag, ValueType, InputTensorDimension>;
	using parent_type = Layer_Base<self_type>;

	using greedy_evaluate_delta = std::true_type;
	using input_tensor_dim = InputTensorDimension;
	using output_tensor_dim = bc::traits::Integer<1>;
	using defines_single_predict = std::true_type;

private:

	Dim<input_tensor_dim::value> m_input_shape;

public:

	Flatten(bc::Dim<input_tensor_dim::value> input_shape):
		parent_type(__func__, input_shape.size(), input_shape.size()),
		m_input_shape(input_shape) {}

	template<class Matrix>
	auto forward_propagation(const Matrix& x) {
		return x.reshaped(this->get_batched_output_shape());
	}

	template<class Vector>
	auto single_predict(const Vector& x) {
		return x.flattened();
	}

	template<class X, class Delta>
	auto back_propagation(const X& x, const Delta& dy) {
		return dy.reshaped(this->get_batched_input_shape());
	}

	auto get_input_shape() const { return m_input_shape; }
};

#ifndef BC_CLING_JIT
template<class ValueType, class SystemTag, int X>
auto flatten(SystemTag system_tag, Dim<X> shape) {
	return Flatten<SystemTag, ValueType, bc::traits::Integer<X>>(shape);
}
#endif

template<class SystemTag, int X>
auto flatten(SystemTag system_tag, Dim<X> shape) {
	return Flatten<
			SystemTag,
			typename SystemTag::default_floating_point_type,
			bc::traits::Integer<X>>(shape);
}

template<int X>
auto flatten(Dim<X> shape) {
	return Flatten<BLACKCAT_DEFAULT_SYSTEM_T,
			typename BLACKCAT_DEFAULT_SYSTEM_T::default_floating_point_type,
			bc::traits::Integer<X>>(shape);
}


}
}

#endif /* FEEDFORWARD_CU_ */