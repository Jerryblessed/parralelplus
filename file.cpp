#include <iostream>

__global__
void vectorAdd(int *a, int *b, int *c, int n) {
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < n) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    int n = 1000;
    int *a, *b, *c;
    // CUDA memory allocation and initialization
    
    vectorAdd<<<(n+255)/256, 256>>>(a, b, c, n);
    
    // CUDA memory copy and cleanup
    
    return 0;
}
