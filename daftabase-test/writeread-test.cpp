#include "daftabase.h"
#include <catch2/catch_all.hpp>

TEST_CASE("Get/set database entry", "[DatabaseGetSet]")
{
    // who: Database user
    // what: Add a key-value pair to the store
    // value: To persist data that can be read later

    SECTION("Normal usage")
    {
        daftabase::DbRef db { daftabase::Daftabase::create("SetTestDb") };
        std::string key { "ThisIsAKey" };
        std::string value { "This is some important data to be saved!" };

        // success conditions:
        // 1) values above should be written to disk and to the in-memory map
        db->set(key, value);
        REQUIRE(db->get(key) == value);

        db->clear();
    }

    SECTION("Change existing data")
    {
        daftabase::DbRef db { daftabase::Daftabase::create("SetTestDb") };
        std::string key { "ThisIsAKey" };
        std::string value { "This is some important data to be saved!" };

        db->set(key, value);
        REQUIRE(db->get(key) == value);

        // success conditions:
        // 1) the changed value should be written to disk and to the in-memory map
        value = "This is some equally important, different data to be saved.";
        db->set(key, value);
        REQUIRE(db->get(key) == value);

        db->clear();
    }
}