#ifndef __MT4_SPRITE__
#define __MT4_SPRITE__

	#include <string>
	#include <QImage>
	#include <QtOpenGL/QGLWidget>
	#include "vect2D.hpp"

	class SpriteRect
	{
		private :
			Vect2D ulc,lrc;
		public :
			SpriteRect(const Vect2D& _ulc, const Vect2D& _lrc);
			const Vect2D& getULC(void) const;
			const Vect2D& getLRC(void) const;
	};

	class SpriteSet
	{
		private :
			unsigned int w,h;
			GLuint texID;
			std::vector<SpriteRect> sprites;

		public :
			SpriteSet(const std::string& filename);
			~SpriteSet(void);

			unsigned int getWidth(void) const;
			unsigned int getHeight(void) const;

			unsigned int declareUniqueSprite(void);
			unsigned int declareSprite(unsigned int xULC, unsigned int yULC, unsigned int xLRC, unsigned int yLRC);
			std::vector<unsigned int> declareSpriteSerie(unsigned int xSize, unsigned int ySize, unsigned int xOffset=0, unsigned int yOffset=0, unsigned int xStride=0, unsigned int yStride=0);
			unsigned int getNumImages(void) const;

			const SpriteRect& getSpriteRect(unsigned int i) const;
			void bind(void) const;
			static void unbind(void);
	};

#endif
