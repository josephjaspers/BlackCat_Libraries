/*
 * Tensor.h
 *
 *  Created on: Dec 30, 2017
 *      Author: joseph
 */

#ifndef BC_TENSOR_N5_H
#define BC_TENSOR_N5_H

#include "BC_Tensor_Base/TensorBase.h"

namespace BC {

template<class T, class Mathlib>
class Tensor5 : public TensorBase<Tensor5<T, Mathlib>> {

	using parent_class = TensorBase<Tensor5<T, Mathlib>>;

public:
	using scalar = T;
	using parent_class::operator=;
	using parent_class::operator[];
	using parent_class::operator();

	__BCinline__ static constexpr int DIMS() { return 5; }

	Tensor5(const Tensor5&  v) : parent_class(v) {}
	Tensor5(	  Tensor5&& v) : parent_class(v) {}
	Tensor5(const Tensor5&& v) : parent_class(v) {}
	explicit Tensor5(int a = 1,int b = 1,int c = 1, int d = 1, int e = 1) : parent_class(array(a,b,c,d,e)) {}

	template<class U> 		  Tensor5(const Tensor5<U, Mathlib>&  t) : parent_class(t) {}
	template<class U> 		  Tensor5(	    Tensor5<U, Mathlib>&& t) : parent_class(t) {}

	Tensor5& operator =(const Tensor5& t)  { return parent_class::operator=(t); }
	Tensor5& operator =(const Tensor5&& t) { return parent_class::operator=(t); }
	Tensor5& operator =(	  Tensor5&& t) { return parent_class::operator=(t); }
	template<class U>
	Tensor5& operator = (const Tensor5<U, Mathlib>& t) { return parent_class::operator=(t); }

private:

	template<class> friend class TensorBase;
	template<class> friend class Tensor_Operations;
	template<class... params> Tensor5(const params&... p) : parent_class(p...) {}

};

} //End Namespace BC

#endif /* MATRIX_H */
