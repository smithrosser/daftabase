#ifndef _APP_H_
#define _APP_H_

#include <cxxopts.hpp>

namespace daftabasecli
{

enum ReturnCode
{
    Success = 0,
    Error = 1,
};

class App
{
private:
    cxxopts::Options m_options { "daftabase-cli", "Command-line interface for Daftabase" };

public:
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

} // namespace daftabasecli

#endif /* _APP_H_ */
