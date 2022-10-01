#ifndef _DB_H_
#define _DB_H_

#include <string>

// required for lib to be platform independent
#ifdef _WIN32
#define DAFTABASE_DIR_DELIM "\\"
#else
#define DAFTABASE_DIR_DELIM "/"
#endif

namespace daftabase
{

class Db
{
public:
    Db() = default;
    virtual ~Db() = default;

    virtual std::string get(const std::string& key) = 0;
    virtual void set(const std::string& key, const std::string& value) = 0;

    virtual std::string getDirectory() = 0;

    virtual void clear() = 0;
};

} // namespace daftabase

#endif /* _DB_H_ */
