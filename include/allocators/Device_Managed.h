/*
 * CUda_Managed_Allocator.h
 *
 *  Created on: Oct 24, 2018
 *      Author: joseph
 */
#ifdef __CUDACC__
#ifndef BC_ALLOCATOR_DEVICE_MANAGED_H_
#define BC_ALLOCATOR_DEVICE_MANAGED_H_

#include "Device.h"

namespace BC {
namespace allocators {

/// A basic allocator, memory is allocated via 'cudaMallocManaged'
template<class T>
struct Device_Managed : Allocator<device_tag, T> {

	static constexpr bool managed_memory = true;

	template<class altT>
	struct rebind { using other = Device_Managed<altT>; };

	Device_Managed() = default;
	Device_Managed(const Device_Managed&)=default;
	Device_Managed(Device_Managed&&) = default;

	Device_Managed& operator = (const Device_Managed&) = default;
	Device_Managed& operator = (Device_Managed&&) = default;

	template<class U>
	constexpr bool operator == (const Device_Managed<U>&) { return true; }

	template<class U>
	Device_Managed(const Device_Managed<U>&) {}

    T* allocate(BC::size_t sz) {
    	T* memptr = nullptr;
    	BC_CUDA_ASSERT((cudaMallocManaged((void**) &memptr, sizeof(T) * sz)));
    	BC_CUDA_ASSERT((cudaDeviceSynchronize())); //This is only required for MallocManagedMemory
        return memptr;
    }
};

}
}


#endif /* CUDA_MANAGED_ALLOCATOR_H_ */
#endif