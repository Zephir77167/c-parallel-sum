#include <stdio.h>
#include "../utils/args.h"
#include "../utils/arrays.h"
#include "../utils/timers.h"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define USE_GPU 0
#define DEVICE_TYPE (USE_GPU == 1 ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU)

#define DATA_SIZE 10
#define MAX_SOURCE_SIZE (0x100000)

static long long reduce(int* array, int size) {
  cl_context context;
  cl_context_properties properties[3];
  cl_kernel kernel;
  cl_command_queue command_queue;
  cl_program program;
  cl_int err;
  cl_uint num_of_platforms = 0;
  cl_platform_id platform_id;
  cl_device_id device_id;
  cl_uint num_of_devices = 0;
  cl_mem inputA, inputB, output;

  size_t global;

  float inputDataA[DATA_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  float inputDataB[DATA_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  float results[DATA_SIZE] = {0};

  int i;

  FILE* fp;
  char file_name[] = "open-cl/my_kernel.cl";
  char* source_str;
  size_t source_size;

  fp = fopen(file_name, "r");
  if (!fp) {
    fprintf(stderr, "Failed to load kernel.\n");
    exit(1);
  }

  source_str = malloc(MAX_SOURCE_SIZE);
  source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
  fclose(fp);

  if (clGetPlatformIDs(1, &platform_id, &num_of_platforms) != CL_SUCCESS) {
    fprintf(stderr, "Unable to get platform id.\n");
    exit(1);
  }

  if (clGetDeviceIDs(platform_id, DEVICE_TYPE, 1, &device_id, &num_of_devices) != CL_SUCCESS) {
    fprintf(stderr, "Unable to get device id.\n");
    exit(1);
  }

  properties[0] = CL_CONTEXT_PLATFORM;
  properties[1] = (cl_context_properties)platform_id;
  properties[2] = 0;

  context = clCreateContext(properties, 1, &device_id, NULL, NULL, &err);
  if (err != 0) {
    fprintf(stderr, "Unable to create context (error: %d).\n", err);
    exit(1);
  }

  command_queue = clCreateCommandQueueWithProperties(context, device_id, 0, &err);
  if (err != 0) {
    fprintf(stderr, "Unable to create command queue (error: %d).\n", err);
    exit(1);
  }

  program = clCreateProgramWithSource(context, 1, (const char**)&source_str, (const size_t*)&source_size, &err);
  if (err != 0) {
    fprintf(stderr, "Unable to create program (error: %d).\n", err);
    exit(1);
  }

  err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
  printf("%d\n", err);

  if (err != CL_SUCCESS) {
    char *buff_erro;
    cl_int errcode;
    size_t build_log_len;
    errcode = clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &build_log_len);
    if (errcode) {
      printf("clGetProgramBuildInfo failed at line %d\n", __LINE__);
      exit(-1);
    }

    buff_erro = malloc(build_log_len);
    if (!buff_erro) {
      printf("malloc failed at line %d\n", __LINE__);
      exit(-2);
    }

    errcode = clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, build_log_len, buff_erro, NULL);
    if (errcode) {
      printf("clGetProgramBuildInfo failed at line %d\n", __LINE__);
      exit(-3);
    }

    fprintf(stderr,"Build log: \n%s\n", buff_erro); //Be careful with  the fprint
    free(buff_erro);
    fprintf(stderr,"clBuildProgram failed\n");
    exit(EXIT_FAILURE);
  }


  if (err != CL_SUCCESS) {
    fprintf(stderr, "Error building program.\n");
    exit(1);
  }

  kernel = clCreateKernel(program, "reduce", &err);

  inputA = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(float) * DATA_SIZE, NULL, NULL);
  inputB = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(float) * DATA_SIZE, NULL, NULL);
  output = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * DATA_SIZE, NULL, NULL);

  clEnqueueWriteBuffer(command_queue, inputA, CL_TRUE, 0, sizeof(float) * DATA_SIZE, inputDataA, 0, NULL, NULL);
  clEnqueueWriteBuffer(command_queue, inputB, CL_TRUE, 0, sizeof(float) * DATA_SIZE, inputDataB, 0, NULL, NULL);

  clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputA);
  clSetKernelArg(kernel, 1, sizeof(cl_mem), &inputB);
  clSetKernelArg(kernel, 2, sizeof(cl_mem), &output);

  global = DATA_SIZE;

  clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global, NULL, 0, NULL, NULL);
  clFinish(command_queue);

  clEnqueueReadBuffer(command_queue, output, CL_TRUE, 0, sizeof(float) * DATA_SIZE, results, 0, NULL, NULL);

  printf("output: ");
  for (i = 0; i < DATA_SIZE; ++i) {
    printf("%f ", results[i]);
  }

  clReleaseMemObject(inputA);
  clReleaseMemObject(inputB);
  clReleaseMemObject(output);
  clReleaseProgram(program);
  clReleaseKernel(kernel);
  clReleaseCommandQueue(command_queue);
  clReleaseContext(context);

  // TODO
  (void)size;
  return (long long)(array[0]);
}

int main(int argc, char** argv) {
  int array_size = get_array_size_from_args(argc, argv);
  int* array = generate_array(array_size);

  printf("Reducing array... ");
  fflush(stdout);
  start_timer();
  long long result = reduce(array, array_size);
  stop_timer();
  printf("Done!\n");
  printf("Time took to reduce array: %lums\n", get_ellapsed_time_ms());
  printf("Result: %lld\n", result);

  clean_array(&array);
  return 0;
}
