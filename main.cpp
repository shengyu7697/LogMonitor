#include <stdio.h>
#include <string>
#include "LogMonitor.h"

using namespace std;

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

    systemPause();
    return 0;
}
