#pragma once
#include <thread>

class OsUtils
{
public:
    OsUtils()
    {
        // KE: request how many threads OS has available to do the job
        threadsAvailable = 1;
        // TODO: once multithreading is supported uncomment this
        // threadsAvailable = std::thread::hardware_concurrency();
    }

    // @brief return amount of threads that could be used
    unsigned int GetAvailableThreads() const;

private:
    unsigned int threadsAvailable;
};

