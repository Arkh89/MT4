#include "renderer.hpp"

	Renderer::Renderer(int w, int h)
	 : QGLWidget(), center(0.0,0.0), scale(1.0)
	{
		resize(w,h);
		show();

		// Set OpenGL states :
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	Renderer::~Renderer(void)
	{ }

	void Renderer::keyPressEvent(QKeyEvent* event)
	{
		emit keyPress(event); //Syntaxe Qt
	}

	void Renderer::keyReleaseEvent(QKeyEvent* event)
	{
		emit keyRelease(event); //Syntaxe Qt
	}

	void Renderer::resizeGL(int w, int h)
	{
		std::cout << "resized to " << w << 'x' << h << std::endl;
		glViewport(0, 0, w, h);
		scaleY = static_cast<float>(w)/static_cast<float>(h);
	}

	void Renderer::apply(void)
	{
		swapBuffers();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glScalef(scale,scaleY*scale,1.0);
		glTranslatef(center.x, center.y,0.0);
	}

	void Renderer::draw(const Vect2D& pt)
	{
		glBegin(GL_POINTS);
			glColor3ub(255,0,0);
			glVertex2f(pt.x,pt.y);
		glEnd();
	}

	void Renderer::draw(const Segment& s)
	{
		glBegin(GL_LINES);
			glColor3ub(255,255,0);
			glVertex2f(s.getX1(), s.getY1());
			glColor3ub(255,0,255);
			glVertex2f(s.getX2(), s.getY2());
		glEnd();

		Vect2D 	mid = s.getCenter(),
			e = mid + s.getNormalVector()/5.0;

		glBegin(GL_LINES);
			glColor3ub(0,0,255);
			glVertex2f(mid.x, mid.y);
			glColor3ub(255,255,255);
			glVertex2f(e.x, e.y);
		glEnd();
	}

	void Renderer::draw(const SpriteSet& set, unsigned int sprite, const Vect2D& center, const Vect2D& diag)
	{
		const SpriteRect& rect = set.getSpriteRect(sprite);

		set.bind();
		glBegin(GL_QUADS);
			glColor3ub(255,255,255); //reset filter to white

			glTexCoord2f(rect.getULC().x,rect.getULC().y);
			glVertex2f(center.x-diag.x/2.0f, center.y+diag.y/2.0f);

			glTexCoord2f(rect.getLRC().x,rect.getULC().y);
			glVertex2f(center.x+diag.x/2.0f, center.y+diag.y/2.0f);

			glTexCoord2f(rect.getLRC().x,rect.getLRC().y);
			glVertex2f(center.x+diag.x/2.0f, center.y-diag.y/2.0f);

			glTexCoord2f(rect.getULC().x,rect.getLRC().y);
			glVertex2f(center.x-diag.x/2.0f, center.y-diag.y/2.0f);
		glEnd();
	}
