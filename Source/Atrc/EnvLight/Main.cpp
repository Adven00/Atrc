#include <filesystem>
#include <iostream>
#include <string>

#include <AGZUtils/Utils/Exception.h>
#include <Lib/cxxopts/cxxopts.hpp>

/*
    1. ��.npy��ʽ�Ļ�������гϵ��ת��Ϊ��(theta, phi)ֱ��ӳ�䵽uv�Ļ�����ͼ
*/

void NpySHToNormal(const std::string &npyFilename, int width, int height, const std::string &outputFilename);

void Run(int argc, char *argv[])
{
    cxxopts::Options opt("Atrc::EnvLight");
    opt.add_options()
        ("i,input", "input filename", cxxopts::value<std::string>())
        ("o,output", "output filename", cxxopts::value<std::string>())
        ("w,width", "output image width", cxxopts::value<int>())
        ("h,height", "output image height", cxxopts::value<int>())
        ("help", "print help");
    auto optRt = opt.parse(argc, argv);

    if(optRt.count("help"))
        std::cout << opt.help({ "" }) << std::endl;

    if(!optRt.count("input"))
    {
        std::cout << "input filename is unspecified" << std::endl;
        return;
    }

    if(!optRt.count("output"))
    {
        std::cout << "output filename is unspecified" << std::endl;
        return;
    }

    auto inputFilename = optRt["input"].as<std::string>();
    auto outputFilename = optRt["output"].as<std::string>();

    auto iExt = std::filesystem::path(inputFilename).extension();
    auto oExt = std::filesystem::path(outputFilename).extension();

    if(iExt == ".npy" && oExt == ".png")
        NpySHToNormal(inputFilename, optRt["width"].as<int>(), optRt["height"].as<int>(), outputFilename);
    else
        std::cout << "Unknown convertion type (" << iExt.string() << " -> " << oExt.string() << std::endl;
}

int main(int argc, char *argv[])
{
    try
    {
        Run(argc, argv);
    }
    catch(const std::exception &err)
    {
        std::vector<std::string> errMsgs;
        AGZ::ExtractHierarchyExceptions(err, std::back_inserter(errMsgs));
        for(auto &m : errMsgs)
            std::cout << m << std::endl;
    }
    catch(...)
    {
        std::cout << "An unknown error occurred..." << std::endl;
    }
}
