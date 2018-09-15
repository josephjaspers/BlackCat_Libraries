/*
 * Tensor_Aliases.h
 *
 *  Created on: Aug 7, 2018
 *      Author: joseph
 */

#ifndef TENSOR_ALIASES_H_
#define TENSOR_ALIASES_H_

#include "Tensor_Base.h"
#include <type_traits>

namespace BC {

#ifndef BC_GPU_DEFAULT
class CPU;
using alloc_t = CPU;
#else
class GPU;
using alloc_t = GPU;
#endif


template<int dimension, class scalar_t, class mathlib_t=alloc_t>
using Tensor = Tensor_Base<internal::Array<dimension, scalar_t, mathlib_t>>;

template<class scalar_t, class mathlib_t = alloc_t> using Scalar = Tensor<0, scalar_t, mathlib_t>;
template<class scalar_t, class mathlib_t = alloc_t> using Vector = Tensor<1, scalar_t, mathlib_t>;
template<class scalar_t, class mathlib_t = alloc_t> using Matrix = Tensor<2, scalar_t, mathlib_t>;
template<class scalar_t, class mathlib_t = alloc_t> using Cube   = Tensor<3, scalar_t, mathlib_t>;

template<int dimension, class scalar_t, class mathlib_t=alloc_t>
using Tensor_View = Tensor_Base<internal::Array_View<dimension, scalar_t, mathlib_t>>;

template<class scalar_t, class mathlib_t = alloc_t> using Scalar_View = Tensor_View<0, scalar_t, mathlib_t>;
template<class scalar_t, class mathlib_t = alloc_t> using Vector_View = Tensor_View<1, scalar_t, mathlib_t>;
template<class scalar_t, class mathlib_t = alloc_t> using Matrix_View = Tensor_View<2, scalar_t, mathlib_t>;
template<class scalar_t, class mathlib_t = alloc_t> using Cube_View   = Tensor_View<3, scalar_t, mathlib_t>;

namespace expr {
template<int x, class iterator_t, typename = std::enable_if_t<iterator_t::DIMS() == x>>
using tensor = Tensor_Base<iterator_t>;

template<class iterator_t> using scal = tensor<0, iterator_t>;
template<class iterator_t> using vec  = tensor<1, iterator_t>;
template<class iterator_t> using mat  = tensor<2, iterator_t>;
template<class iterator_t> using cube  = tensor<3, iterator_t>;
}

}



#endif /* TENSOR_ALIASES_H_ */
