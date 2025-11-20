# Fermats-fake-disprove
This code uses the 64-bit IEEE-754 limitation to **wrongly** disprove Fermat's last thorem with the exponent of 3.

The different versions may give different results depending on the exact arithmetic algorithms used by the compiler and the processor's architecture.

## Compiling

To compile the CPU version, type `make cpu`.

To compile the CUDA version (faster but requires nvcc) type `make cuda`.

To compile both type `make all`.

## Running

To run the CPU version with default maximum value of 1M, type `make run-cpu`.

To run the CUDA version with default maximum value of 1M, type `make run-cuda`.

To run the CPU version with a specified maximum value, type `./calc_cpu <value>`.

To run the CUDA version with a specified maximum value, type `./calc_cuda <value>`.
