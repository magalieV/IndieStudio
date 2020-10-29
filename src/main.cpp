/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Menu
 *
 * File creation = 27/05/2020
 * Last modification = 27/05/2020
 */

#include <filesystem>
#include <fstream>
#include "Engine/Core.hpp"
#include "Engine/GenerateMap.hpp"
#include "Engine/PathFinder.hpp"
#include "MacroIndie.hpp"
#include "Engine/AError.hpp"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
    if (!std::filesystem::exists(".save")) {
        std::filesystem::create_directory(".save");
        std::filesystem::create_directory(".save/.users");
        std::ofstream saveFile(".save/.users/.userAccount.xml");
        saveFile << "<?xml version='1.0' encoding='utf-8'?>\n";
        saveFile.close();
    }
    try {
        indie::engine::Core game;
        game.run();
    } catch (const AError &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}