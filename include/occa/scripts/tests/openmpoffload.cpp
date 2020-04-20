// OMP Offload Testing (Anoop)
#include <omp.h>

int main(int argc, char **argv) {
#if(defined(__INTEL_LLVM_COMPILER) && !(defined(__SYCL_DEVICE_ONLY__)))
  return 0;
#else
  return 1;
#endif
}

