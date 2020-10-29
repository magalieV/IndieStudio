set(PATH_H
        inc/connexion/)
set(PATH_S
        src/connexion/)

set(SOURCES
        ${PATH_S}ConnexionBoard.cpp
        ${PATH_S}Signup.cpp
        ${PATH_S}Login.cpp
        )

set(HEADERS
        ${PATH_H}ConnexionBoard.hpp
        ${PATH_H}Signup.hpp
        ${PATH_H}Login.hpp
        ${PATH_H}ConnexionHandle.hpp
        )

set(CONNEXION_FILES
        ${SOURCES}
        ${HEADERS}
        )