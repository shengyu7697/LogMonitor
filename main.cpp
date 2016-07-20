#include <stdio.h>
#include <string>
#include "LogMonitor.h"
#if defined(_WIN32)
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

inline void sleep(int milliseconds)
{
#if defined(_WIN32)
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

void systemPause()
{
    printf("%s\n", "press any key to continue...");
    getchar();
}

int main(int argc, const char *argv[])
{
    string filename = "test.log";

    if (argc >= 2)
        filename = argv[1];

    LogMonitor lm(filename.c_str());

    lm.start();

    while (1)
    {
        sleep(1000);
    }

    systemPause();
    return 0;
}
