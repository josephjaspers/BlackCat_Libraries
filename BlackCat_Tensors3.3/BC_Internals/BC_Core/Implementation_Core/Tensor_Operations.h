/*
 * Tensor_Core.h
 *
 *  Created on: Dec 30, 2017
 *      Author: joseph
 */

#ifndef TENSOR_CORE_H_
#define TENSOR_CORE_H_

#include "Tensor_Operations_impl.h"

namespace BC {

template<class scalar, class functor, class evaluation, class math_lib>
struct _TRAITS {
		using scalar_type 		= scalar;
		using functor_type 		= functor;
		using evaluation_type 	= evaluation;
		using math_library 		= math_lib;
};

	template <class T, class functor, class derived, class mathlibrary>
	struct Tensor_Operations
			:
			  public Tensor_Operations_impl<
			  derived,
			  _TRAITS<
			  	  typename MTF::determine_scalar<T>::type,
			  	  functor,
			  	  typename MTF::determine_evaluation<derived>::type,
			  	  mathlibrary>> {


			using parent_class = Tensor_Operations_impl<
					  derived,

					  _TRAITS<
					  	  typename MTF::determine_scalar<T>::type,
					  	  functor,
					  	  typename MTF::determine_evaluation<derived>::type,
					  	  mathlibrary>>;

			using functor_type = typename parent_class::functor_type;
			using parent_class::operator=;

	};

}



#endif /* TENSOR_CORE_H_ */