#include <CL/sycl.hpp>
#include <iostream>

namespace sycl = cl::sycl;

class VectorAdd;

int main() {
    int n = 1000;
    std::vector<int> a(n), b(n), c(n);
    // Initialize a and b arrays
    
    {
        sycl::queue queue(sycl::default_selector{});

        sycl::buffer<int, 1> bufA(a.data(), sycl::range<1>(n));
        sycl::buffer<int, 1> bufB(b.data(), sycl::range<1>(n));
        sycl::buffer<int, 1> bufC(c.data(), sycl::range<1>(n));

        queue.submit([&](sycl::handler &cgh) {
            auto accA = bufA.get_access<sycl::access::mode::read>(cgh);
            auto accB = bufB.get_access<sycl::access::mode::read>(cgh);
            auto accC = bufC.get_access<sycl::access::mode::write>(cgh);

            cgh.parallel_for<class VectorAdd>(sycl::range<1>(n), [=](sycl::id<1> idx) {
                int i = idx[0];
                accC[i] = accA[i] + accB[i];
            });
        });
    }
    
    // Use c array
    
    return 0;
}
