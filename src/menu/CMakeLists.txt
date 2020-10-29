set(PATH_H
 inc/menu/)

set(PATH_S
 src/menu/)

set(SOURCES
		${PATH_S}Menu.cpp
	    ${PATH_S}MenuPlay.cpp
	)

set(HEADERS
		${PATH_H}Menu.hpp
	    ${PATH_H}MenuPlay.hpp
	    ${PATH_H}PlayHandle.hpp
		)

set(MENU_FILES
		${SOURCES}
		${HEADERS}
		)