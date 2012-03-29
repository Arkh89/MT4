CONFIG 		+= 	qt
QT           	+= 	opengl
HEADERS      	+= 	./src/vect2D.hpp \
			./src/exception.hpp \
			./src/MT4Header.hpp \
			./src/segment.hpp \
			./src/sprite.hpp \
			./src/renderer.hpp \
			./src/world.hpp \
			./src/body.hpp \
			./src/keyLayout.hpp \
			./src/game.hpp
SOURCES      	+= 	./src/main.cpp \
			./src/exception.cpp \
			./src/vect2D.cpp \
			./src/segment.cpp \
			./src/sprite.cpp \
			./src/renderer.cpp \
			./src/world.cpp \
			./src/body.cpp \
			./src/keyLayout.cpp \
			./src/game.cpp
