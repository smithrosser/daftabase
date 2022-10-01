#include "app.h"
#include "daftabase.h"
#include <iostream>

App::App()
{
    // clang-format off
    m_options.add_options()
        ("c,create", "Create a database")
        ("d,destroy", "Destroy a database")
        ("s,set", "Set a key-value pair")
        ("g,get", "Get a key-value pair")
        ("n,name", "Database name (required)", cxxopts::value<std::string>())
        ("k,key", "Key to get/set", cxxopts::value<std::string>())
        ("v,value", "Value to set", cxxopts::value<std::string>())
        ("l,list", "List all database entries")
    ;
    // clang-format on
}

int App::run(int argc, char* argv[])
{
    auto result = m_options.parse(argc, argv);

    if (result.count("c") == 1)
    {
        createDb(result);
    }
    else if (result.count("d") == 1)
    {
        destroyDb(result);
    }
    else if (result.count("l") == 1)
    {
        listDb(result);
    }
    else if (result.count("s") == 1)
    {
        setEntry(result);
    }
    else if (result.count("g") == 1)
    {
        getEntry(result);
    }

    std::cerr << "No command line options provided!\n\n";
    printUsage();

    exit(ReturnCode::Error);
}

void App::printUsage()
{
    std::cerr << m_options.help({ "" }, true) << '\n';
}

void App::createDb(const cxxopts::ParseResult& result)
{
    if (result.count("n") != 1)
    {
        std::cerr << "Please supply a database name: -n <name>\n";
        exit(ReturnCode::Error);
    }

    try
    {
        daftabase::Daftabase::create(result["n"].as<std::string>());
    }
    catch (daftabase::Error err)
    {
        std::cerr << "[Daftabase error] " << err.what() << "\n";
        exit(ReturnCode::Error);
    }

    exit(ReturnCode::Success);
}

void App::destroyDb(const cxxopts::ParseResult& result)
{
    if (result.count("n") != 1)
    {
        std::cerr << "Please supply a database name: -n <name>\n";
        exit(ReturnCode::Error);
    }

    try
    {
        daftabase::Daftabase::destroy(result["n"].as<std::string>());
    }
    catch (daftabase::Error err)
    {
        std::cerr << "[Daftabase error] " << err.what() << "\n";
        exit(ReturnCode::Error);
    }

    exit(ReturnCode::Success);
}

void App::listDb(const cxxopts::ParseResult& result)
{
    // TODO implement listing all database entries
}

void App::setEntry(const cxxopts::ParseResult& result)
{
    if (result.count("n") != 1)
    {
        std::cerr << "Please supply a database name: -n <name>\n";
        exit(ReturnCode::Error);
    }
    if (result.count("k") != 1)
    {
        std::cerr << "Please supply a key: -k <key>\n";
        exit(ReturnCode::Error);
    }
    if (result.count("v") != 1)
    {
        std::cerr << "Please supply a value: -v <value>\n";
        exit(ReturnCode::Error);
    }

    std::string dbName { result["n"].as<std::string>() };
    std::string key { result["k"].as<std::string>() };
    std::string value { result["v"].as<std::string>() };

    try
    {
        daftabase::DbRef db { daftabase::Daftabase::load(dbName) };
        db->set(key, value);
    }
    catch (daftabase::Error err)
    {
        std::cerr << "[Daftabase error] " << err.what() << "\n";
        exit(ReturnCode::Error);
    }

    exit(ReturnCode::Success);
}

void App::getEntry(const cxxopts::ParseResult& result)
{
    if (result.count("n") != 1)
    {
        std::cerr << "Please supply a database name: -n <name>\n";
        exit(ReturnCode::Error);
    }
    if (result.count("k") != 1)
    {
        std::cerr << "Please supply a key: -k <key>\n";
        exit(ReturnCode::Error);
    }

    std::string dbName { result["n"].as<std::string>() };
    std::string key { result["k"].as<std::string>() };
    std::string value;

    try
    {
        daftabase::DbRef db { daftabase::Daftabase::load(dbName) };
        value = db->get(key);
    }
    catch (daftabase::Error err)
    {
        std::cerr << "[Daftabase error] " << err.what() << "\n";
        exit(ReturnCode::Error);
    }

    std::cout << value;

    exit(ReturnCode::Success);
}