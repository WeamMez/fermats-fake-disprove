#include <cstdio>
#include <cmath>

typedef double num_t;

__global__ void single_height_kernel(num_t exp, num_t min_sum)
{
    const num_t MIN_NUMBER = 3;
    const num_t MIN_SUM = MIN_NUMBER * 2 + 1;

    num_t sum = (num_t)(blockIdx.x * blockDim.x + threadIdx.x) + MIN_SUM + min_sum;

    for (num_t a = MIN_NUMBER; a < sum / 2; a++)
    {
        num_t b = sum - a;
        num_t c_pow = pow(a, exp) + pow(b, exp);
        num_t c = pow(c_pow, 1.0 / exp);
        if (floor(c) == ceil(c) && c > b)
        {
            printf("exp=%lf, a=%lf, b=%lf, c=%lf\n", exp, a, b, c);
        }
    }
}

__host__ void single_exp_calc(num_t exp, num_t max_sum)
{
    const int THREADS_IN_BLOCK = 64;
    const int BLOCKS = 64;

    for (int curr_sum = 0; curr_sum < max_sum; curr_sum += BLOCKS * THREADS_IN_BLOCK)
    {
        single_height_kernel<<<BLOCKS, THREADS_IN_BLOCK>>>(exp, curr_sum);
        cudaDeviceSynchronize();
        cudaError_t err = cudaGetLastError();
        if (err != cudaSuccess)
            printf("%s\n", cudaGetErrorString(err));
    }
}

int main(int argc, char *argv[])
{
    // In case no other input have been provided
    const int DEFAULT_MAX_SUM = 1000000;

    const num_t EXPONENT = 3.0;

    int max_sum = DEFAULT_MAX_SUM;
    if (argc > 1)
        max_sum = atoi(argv[1]);
    single_exp_calc(EXPONENT, (num_t)max_sum);
}