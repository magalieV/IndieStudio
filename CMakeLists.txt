cmake_minimum_required(VERSION 3.11)
project(bomberman)

# set the cmake variable

if (NOT DEFINED IRRLICHT_LOCATION)
	file(MAKE_DIRECTORY "cmake")
	set (IRRLICHT_LOCATION "cmake")
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindIrrlicht.cmake
		DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/cmake)
endif()

file(MAKE_DIRECTORY "lib")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/lib/"  DESTINATION "${CMAKE_BINARY_DIR}/lib")

if(MSVC)
	set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/SFML-2.5.1/lib/cmake/SFML")
endif()

option(COPY_ASSET_FILES "Copy assets files (assets/) when installing" ON)
## copy resource files
if(COPY_ASSET_FILES)
	file(MAKE_DIRECTORY "assets")
	file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets/"  DESTINATION "${CMAKE_BINARY_DIR}/assets")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${IRRLICHT_LOCATION})


# Add custom command like fclean or re command
add_custom_target(fclean COMMAND rm -f MyGKrell COMMAND make clean)
add_custom_target(re COMMAND make fclean COMMAND ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all)

# add the encrypt tool
add_subdirectory(EncryptTool)
add_subdirectory(src/objects)
add_subdirectory(src/banks)
add_subdirectory(src/connexion)
add_subdirectory(src/menu)
add_subdirectory(src/Engine)
add_subdirectory(src/Game)

#include
include_directories(inc/)

get_directory_property(SRCS_OBJECTS DIRECTORY src/objects DEFINITION OBJECTS_FILES)
get_directory_property(SRCS_BANKS DIRECTORY src/banks DEFINITION BANKS_FILES)
get_directory_property(SRCS_CONNEXION DIRECTORY src/connexion DEFINITION CONNEXION_FILES)
get_directory_property(SRCS_MENU DIRECTORY src/menu DEFINITION MENU_FILES)
get_directory_property(SRCS_ENGINE DIRECTORY src/Engine DEFINITION ENGINE_FILES)
get_directory_property(SRCS_GAME DIRECTORY src/Game DEFINITION GAME_FILES)

# set the source files
set(SRCS
    src/main.cpp
	inc/MacroIndie.hpp
	inc/interface/IConnexion.hpp
	inc/interface/ISubMenu.hpp
	inc/interface/IVisualObject.hpp
	${SRCS_OBJECTS}
	${SRCS_BANKS}
	${SRCS_CONNEXION}
	${SRCS_MENU}
	${SRCS_ENGINE}
	${SRCS_GAME}
	)

# create executable
add_executable(bomberman ${SRCS})

# find irrlicht
find_package(Irrlicht REQUIRED)

if(MSVC)
	find_package(SFML 2.5.1 COMPONENTS audio REQUIRED)
endif()

#check if irrlicht found, if yes add irrlicht and encrypt tool to executable
if (Irrlicht_FOUND)
	target_include_directories(bomberman PUBLIC ${Irrlicht_INCLUDE_DIRS})
	target_link_libraries(bomberman ${Irrlicht_LIBRARIES} encrypt sfml-audio sfml-system)
else ()
	message(FATAL_ERROR "lib Irrlicht not found")
endif()

