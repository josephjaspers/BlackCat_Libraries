/*  Project: BlackCat_Tensors
 *  Author: JosephJaspers
 *  Copyright 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifdef __CUDACC__
#ifndef BC_MATHEMATICS_DEVICE_H_
#define BC_MATHEMATICS_DEVICE_H_

#include "../../../common.h"
#include <cuda_runtime_api.h>
#include <cuda.h>

#include "device_impl.cu"
#include <iostream>


namespace bc {

struct device_tag;

namespace tensors {
namespace exprs {
namespace evaluator {

template<class SystemTag>
struct Evaluator;

template<>
struct Evaluator<device_tag> {

		struct n1 {
		template<class Expression>
				static void eval(Expression expression, cudaStream_t stream) {
					gpu_impl::eval<<<calculate_block_dim(expression.size()),
							calculate_threads(), 0, stream>>>(expression);
				}
			};
		struct n2 {
			template<class Expression>
			static void eval(Expression expression, cudaStream_t stream) {
				dim3 grid(calculate_block_dim(expression.dim(0)),
							calculate_block_dim(expression.dim(1)));

				gpu_impl::eval2d<<<
						grid, calculate_threads(), 0, stream>>>(expression);
			}
		};
		struct n3 {
			template<class Expression>
			static void eval(Expression expression, cudaStream_t stream) {
				dim3 grid(
						calculate_block_dim(expression.dim(0)),
						calculate_block_dim(expression.dim(1)),
						calculate_block_dim(expression.dim(2)));

				gpu_impl::eval3d<<<
						grid, calculate_threads(), 0, stream>>>(expression);
			}
		};
		struct n4 {
			template<class Expression>
			static void eval(Expression expression, cudaStream_t stream) {
				dim3 grid(
						calculate_block_dim(expression.dim(0)),
						calculate_block_dim(expression.dim(1)),
						calculate_block_dim(expression.dim(2)));

				gpu_impl::eval4d<<<
						grid, calculate_threads(), 0, stream>>>(expression);
			}
		};
		struct n5 {
			template<class Expression>
			static void eval(Expression expression, cudaStream_t stream) {
				dim3 grid(
						calculate_block_dim(expression.dim(0)),
						calculate_block_dim(expression.dim(1)),
						calculate_block_dim(expression.dim(2)));

				gpu_impl::eval5d<<<
						grid, calculate_threads(), 0, stream>>>(expression);
			}
		};

	template<int Dimensions, class Expression, class Stream>
	static void nd_evaluate(Expression expression, Stream stream) {
		static_assert(
				Expression::tensor_dim <= Dimensions ||
				Expression::tensor_iterator_dim <= 1,
				"Iterator Dimension must be "
				"greater than or equal to the tensor_dim");

		using run =
				std::conditional_t<(Dimensions <= 1), n1,
				std::conditional_t<(Dimensions == 2), n2,
				std::conditional_t<(Dimensions == 3), n3,
				std::conditional_t<(Dimensions == 4), n4, n5>>>>;

		stream.enqueue([=]() {
			run::eval(expression, stream);
			BC_CUDA_ASSERT(cudaPeekAtLastError());
		});
	}

};

}
}
}
}

#endif /* MATHEMATICS_CPU_H_ */

#endif //if cudda cc defined
