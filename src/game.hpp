#ifndef __MT4_GAME__
#define __MT4_GAME__

	#include <QTimer>
	#include <QApplication>
	#include <QWidget>

	// Prototypes :
	class Renderer;
	class SpriteSet;
	class KeyLayout;
	class SoundEngine;
	class Sound;
        class SoundSource;

	// Class :
	class Game : public QApplication
	{
		Q_OBJECT

		private :
			QTimer* 	timer;
			Renderer* 	renderer;
			KeyLayout* 	keyLayout;
			SoundEngine*	soundEngine;

			SpriteSet*	spriteSet;
			Sound		*jump, *coin;

		public :
			Game(int& argc, char** argv, int w, int h, int fps);
			~Game(void);

		private slots :
			void update(void);
	};

#endif
