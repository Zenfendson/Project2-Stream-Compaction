#include <cuda.h>
#include <cuda_runtime.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/scan.h>
#include "common.h"
#include "thrust.h"

namespace StreamCompaction {
    namespace Thrust {
        using StreamCompaction::Common::PerformanceTimer;
        PerformanceTimer& timer()
        {
            static PerformanceTimer timer;
            return timer;
        }
        /**
         * Performs prefix-sum (aka scan) on idata, storing the result into odata.
         */
        void scan(int n, int *odata, const int *idata) {
            // Create device_vectors and copy input data to device
            thrust::device_vector<int> dv_in(idata, idata + n);
            thrust::device_vector<int> dv_out(n);
            
            nvtxRangePushA("thrust scan");

            timer().startGpuTimer();
            thrust::exclusive_scan(dv_in.begin(), dv_in.end(), dv_out.begin());
            timer().endGpuTimer();
            
            nvtxRangePop();


            thrust::copy(dv_out.begin(), dv_out.end(), odata);
            
        }
    }
}
