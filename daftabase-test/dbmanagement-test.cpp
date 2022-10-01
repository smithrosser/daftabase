#include "daftabase.h"
#include <catch2/catch_all.hpp>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("Create empty db", "[CreateEmptyDb]")
{
    // who: Database administrator
    // what: Create a new, empty database
    // value: For later storage & retrieval of data

    SECTION("Create db normally")
    {
        daftabase::DbRef db { daftabase::Daftabase::create("TestDb") };

        // success conditions:
        // 1) a valid database instance should be returned
        // 2) a new folder named after the database should be created
        REQUIRE(fs::is_directory(fs::status(db->getDirectory())));

        // 3) the folder should be empty
        const auto& itr { fs::directory_iterator(db->getDirectory()) };
        REQUIRE(itr == end(itr));

        db->clear();
    }

    SECTION("Create db with name already taken")
    {
        bool isError { false };
        daftabase::DbRef db { daftabase::Daftabase::create("TestDb") };

        try
        {
            daftabase::DbRef db { daftabase::Daftabase::create("TestDb") };
        }
        catch (daftabase::Error err)
        {
            // success conditions:
            // 1) daftabase should throw an exception if recreation attempted
            isError = true;
        }

        REQUIRE(isError);

        db->clear();
    }
}

TEST_CASE("Load existing database", "[LoadExistingDb]")
{
    // who: Database user
    // what: Load an existing database
    // value: For later storage & retrieval of data

    SECTION("Load db normally")
    {
        daftabase::DbRef db { daftabase::Daftabase::create("TestDb") };
        daftabase::DbRef db2 { daftabase::Daftabase::load("TestDb") };

        // success conditions:
        // 1) a valid database instance should be returned
        // 2) a new folder named after the database should be created
        REQUIRE(fs::is_directory(fs::status(db->getDirectory())));

        // 3) the folder should be empty
        const auto& itr { fs::directory_iterator(db->getDirectory()) };
        REQUIRE(itr == end(itr));

        db->clear();
    }

    SECTION("Load non-existent db")
    {
        bool isError { false };

        try
        {
            daftabase::DbRef db { daftabase::Daftabase::load("TestDb") };
        }
        catch (daftabase::Error err)
        {
            // success conditions:
            // 1) daftabase should throw an exception if nonexistent load attempted
            isError = true;
        }

        REQUIRE(isError);
    }
}