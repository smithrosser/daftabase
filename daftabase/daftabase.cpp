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

} // namespace daftabase