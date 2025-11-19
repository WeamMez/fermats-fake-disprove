#include <cstdio>
#include <cmath>
#include <thread>
#include <vector>
#include <atomic>

typedef double num_t;

using namespace std;

const num_t MIN_NUMBER = 3;

void single_sum_calc(num_t exp, num_t sum, atomic_bool *finish_flag)
{
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
    finish_flag->store(true);
}

class CalcThread
{
private:
    num_t exp, sum;
    thread *calc_thread;
    atomic_bool finished = false;

public:
    CalcThread(num_t exp, num_t sum) : exp(exp), sum(sum), calc_thread(new thread(single_sum_calc, exp, sum, &this->finished)) {}
    ~CalcThread()
    {
        delete calc_thread;
    }
    bool is_finished()
    {
        return finished.load();
    }
    bool try_join()
    {
        if (this->is_finished())
        {
            calc_thread->join();
            return true;
        }
        return false;
    }
};

void single_exp_calc(num_t exp, num_t max_sum)
{
    const size_t INNER_THREAD_COUNT = thread::hardware_concurrency();
    vector<CalcThread *> calc_threads;
    num_t curr_sum = MIN_NUMBER * 2 + 1;
    while (calc_threads.size() <= INNER_THREAD_COUNT)
    {
        calc_threads.push_back(new CalcThread(exp, curr_sum++));
    }
    while (curr_sum < max_sum)
    {
        for (vector<CalcThread *>::iterator it = calc_threads.begin(); it != calc_threads.end(); it++)
        {
            if ((*it)->try_join())
            {
                delete *it;
                calc_threads.erase(it);
                calc_threads.push_back(new CalcThread(exp, curr_sum++));
            }
        }
    }
}

int main(int argc, char *argv[])
{
    // In case no other input have been provided
    const num_t DEFAULT_MAX_SUM = 1000000;

    const num_t EXPONENT = 3.0;

    int max_sum = DEFAULT_MAX_SUM;
    if (argc > 1)
        max_sum = atoi(argv[1]);
    single_exp_calc(EXPONENT, (num_t)max_sum);
}