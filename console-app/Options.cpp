#include "Options.hpp"

#include "FileLoader.hpp"

#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

Options::Options(int argc, char **argv)
{
    configureOptions();
    loadArgs(argc, argv);
    if (loadConfigFile())
    {
        cout << "Config file loaded" << endl;
    }
    else
    {
        cout << "Config file not found" << endl;
    }
    cout << "Configuration: " << endl;
    cout << "\tinput-path: " << inputPath << endl;
    cout << "\textensions: [";
    for (string const& ext : extensions)
    {
        cout << ext << ", ";
    }
    cout << "]" << endl;
    loadExs();
}

void Options::loadExs()
{
    if (!v1.empty()) exs.vexs.push_back(Vex(v1));

    // TODO append other values

    /*if (!v2.empty()) exs.vexs.emplace_back(Vex(v2));
    if (!v3.empty()) exs.vexs.emplace_back(Vex(v3));
    if (!t1.empty()) exs.texs.emplace_back(Tex(t1));
    if (!t2.empty()) exs.texs.emplace_back(Tex(t2));
    if (!t3.empty()) exs.texs.emplace_back(Tex(t3));
    if (!f1.empty()) exs.fexs.emplace_back(Fex(f1));
    if (!f2.empty()) exs.fexs.emplace_back(Fex(f2));
    if (!f3.empty()) exs.fexs.emplace_back(Fex(f3));*/
}

string const& Options::getInputPath() const
{
    return inputPath;
}

Extensions Options::getExtensions() const
{
    return extensions;
}

Exs const& Options::getExs() const
{
    return exs;
}

void Options::loadArgs(int argc, char **argv)
{
    po::store(po::parse_command_line(argc, argv, options), vm);
    vm.notify();
}

bool Options::loadConfigFile()
{
    string defaultConfigFile("../data/config");
    if (vm.count("config-file"))
    {
        return processConfigFile(configFilename);
    }
    else if (FileLoader::exists(defaultConfigFile))
    {
        return processConfigFile(defaultConfigFile);
    }
    return false;
}

bool Options::processConfigFile(string const& filename)
{
    std::ifstream file;
    if (FileLoader::openFile(filename, file))
    {
        po::store(po::parse_config_file(file, options), vm);
        po::notify(vm);
        return true;
    }
    return false;
}

void Options::configureOptions()
{
    po::options_description generic("Generic options");
    generic.add_options()
        ("version,v", "print version string")
        ("help,h", "produce help message")
        ;

    po::options_description config("Configuration");
    config.add_options()
        ("config-file", po::value<string>(&configFilename),
              "configuration file path")
        ("input-path", po::value<string>(&inputPath),
            "input file/directory path")
        ("extensions,e", po::value<Extensions>(&extensions)->multitoken(),
            "extensions of files (ex. .c or .h")
        ("lang,l", "processing language, possible values: c++, java")
        ;

    po::options_description searchOptions("Search");
    searchOptions.add_options()
            ("V1", po::value<string>(&v1),
                  "V1")
            ("V2", po::value<string>(&v2),
                  "V2")
            ("V3", po::value<string>(&v3),
                  "V3")
            ("T1", po::value<string>(&t1),
                  "T1")
            ("T2", po::value<string>(&t2),
                  "T2")
            ("T3", po::value<string>(&t3),
                  "T3")
            ("F1", po::value<string>(&f1),
                  "F1")
            ("F2", po::value<string>(&f2),
                  "F2")
            ("F3", po::value<string>(&f3),
                  "F3")
        ;

    options.add(generic).add(config).add(searchOptions);
}
