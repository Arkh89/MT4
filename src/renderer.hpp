#ifndef __MT4_RENDERER__
#define __MT4_RENDERER__

	#include <QGLWidget>
	#include "vect2D.hpp"
	#include "segment.hpp"
	#include "sprite.hpp"

	class Renderer : public QGLWidget
	{
		Q_OBJECT

		private :
			float scaleY;

		protected :
			void keyPressEvent(QKeyEvent* event);
			void keyReleaseEvent(QKeyEvent* event);

		public :
			Vect2D center;
			float scale;

			Renderer(int w, int h);
			~Renderer(void);

			// Event Handling :
			void resizeGL(int w, int h);
			void apply(void);

			// Primitive drawing :
			void draw(const Vect2D& pt);
			void draw(const Segment& s);
			void draw(const SpriteSet& set, unsigned int sprite, const Vect2D& center, const Vect2D& diag);

		signals :
			void keyPress(QKeyEvent* event);
			void keyRelease(QKeyEvent* event);
	};

#endif
