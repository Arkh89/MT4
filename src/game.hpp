#ifndef __MT4_GAME__
#define __MT4_GAME__

	#include <QTimer>
	#include <QApplication>
	#include <QWidget>

	// Prototypes :
	class Renderer;
	class SpriteSet;
	class KeyLayout;

	// Class :
	class Game : public QApplication
	{
		Q_OBJECT

		private :
			QTimer* 	timer;
			Renderer* 	renderer;
			KeyLayout* 	keyLayout;

			SpriteSet*	spriteSet;

		public :
			Game(int& argc, char** argv, int w, int h, int fps);
			~Game(void);

		private slots :
			void update(void);
	};

#endif
