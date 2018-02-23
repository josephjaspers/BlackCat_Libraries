/*
 * Defaults.h
 *
 *  Created on: Feb 22, 2018
 *      Author: joseph
 */

#ifndef DEFAULTS_H_
#define DEFAULTS_H_

#include "BlackCat_Tensors.h"
#include "BlackCat_TensorFunctions.cu"
namespace BC {

using namespace NN_Abreviated_Functions;
struct BASE;

#ifndef BC_USE_GPU ////NOT READY YET
using ml = CPU;
using fp_type = double;
#else
using ml = GPU;
using fp_type = float;
#endif

using vec = Vector<fp_type>;
using mat = Matrix<fp_type>;

template<class T, class ML = ml> using mat_expr = Matrix<T, ML>;
template<class T, class ML = ml> using vec_expr = Vector<T, ML>;

}

#endif /* DEFAULTS_H_ */
