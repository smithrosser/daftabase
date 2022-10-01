#ifndef _DB_H_
#define _DB_H_

#include <string>

namespace daftabase
{

class Db
{
public:
    Db() = default;
    virtual ~Db() = 0;

    virtual std::string get(const std::string& key) = 0;
    virtual std::string set(const std::string& key, const std::string& value) = 0;

    virtual void clear() = 0;
};

} // namespace daftabase

#endif /* _DB_H_ */
