#include <thread>
#include <condition_variable>
#include <mutex>

inline std::condition_variable h_cv;
inline std::mutex h_mtx;

inline bool start = false;

class Thread{
public:
    Thread();

public:
    void Initialize(const int* a, const int* b, int* c, int i, int n, int count);
    void join();
    
private:
    
    void add(const int* a, const int* b, int* c, int index, int n, int count);

    std::thread m_t;
    int m_index = 0;
};