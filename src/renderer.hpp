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

			static const unsigned int NLayer = 3;
			SpriteSet* layer[NLayer];
			float coeffLayer[NLayer];

		protected :
			void keyPressEvent(QKeyEvent* event);
			void keyReleaseEvent(QKeyEvent* event);

		public :
			Vect2D center;
			float scale;

			Renderer(int w, int h);
			~Renderer(void);

			// init methods :
			void removeLayer(unsigned int i);
			void setLayer(unsigned int i, const std::string&, float coeff);

			// Event Handling :
			void resizeGL(int w, int h);
			void begin(void);
			void end(void);

			// Primitive drawing :
			void draw(const Vect2D& pt, float radius=1.0f);
			void draw(const Segment& s);
			void draw(const SpriteSet& set, unsigned int sprite, const Vect2D& center, const Vect2D& diag, const Vect2D& loop = Vect2D(0.0,0.0));
			void drawBackground(void);

		signals :
			void keyPress(QKeyEvent* event);
			void keyRelease(QKeyEvent* event);
	};

#endif
