#ifndef _DAFTABASE_H_
#define _DAFTABASE_H_

#include "db.h"
#include "error.h"
#include <memory>
#include <string>

namespace daftabase
{

using DbRef = std::unique_ptr<Db>;

class Daftabase
{
public:
    static const std::unique_ptr<Db> create(const std::string& name);
    static const std::unique_ptr<Db> load(const std::string& name);
};

} // namespace daftabase

#endif /* _DAFTABASE_H_ */
