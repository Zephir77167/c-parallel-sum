#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

kernel void reduce(global float* inputA, global float* inputB, float* output) {
  size_t id = get_global_id(0);
  output[id] = inputA[id] + inputB[id];
}
