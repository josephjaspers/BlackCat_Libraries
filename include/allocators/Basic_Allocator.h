/*  Project: BlackCat_Tensors
 *  Author: JosephJaspers
 *  Copyright 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BASIC_ALLOCATOR_H_
#define BASIC_ALLOCATOR_H_

namespace BC {

class CPU;

namespace module {
namespace stl  {

struct Basic_Allocator : CPU {

    using mathlib_t = CPU;

    template<typename T>
    static T*& allocate(T*& internal_mem_ptr, int size) {
        internal_mem_ptr = new T[size];
        return internal_mem_ptr;
    }
    template<typename T>
    static T*& unified_allocate(T*& intenral_mem_ptr, int size) {
        intenral_mem_ptr = new T[size];
        return intenral_mem_ptr;
    }
    template<typename T>
    static void deallocate(T* t) {
        delete[] t;
    }
    template<typename T>
    static void deallocate(T t) {
        //empty
    }
    template<class T, class U>
    static void HostToDevice(T* device_ptr, U* host_ptr, int size=1) {
        CPU::copy(device_ptr, host_ptr, size);
    }
    template<class T, class U>
    static void DeviceToHost(T* host_ptr, U* device_ptr, int size=1) {
        CPU::copy(host_ptr, device_ptr, size);
    }
    template<class T>
    static T extract(T* data_ptr, int index) {
    	return data_ptr[index];
    }

};
}
}
}



#endif /* BASIC_ALLOCATOR_H_ */