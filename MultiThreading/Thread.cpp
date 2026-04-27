#include "Thread.h"

Thread::Thread()
{
    
}

void Thread::Initialize(const int* a, const int* b, int* c, int i, int n, int count)
{
    m_index = i;
    m_t = std::thread(&Thread::add, this, a, b, c, m_index,  n, count);
}
void Thread::join()
{
    m_t.join();
}
void Thread::add(const int* a, const int* b, int* c, int index, int n, int count)
{
    {
        std::unique_lock<std::mutex> lock(h_mtx);
        h_cv.wait(lock, [&]{return start;});
    }
    for (int i = index; i < n; i += count)
    {
        c[i] = a[i] + b[i];
    }
}