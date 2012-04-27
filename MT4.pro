CONFIG 				+= 	qt
QT           			+= 	opengl network

win32:		INCLUDEPATH     +=      ./ext/openal-soft-1.14-bin/include

win32:		LIBS  		+=	../MT4/ext/openal-soft-1.14-bin/lib/Win32/libOpenAL32.dll.a
else:unix:	LIBS 		+=	-lopenal

HEADERS      			+= 	./src/vect2D.hpp \
					./src/vector.hpp \
					./src/exception.hpp \
					./src/MT4Header.hpp \
					./src/segment.hpp \
					./src/sprite.hpp \
					./src/renderer.hpp \
					./src/world.hpp \
					./src/body.hpp \
					./src/keyLayout.hpp \
					./src/soundEngine.hpp \
					./src/color.hpp \
					./src/network.hpp \
					./src/game.hpp
SOURCES      			+= 	./src/main.cpp \
					./src/exception.cpp \
					./src/segment.cpp \
					./src/vect2D.cpp \
					./src/sprite.cpp \
					./src/renderer.cpp \
					./src/world.cpp \
					./src/body.cpp \
					./src/keyLayout.cpp \
					./src/soundEngine.cpp \
					./src/color.cpp \
					./src/network.cpp \
					./src/game.cpp
