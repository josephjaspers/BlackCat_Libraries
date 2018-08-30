/*
 * Array_Row.h
 *
 *  Created on: Aug 27, 2018
 *      Author: joseph
 */

#ifndef ARRAY_ROW_H_
#define ARRAY_ROW_H_

#include "Array_Base.h"

namespace BC {
namespace internal {

template<class PARENT>
struct Array_Row : Tensor_Array_Base<Array_Row<PARENT>, 1> {

	using scalar_t = typename PARENT::scalar_t;
	using mathlib_t = typename PARENT::mathlib_t;

	static_assert(PARENT::DIMS() == 2, "A ROW VIEW MAY ONLY BE CONSTRUCTED FROM A MATRIX");

	__BCinline__ static constexpr int ITERATOR() { return MTF::max(PARENT::ITERATOR() - 1, 0); }
	__BCinline__ static constexpr int DIMS() { return MTF::max(PARENT::DIMS() - 1, 0); }

	__BCinline__ operator const PARENT() const	{ return parent; }

	const PARENT parent;
	scalar_t* array_slice;

	__BCinline__ Array_Row(const scalar_t* array, PARENT parent_) : array_slice(const_cast<scalar_t*>(array)), parent(parent_) {}

	__BCinline__ const auto inner_shape() const { return l_array<1>([&](int i) { return this->dimension(i); }); }
	__BCinline__ const auto outer_shape() const { return l_array<1>([&](int i) { return this->leading_dimension(i); }); }
	__BCinline__ int size() const { return parent.cols(); }
	__BCinline__ int rows() const { return size(); }
	__BCinline__ int cols() const { return  1; }
	__BCinline__ int dimension(int i) const { return i == 0 ? parent.cols() : 1; }
	__BCinline__ int outer_dimension() const { return 1; }
	__BCinline__ int leading_dimension(int i) const { return i == 0 ? parent.leading_dimension(1) : 0; }

	__BCinline__ const scalar_t* memptr() const { return array_slice; }
	__BCinline__	   scalar_t* memptr()   	{ return array_slice; }

};
}

}





#endif /* ARRAY_ROW_H_ */
