#ifndef __MT4_GAME__
#define __MT4_GAME__

	#include <QTimer>
	#include <QApplication>

	// Prototypes :
	class Renderer;

	// Class :
	class Game : public QApplication
	{
		Q_OBJECT

		private :
			QTimer* timer;
			Renderer* renderer;

		public :
			Game(int& argc, char** argv, int w, int h, int fps);
			~Game(void);

		private slots :
			void update(void);
	};

#endif
