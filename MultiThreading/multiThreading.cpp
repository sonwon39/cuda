#include <chrono>
#include <vector>
#include <iostream>
#include <random>
#include "Thread.h"

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1,10);
    int thread_count = std::thread::hardware_concurrency();
    std::cout << "thread count : " << thread_count << "\n";

    using clock = std::chrono::high_resolution_clock;

    int n = 100'000'000;
    int bytes = n * sizeof(int);

    int *a, *b, *c;
    a = (int*)malloc(bytes);
    b = (int*)malloc(bytes);
    c = (int*)malloc(bytes);
    for (int i = 0; i < n; i++)
    {
        a[i] = int(dist(gen));   
        b[i] = int(dist(gen));   
    }
    std::vector<Thread> threads(thread_count);
    for (int i = 0; i < thread_count; i++)
    {
        threads[i].Initialize(a,b,c,i,n,thread_count);
    }
    std::cout << "multi thread start\n";

    auto start_tick = clock::now();

    {
        std::lock_guard<std::mutex> lock(h_mtx);
        start = true;
    }
    h_cv.notify_all();

    for (int i = 0; i < thread_count; i++)
    {
        threads[i].join();
    }
    auto end_tick = clock::now();
    double elapsed_time = std::chrono::duration<double,std::milli>(end_tick - start_tick).count();

    std::cout << "elapsed time (multi thread) : " << elapsed_time << " ms\n";
    

    start_tick = clock::now();

#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        c[i] = a[i] + b[i];
    }
    
    end_tick = clock::now();
    elapsed_time = std::chrono::duration<double,std::milli>(end_tick - start_tick).count();

    std::cout << "elapsed time (multi thread - OpenMP): " << elapsed_time << " ms\n";

    start_tick = clock::now();

    for (int i = 0; i < n; i++)
    {
        c[i] = a[i] + b[i];
    }
    end_tick = clock::now();
    elapsed_time = std::chrono::duration<double,std::milli>(end_tick - start_tick).count();

    std::cout << "elapsed time (1 thread): " << elapsed_time << " ms\n";

    free(a);
    free(b);
    free(c);
}
