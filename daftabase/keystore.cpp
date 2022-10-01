#include "keystore.h"
#include "include/daftabase.h"

#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>

#include <iostream>

namespace fs = std::filesystem;

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

private:
    void loadEntryFromFile(const fs::directory_entry& dbEntry);
    void loadDatabaseFromFile(const std::string& dbPath);

    void writeEntryToFile(const std::string& key, const std::string& value);
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
    std::string baseDirectory { ".daftabase" };
    std::string dbDirectory { baseDirectory + DAFTABASE_DIR_DELIM + name };

    m_path = dbDirectory;

    if (!fs::exists(baseDirectory))
    {
        fs::create_directory(baseDirectory);
    }

    if (isNewDb)
    {
        if (fs::exists(dbDirectory))
        {
            throw Error("Database '" + name + "' already exists");
        }

        fs::create_directory(dbDirectory);
    }
    else
    {
        if (!fs::exists(dbDirectory))
        {
            throw Error("Database '" + name + "' does not exist");
        }

        loadDatabaseFromFile(dbDirectory);
    }
}

KeyStore::Impl::~Impl()
{
}

std::string KeyStore::Impl::get(const std::string& key)
{
    std::string result;

    // read data from in-memory map
    try
    {
        result = m_map.at(key);
    }
    catch (std::out_of_range e)
    {
        throw Error("Entry '" + key + "' does not exist");
    }

    return result;
}

void KeyStore::Impl::set(const std::string& key, const std::string& value)
{
    // flush data to filesystem
    writeEntryToFile(key, value);

    // write data to in-memory map
    m_map[key] = value;
}

std::string KeyStore::Impl::getDirectory()
{
    return m_path;
}

void KeyStore::Impl::clear()
{
    m_map.clear();

    if (fs::exists(m_path))
    {
        fs::remove_all(m_path);
    }
}

// KeyStore implementation helper functions
// --------------------------------------------------------------------------------------------------------------------

void KeyStore::Impl::loadEntryFromFile(const fs::directory_entry& dbEntry)
{
    std::ifstream fin(dbEntry.path());
    std::string filename { dbEntry.path().filename().string() };
    std::string key { filename.substr(0, filename.find_last_of('_')) };
    std::string value;

    // read in raw data from file
    fin.seekg(0, std::ios::end);
    value.reserve(fin.tellg());
    fin.seekg(0, std::ios::beg);
    value.assign(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());

    // write to in-memory map
    m_map[key] = value;
}

void KeyStore::Impl::loadDatabaseFromFile(const std::string& dbPath)
{
    for (const auto& entry : fs::directory_iterator(dbPath))
    {
        if (entry.exists() && entry.is_regular_file())
        {
            if (entry.path().extension() == ".kv")
            {
                loadEntryFromFile(entry);
            }
        }
    }
}

void KeyStore::Impl::writeEntryToFile(const std::string& key, const std::string& value)
{
    std::string entryPath { m_path + DAFTABASE_DIR_DELIM + key + "_str.kv" };
    std::ofstream fout;

    fout.open(entryPath, std::ios::out | std::ios::trunc);
    if (!fout.is_open())
    {
        throw Error("Failed to write entry '" + key + "' to filesystem");
    }
    fout << value;
    fout.close();
}

} // namespace daftabase
