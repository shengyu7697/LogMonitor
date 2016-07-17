#ifndef LOGMONITOR_H
#define LOGMONITOR_H

#include <string>

class LogMonitor
{
    private:
        const std::string m_filename;
        FILE *m_fp;
        bool m_interrupt;

    public:
        LogMonitor(const std::string &filename);
        ~LogMonitor();
        void start();
        void stop();

    private:
        void m_open();
        void m_close();
        long int m_getFileSize();
};

#endif
