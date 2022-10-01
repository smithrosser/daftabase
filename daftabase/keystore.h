#ifndef _KEYSTORE_H_
#define _KEYSTORE_H_

#include "include/db.h"
#include <memory>

namespace daftabase
{

class KeyStore : public Db
{
private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;

public:
    KeyStore(const std::string& name, bool isNewDb);
    virtual ~KeyStore();

    std::string get(const std::string& key);
    void set(const std::string& key, const std::string& value);

    std::string getDirectory();

    void clear();
};

} // namespace daftabase

#endif /* _KEYSTORE_H_ */
