#include "sprite.hpp"
#include "exception.hpp"

	SpriteRect::SpriteRect(const Vect2D& _ulc, const Vect2D& _lrc)
	 : ulc(_ulc), lrc(_lrc)
	{ }

	const Vect2D& SpriteRect::getULC(void) const
	{
		return ulc;
	}

	const Vect2D& SpriteRect::getLRC(void) const
	{
		return lrc;
	}

	SpriteSet::SpriteSet(const std::string& filename)
	{
		// Add a parameter to control transparency color :
		const unsigned char 	rTrans = 0,
					gTrans = 0,
					bTrans = 0;

		QImage img(filename.c_str());

		if(img.isNull())
			throw Exception("SpriteSet::SpriteSet - Cannnot load sprite set " + filename + ".", __FILE__, __LINE__);

		glEnable(GL_TEXTURE_2D);

		glGenTextures(1, &texID);

		glBindTexture(GL_TEXTURE_2D,texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT );

		w = img.width();
		h = img.height();

		unsigned char* temp = new unsigned char[w*h*4]; //RGBA
		int t=0;

		for(int i=0; i<h; i++)
		{
			for(int j=0; j<w; j++)
			{
				QRgb col 	= img.pixel(j,i);
				temp[t+0] 	= static_cast<unsigned char>( qRed( col ) );
				temp[t+1] 	= static_cast<unsigned char>( qGreen( col ) );
				temp[t+2] 	= static_cast<unsigned char>( qBlue( col ) );
				if(temp[t+0]==rTrans && temp[t+1]==gTrans && temp[t+2]==bTrans)
					temp[t+3] = 0;
				else
					temp[t+3] = 255;

				//temp[t+0]	= (i%2)*(j%2)*255;
				//temp[t+1]	= (1-i%2)*(j%2)*255;
				//temp[t+2]	= (i%2)*(1-j%2)*255;
				//temp[t+3]	= 255;
				t += 4;
			}
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, temp);

		unbind();

		delete[] temp;
	}

	SpriteSet::~SpriteSet(void)
	{
		glDeleteTextures( 1, &texID);
	}

	unsigned int SpriteSet::getWidth(void) const
	{
		return w;
	}

	unsigned int SpriteSet::getHeight(void) const
	{
		return h;
	}

	unsigned int SpriteSet::declareSprite(unsigned int xULC, unsigned int yULC, unsigned int xLRC, unsigned int yLRC)
	{
		Vect2D 	a(static_cast<float>(xULC)/static_cast<float>(w),static_cast<float>(yULC)/static_cast<float>(h)),
			b(static_cast<float>(xLRC)/static_cast<float>(w),static_cast<float>(yLRC)/static_cast<float>(h));

		//std::cout << a << " " << b << std::endl;

		sprites.push_back(SpriteRect(a,b));

		return sprites.size()-1;
	}

	std::vector<unsigned int> SpriteSet::declareSpriteSerie(unsigned int xSize, unsigned int ySize, unsigned int xOffset, unsigned int yOffset, unsigned int xStride, unsigned int yStride)
	{
		std::vector<unsigned int> indexes;

		unsigned int 	nW = (w-xOffset)/(xSize+xStride),
				nH = (h-yOffset)/(ySize+yStride);

		for(unsigned int i=0; i<nH; i++)
			for(unsigned int j=0; j<nW; j++)
			{
				float 	xA = static_cast<float>(xOffset+j*(xSize+xStride))/static_cast<float>(w),
					yA = static_cast<float>(yOffset+i*(ySize+yStride))/static_cast<float>(h),
					xB = static_cast<float>(xOffset+(j+1)*(xSize+xStride))/static_cast<float>(w),
					yB = static_cast<float>(yOffset+(i+1)*(ySize+yStride))/static_cast<float>(h);
				sprites.push_back(SpriteRect(Vect2D(xA,yA),Vect2D(xB,yB)));
				indexes.push_back(sprites.size()-1);
			}

		return indexes;
	}

	unsigned int SpriteSet::getNumImages(void) const
	{
		return sprites.size();
	}

	const SpriteRect& SpriteSet::getSpriteRect(unsigned int i) const
	{
		if(i>=getNumImages())
			throw Exception("SpriteSet::getSpriteRect - Index out of range.", __FILE__, __LINE__);
		else
			return sprites[i];
	}

	void SpriteSet::bind(void) const
	{
		glBindTexture(GL_TEXTURE_2D, texID);
	}

	void SpriteSet::unbind(void)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
