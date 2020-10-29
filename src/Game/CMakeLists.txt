set(PATH_H
        inc/Game/)
set(PATH_S
        src/Game/)

set(SOURCES
        ${PATH_S}ChoosePlayer.cpp
        ${PATH_S}CreateBoard.cpp
        ${PATH_S}Game.cpp
        ${PATH_S}Intro.cpp
        ${PATH_S}Pause.cpp
        ${PATH_S}EndGame.cpp
        ${PATH_S}ChoosePlayerNumber.cpp
        ${PATH_S}MultiplayerGame.cpp
        ${PATH_S}SplashScreen.cpp
        )

set(HEADERS
        ${PATH_H}ChoosePlayer.hpp
        ${PATH_H}CreateBoard.hpp
        ${PATH_H}Game.hpp
        ${PATH_H}Intro.hpp
        ${PATH_H}Pause.hpp
        ${PATH_H}EndGame.hpp
        ${PATH_H}ChoosePlayerNumber.hpp
        ${PATH_H}MultiplayerGame.hpp
        ${PATH_H}SplashScreen.hpp
        )

set(GAME_FILES
        ${SOURCES}
        ${HEADERS}
        )