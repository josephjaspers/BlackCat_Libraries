/*
 * Tensor_Core_Essentials.cu
 *
 *  Created on: Feb 19, 2018
 *      Author: joseph
 */

#ifndef TENSOR_CORE_ESSENTIALS_CU_
#define TENSOR_CORE_ESSENTIALS_CU_

#define __BC_gcpu__ __host__ __device__

#include "../../../BC_MetaTemplateFunctions/Adhoc.h"
#include "../../../BC_Expressions/BlackCat_Internal_Definitions.h"
#include <iostream>

namespace BC
{

using MTF::prim; //isPrimitive
using MTF::ifte; //if then else

template<int inner_rank_, int outer_rank_ = inner_rank_, class voider = void>
struct Rank {
	static constexpr int inner_rank = inner_rank_;
	static constexpr int outer_rank = outer_rank_;
};

template<class T, class Mathlib, class ranker> struct Tensor_Core;


}



#endif /* TENSOR_CORE_ESSENTIALS_CU_ */