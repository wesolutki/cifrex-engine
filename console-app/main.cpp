#include "Options.hpp"
#include <Engine.hpp>

int main(int argc, char ** argv)
{
    Options options(argc, argv);
    EngineOptions engineOptions(true);
    Engine engine(engineOptions, options.getExs().vexs);
    if (engine.ok())
    {
        std::cout << "Engine loaded properly" << std::endl;
        engine.search(options.getInputPath(), options.getExtensions());
    }
    else
    {
        std::cout << "Nothing to search!" << std::endl;
    }
    return 0;
}
