set(PATH_H
        inc/Engine/)
set(PATH_S
        src/Engine/)

set(SOURCES
        ${PATH_S}Core.cpp
        ${PATH_S}Window.cpp
        ${PATH_S}EventHandler.cpp
        ${PATH_S}GenerateMap.cpp
        ${PATH_S}CollisionSystem.cpp
        ${PATH_S}PathFinder.cpp
        ${PATH_S}AError.cpp
        ${PATH_S}LoadError.cpp
        )

set(HEADERS
        ${PATH_H}Core.hpp
        ${PATH_H}Window.hpp
        ${PATH_H}EventHandler.hpp
        ${PATH_H}CollisionSystem.hpp
        ${PATH_H}GenerateMap.hpp
        ${PATH_H}PathFinder.hpp
        ${PATH_H}AError.hpp
        ${PATH_H}LoadError.hpp
        )

set(ENGINE_FILES
        ${SOURCES}
        ${HEADERS}
        )