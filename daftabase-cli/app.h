#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <cxxopts.hpp>

class App
{
private:
    cxxopts::Options m_options { "daftabase-cli", "Command-line interface for Daftabase" };

public:
    enum ReturnCode
    {
        Success = 0,
        Error = 1,
    };

    App();

    int run(int argc, char* argv[]);

private:
    void printUsage();
    void createDb(const cxxopts::ParseResult& result);
    void destroyDb(const cxxopts::ParseResult& result);
    void listDb(const cxxopts::ParseResult& result);
    void setEntry(const cxxopts::ParseResult& result);
    void getEntry(const cxxopts::ParseResult& result);
};

#endif /* _APPLICATION_H_ */
