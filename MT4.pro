CONFIG 		+= 	qt
QT           	+= 	opengl
LIBS		+=	-lopenal\
			-lsndfile
HEADERS      	+= 	./src/vect2D.hpp \
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
			./src/game.hpp
SOURCES      	+= 	./src/main.cpp \
			./src/exception.cpp \
			./src/segment.cpp \
			./src/vect2D.cpp \
			./src/sprite.cpp \
			./src/renderer.cpp \
			./src/world.cpp \
			./src/body.cpp \
			./src/keyLayout.cpp \
			./src/soundEngine.cpp \
			./src/game.cpp

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../openal-soft-1.14-bin/lib/Win32 -libOpenAL32
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../openal-soft-1.14-bin/lib/Win32 -libOpenAL32d

#INCLUDEPATH += $$PWD/../openal-soft-1.14-bin/include
#DEPENDPATH += $$PWD/../openal-soft-1.14-bin/include


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Windows/Utilitaires/libsndfile/lib/ -llibsndfile-1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Windows/Utilitaires/libsndfile/lib/ -llibsndfile-1d

INCLUDEPATH += $$PWD/../../Windows/Utilitaires/libsndfile/include
DEPENDPATH += $$PWD/../../Windows/Utilitaires/libsndfile/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Windows/Utilitaires/"OpenAL 1.1 SDK"/libs/Win64/ -lOpenAL32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Windows/Utilitaires/"OpenAL 1.1 SDK"/libs/Win64/ -lOpenAL32d

INCLUDEPATH += $$PWD/../../Windows/Utilitaires/"OpenAL 1.1 SDK"/libs/Win64
DEPENDPATH += $$PWD/../../Windows/Utilitaires/"OpenAL 1.1 SDK"/libs/Win64
