#include <stdio.h>
#include <string.h>
#include "LogMonitor.h"
#if defined(_WIN32)
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#else
#include <unistd.h>
#include <sys/stat.h>
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

void help(const char *progname)
{
    printf("\nThis program is used to monitor log\n"
            "Usage:\n"
            "%s log_filename\n\n", progname);
}

bool fileExists(const char *filename)
{
#if defined(_WIN32)
    return (PathFileExists(filename) == TRUE);
#else
    struct stat sb;
    return (stat(filename, &sb) == 0);
#endif
}

int main(int argc, const char *argv[])
{
    string filename;
    bool exists = false;

    if (argc == 2)
    {
        if ((exists = fileExists(argv[1])))
            filename = argv[1];
    }

    if (!exists)
    {
        help(argv[0]);
        return 1;
    }

    LogMonitor lm(filename.c_str());

    lm.start();

    while (1)
    {
        sleep(1000);
    }

    systemPause();
    return 0;
}
