/*
 * _shaping_test.h
 *
 *  Created on: May 22, 2018
 *      Author: joseph
 */

#ifndef SHAPING_TEST_H_
#define SHAPING_TEST_H_

#include <iostream>
#include "../BlackCat_Tensors.h"

using BC::Vector;
using BC::Matrix;
using BC::Cube;

int shaping() {

	//parameter oacks + lamdas not supported by CUDA yet
//#ifndef __CUDACC__
	std::cout << " --------------------------------------SHAPING (RESHAPE, AND CHUNK)--------------------------------------" << std::endl;



	Cube<float, BC::CPU> m2(4,4, 4);
	m2.randomize(0,100);
	std::cout << " original " << std::endl;
	m2.print();

	std::cout << " reshape (2,16, 2) " << std::endl;
	reshape(m2)(2, 16, 2).print();

	std::cout << " chunk at (2,1, 0) dims (2,3) (utilizing shape object)" << std::endl;

//	std::cout << m2.internal().chunk(2,1,0)(1,1,1)[0] << std::endl;

		chunk(m2)(2,1,0)(2,3).print_leading_dimensions();//.internal()[i] << std::endl;
		chunk(m2)(2,1,0)(2,3).print();//.internal()[i] << std::endl;


		// FIXME DOES NOT WORK

//	std::cout << "reshape (2,3) chunk to (3,2)" << std::endl;
//	chunk(m2)(2,1,0)(2,3);//.print();
//	reshape(ch)(3,2);
//	m2.print();

//#endif
	return 0;
}



#endif /* SHAPING_TEST_H_ */
