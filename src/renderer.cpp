#include "renderer.hpp"

	Renderer::Renderer(int w, int h)
	 : QGLWidget()
	{
		resize(w,h);
		show();

		// Set OpenGL states :
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
	}

	Renderer::~Renderer(void)
	{ }

	void Renderer::resizeGL(int w, int h)
	{
		std::cout << "resized to " << w << 'x' << h << std::endl;
		glViewport(0, 0, w, h);
	}

	void Renderer::apply(void)
	{
		swapBuffers();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
