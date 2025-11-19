CXX = g++
CXX_OUTPUT = calc_cpu

CUDA = nvcc
CUDA_OUTPUT = calc_cuda

all: cuda cpu

cuda:
	$(CUDA) calc.cu -o $(CUDA_OUTPUT)

cpu:
	$(CXX) calc.cpp -o $(CXX_OUTPUT)

run-cuda:
	./$(CUDA_OUTPUT)

run-cpu:
	./$(CXX_OUTPUT)

clean:
	rm -f $(CUDA_OUTPUT) $(CXX_OUTPUT)