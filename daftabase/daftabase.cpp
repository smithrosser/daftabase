#include "daftabase.h"
#include "keystore.h"

namespace daftabase
{

static const std::unique_ptr<Db> create(const std::string& name)
{
    return std::make_unique<KeyStore>(name, true);
}

static const std::unique_ptr<Db> load(const std::string& name)
{
    return std::make_unique<KeyStore>(name, false);
}

} // namespace daftabase