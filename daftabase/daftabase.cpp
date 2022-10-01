#include "include/daftabase.h"
#include "keystore.h"

namespace daftabase
{

const std::unique_ptr<Db> Daftabase::create(const std::string& name)
{
    return std::make_unique<KeyStore>(name, true);
}

const std::unique_ptr<Db> Daftabase::load(const std::string& name)
{
    return std::make_unique<KeyStore>(name, false);
}

void Daftabase::destroy(const std::string& name)
{
    const std::unique_ptr<Db> db { load(name) };
    db->clear();
}

} // namespace daftabase
