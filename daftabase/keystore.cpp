#include "keystore.h"

#include <string>
#include <unordered_map>

namespace daftabase
{

class KeyStore::Impl : public Db
{
private:
    std::string m_name;
    std::string m_path;
    std::unordered_map<std::string, std::string> m_map;

public:
    Impl(const std::string& name, bool isNewDb);
    virtual ~Impl();

    virtual std::string get(const std::string& key) const;
    virtual std::string set(const std::string& key, const std::string& value);

    virtual void clear();
};

// KeyStore top-level API functions
// --------------------------------------------------------------------------------------------------------------------

KeyStore::KeyStore(const std::string& name, bool isNewDb)
    : m_pImpl(std::make_unique<KeyStore::Impl>(name))
{
}

KeyStore::~KeyStore()
{
}

std::string KeyStore::get(const std::string& key) const
{
    return m_pImpl->get(key);
}

std::string KeyStore::set(const std::string& key, const std::string& value)
{
    m_pImpl->set(key, value);
}

void KeyStore::clear()
{
    m_pImpl->clear();
}

// Actual KeyStore implementation code
// --------------------------------------------------------------------------------------------------------------------

KeyStore::Impl::Impl(const std::string& name, bool isNewDb)
    : m_name(name)
{
    // check for existing database with called `name`
    // load data in from filesystem
}

KeyStore::Impl::~Impl()
{
}

std::string KeyStore::Impl::get(const std::string& key) const
{
    // read data from in-memory map
}

std::string KeyStore::Impl::set(const std::string& key, const std::string& value)
{
    // write data to in-memory map
    // flush data to filesystem
}

void KeyStore::Impl::clear()
{
}

} // namespace daftabase