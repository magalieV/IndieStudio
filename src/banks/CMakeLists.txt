set(PATH_H
        inc/banks/)
set(PATH_S
        src/banks/)

set(SOURCES
        ${PATH_S}ButtonBank.cpp
        ${PATH_S}ObjectBank.cpp
        ${PATH_S}PictureBank.cpp
        ${PATH_S}FormBank.cpp
        )

set(HEADERS
        ${PATH_H}ButtonBank.hpp
        ${PATH_H}ObjectBank.hpp
        ${PATH_H}PictureBank.hpp
        ${PATH_H}FormBank.hpp
        )

set(BANKS_FILES
        ${SOURCES}
        ${HEADERS}
        )