CONFIG 		+= 	qt
QT           	+= 	opengl
HEADERS      	+= 	./src/vect2D.hpp \
			./src/MT4Header.hpp \
			./src/segment.hpp \
			./src/renderer.hpp \
			./src/world.hpp \
			./src/body.hpp \
			./src/game.hpp
SOURCES      	+= 	./src/main.cpp \
			./src/vect2D.cpp \
			./src/segment.cpp \
			./src/renderer.cpp \
			./src/world.cpp \
			./src/body.cpp \
			./src/game.cpp
