#ifndef __MT4_RENDERER__
#define __MT4_RENDERER__

	#include <QGLWidget>
	#include "segment.hpp"

	class Renderer : public QGLWidget
	{
		Q_OBJECT

		private :

		public :
			Renderer(int w, int h);
			~Renderer(void);

			// Event Handling :
			void resizeGL(int w, int h);
			void apply(void);

			// Primitive drawing :
			void draw(const Vect2D& pt);
			void draw(const Segment& s);
	};

#endif
