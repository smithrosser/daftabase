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

    std::string get(const std::string& key);
    void set(const std::string& key, const std::string& value);

    std::string getDirectory();

    void clear();
};

// KeyStore top-level API functions
// --------------------------------------------------------------------------------------------------------------------

KeyStore::KeyStore(const std::string& name, bool isNewDb)
    : m_pImpl(std::make_unique<KeyStore::Impl>(name, isNewDb))
{
}

KeyStore::~KeyStore()
{
}

std::string KeyStore::get(const std::string& key)
{
    return m_pImpl->get(key);
}

void KeyStore::set(const std::string& key, const std::string& value)
{
    m_pImpl->set(key, value);
}

std::string KeyStore::getDirectory()
{
    return m_pImpl->getDirectory();
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
    // or create new database
}

KeyStore::Impl::~Impl()
{
}

std::string KeyStore::Impl::get(const std::string& key)
{
    // read data from in-memory map
    return std::string("");
}

void KeyStore::Impl::set(const std::string& key, const std::string& value)
{
    // write data to in-memory map
    // flush data to filesystem
}

std::string KeyStore::Impl::getDirectory()
{
    return std::string("");
}

void KeyStore::Impl::clear()
{
}

} // namespace daftabase