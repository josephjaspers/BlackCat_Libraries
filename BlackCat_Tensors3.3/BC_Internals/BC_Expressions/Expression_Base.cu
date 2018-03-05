/*

 * BC_Expression_Base.h
 *
 *  Created on: Dec 11, 2017
 *      Author: joseph
 */

#ifdef  __CUDACC__
#ifndef EXPRESSION_BASE_H_
#define EXPRESSION_BASE_H_

#include "BlackCat_Internal_Definitions.h"
#include "../BC_Core/Implementation_Core/Determiners.h"
#include <iostream>

namespace BC {

template<class T, class derived>
struct expression {
	using type = derived;
	using scalar_type = T;
private:

	template<class ret = int>
	static ret shadowFailure(std::string method) {
		std::cout << "SHADOW METHOD FAILURE OF REQUIRED METHOD - ENLIGHTENED METHOD: " << method << " -- OVERRIDE THIS METHOD" << std::endl;
		throw std::invalid_argument("MANDATORY METHOD - NOT SHADOWED POTENTIAL INCORRECT CAST BUG");
	}
		  derived& asDerived() 		 { return static_cast<	    derived&>(*this); }
	const derived& asDerived() const { return static_cast<const derived&>(*this); }

public:
//	expression() { static_assert(std::is_trivially_copyable<derived>::value, "DERIVATIVES OF EXPRESSION TYPES MUST BE TRIVIALLY COPYABLE"); }


	int rank() const 	{ return shadowFailure<int>("int rank() const"); }
	int size() const 	{ return shadowFailure<int>("int size() const"); }
	int rows() const 	{ return shadowFailure<int>("int rows() const"); }
	int cols() const 	{ return shadowFailure<int>("int cols() const"); }
	int LD_rows() const { return shadowFailure<int>("int LD_rows() const"); }
	int LD_cols() const { return shadowFailure<int>("int LD_cols() const");}
	int dimension(int i)		const { return shadowFailure<int>("int dimension(int) const"); }
	void printDimensions() 		const { shadowFailure<>("void printDimensions() const"); }
	void printLDDimensions() 	const { shadowFailure<>("void printLDDimensions() const"); }
	const int* innerShape() const 			{ return shadowFailure<int*>("auto(const int*) innerShape() const  MAY RETURN INT*, _sh<T>, or std::vector<int>, "); }
	const int* outerShape() const 			{ return shadowFailure<int*>("auto(const int*) outerShape() const  MAY RETURN INT*, _sh<T>, or std::vector<int>, "); }
	int slice(int i) const { return shadowFailure<>("const Tensor_Slice(int) const  => THIS METHOD SHOULD ONLY BE ENABLED FOR TENSOR_CORE"); }
	int slice(int i) 	   {  return shadowFailure<>("Tensor_Slice(int)  => THIS METHOD SHOULD ONLY BE ENABLED FOR TENSOR_CORE"); }
};

}

#endif /* EXPRESSION_BASE_H_ */
#endif
