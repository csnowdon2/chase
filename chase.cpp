#include <iostream>
#include <vector>
#include <cstdio>
#include <chrono>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Expected one arg: size (KB)" << std::endl;
    exit(1);
  }

  const size_t cacheline = 64;
  size_t max_size = 1024*atoi(argv[1])/4;
  // std::cout << "Size   = " << size << std::endl;


  std::cout << "size,stride,latency" << std::endl;
  for (int size = 256; size < max_size; size <<= 1) {
    int reps = size*10;
    std::vector<int> data(size);
    for (int stride = 1; stride < size; stride <<= 1) {
      std::cout << size*sizeof(int) << ",";
      std::cout << stride*sizeof(int) << ",";
      //std::cout << "Stride=" << stride*sizeof(int) << "B\t\t";
      int set = std::min(cacheline, stride*sizeof(int));
      // size/stride = # of sets accessed
      // set = size retrieved from memory, e.g. whole cache line or one int
      for (int i = 0; i < size; i++)
        data[i] = (i+stride)%size;

      // Bandwidth will be low as we are forcing the loop
      // to depend on latency.
      auto t1 = std::chrono::high_resolution_clock::now();
      int k = 0;
      for (int i = 0; i < reps; i++)
        k = data[k];
      auto t2 = std::chrono::high_resolution_clock::now();
      double t = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
      std::cout << t/reps << std::endl;
    }
  }
}
