///*  Project: BlackCat_Tensors
// *  Author: JosephJaspers
// *  Copyright 2018
// *
// * This Source Code Form is subject to the terms of the Mozilla Public
// * License, v. 2.0. If a copy of the MPL was not distributed with this
// * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
//
//#ifndef TENSOR_CHUNK_H_
//#define TENSOR_CHUNK_H_
//
//#include "Array_Base.h"
//
//namespace BC {
//namespace et {
//
//template<int dimension>
//struct Array_Chunk  {
//
//    template<class PARENT>
//    struct implementation : Array_Base<implementation<PARENT>,dimension>, Shape<dimension> {
//
//        static_assert(PARENT::ITERATOR == 0 || dimension <= PARENT::DIMS, "TENSOR-CHUNK'S DIMENSIONS MUST BE LESS OR EQUAL TO PARENT'S DIMENSIONS");
//        using value_type = typename PARENT::value_type;
//        using allocator_t = typename PARENT::allocator_t;
//        using system_tag = typename PARENT::system_tag;
//
//        __BCinline__ static constexpr BC::size_t  DIMS     { return dimension; };
//        __BCinline__ static constexpr BC::size_t  ITERATOR { return dimension; }
//
//        operator const PARENT() const    { return parent; }
//
//        PARENT parent;
//        value_type* array;
//
//        template<class... integers> __BCinline__
//        implementation(PARENT parent, BC::array<PARENT::DIMS, int> index, BC::array<dimension, int> shape)
//        :  Shape<dimension>(shape),
//           parent(parent),
//           array(const_cast<value_type*>(& parent(index))) {}
//
//        __BCinline__ const auto block_shape() const     { return Shape<dimension>::outer_shape(); }
//        __BCinline__ const auto outer_shape() const     { return parent.outer_shape(); }
//        __BCinline__ BC::size_t  leading_dimension(int i) const { return DIMS == 0 ? 1 : parent.leading_dimension(i); }
//
//        __BCinline__ const auto memptr() const { return array; }
//        __BCinline__       auto memptr()       { return array; }
//    };
//};
//
//template<class internal_t, BC::size_t  parent_dims, BC::size_t  dims>
//auto make_chunk(internal_t internal, BC::array<parent_dims, int> index, BC::array<dims, int> shape) {
//    return typename Array_Chunk<dims>::template implementation<internal_t>(internal, index, shape);
//}
//
//}
//}
//
//#endif /* TENSOR_RESHAPE_H_ */