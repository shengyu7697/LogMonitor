#include "LogMonitor.h"
#include <string.h>
#if defined(_WIN32)
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

//#define DEBUG
#define BUF_SIZE 64

inline void sleep(int milliseconds)
{
#if defined(_WIN32)
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

LogMonitor::LogMonitor(const std::string &filename)
    : m_filename(filename)
    , m_fp(NULL)
    , m_interrupt(false)
{
    m_open();
}

LogMonitor::~LogMonitor()
{
    m_close();
}

void LogMonitor::start()
{
    char buf[BUF_SIZE];
    long int size;
    long int totalSize;

    size = ftell(m_fp);
    totalSize = m_getFileSize();
    while (!m_interrupt)
    {
        if (size < totalSize)
        {
            memset(buf, 0, sizeof(buf));
            //fread(buf, 1, sizeof(buf), m_fp);
            fgets(buf, sizeof(buf), m_fp);
            printf("%s", buf);
            fflush(stdout);

            size = ftell(m_fp);

#if defined(DEBUG)
            printf("size = %ld %ld\n", size, totalSize);
            sleep(1000);
#endif
        }
        totalSize = m_getFileSize();
    }
}

void LogMonitor::stop()
{
    m_interrupt = true;
}

void LogMonitor::m_open()
{
    m_fp = fopen(m_filename.c_str(), "r");

    if (m_fp == NULL)
        printf("ERROR: Can't open the file %s\n", m_filename.c_str());
}

void LogMonitor::m_close()
{
    if (m_fp != NULL)
        fclose(m_fp);
}

long int LogMonitor::m_getFileSize()
{
    long int nowSize;
    long int totalSize;

    nowSize = ftell(m_fp);

    fseek(m_fp , 0, SEEK_END);
    totalSize = ftell(m_fp);

    fseek(m_fp , nowSize, SEEK_SET);

    return totalSize;
}
