#pragma once

#include "exs/Exs.hpp"

#include <boost/program_options.hpp>
#include <vector>

class Options
{
public:
    Options(int argc, char ** argv);
    std::string const& getInputPath() const;
    std::vector<std::string> getExtensions() const;
    Exs const& getExs() const;

private:
    void loadArgs(int argc, char ** argv);
    bool loadConfigFile();
    bool processConfigFile(std::string const& filename);
    void loadExs();

    void configureOptions();

    boost::program_options::options_description options;
    boost::program_options::variables_map vm;

    std::string configFilename, inputPath;
    std::vector<std::string> extensions;
    std::string v1, v2, v3, t1, t2, t3, f1, f2, f3;
    Exs exs;
};
