#include "renderer.hpp"
#include "exception.hpp"

    Renderer::Renderer(int w, int h)
     : QGLWidget(), center(0.0,0.0), scale(1.0)
    {
        memset(layer,0,NLayer*sizeof(void*));
        memset(coeffLayer,0,NLayer*sizeof(float));

        resize(w,h);
        show();

        // Set OpenGL states :
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    Renderer::~Renderer(void)
    {
        for(unsigned int i=0; i<NLayer; i++)
            removeLayer(i);
    }

    void Renderer::keyPressEvent(QKeyEvent* event)
    {
        emit keyPress(event); //Syntaxe Qt
    }

    void Renderer::keyReleaseEvent(QKeyEvent* event)
    {
        emit keyRelease(event); //Syntaxe Qt
    }

    void Renderer::removeLayer(unsigned int i)
    {
        if(i>=NLayer)
            throw Exception("Renderer::setLayer - Index out of range.",__FILE__,__LINE__);

        delete layer[i];
        layer[i] = NULL;
    }

    void Renderer::setLayer(unsigned int i, const std::string& filename, float coeff)
    {
        if(i>=NLayer)
            throw Exception("Renderer::setLayer - Index out of range.",__FILE__,__LINE__);

        if(layer[i]!=NULL)
            delete layer[i];

        layer[i] = new SpriteSet(filename);

        layer[i]->declareUniqueSprite();

        coeffLayer[i] = coeff;
    }

    void Renderer::resizeGL(int w, int h)
    {
        std::cout << "resized to " << w << 'x' << h << std::endl;
        glViewport(0, 0, w, h);
        scaleY = static_cast<float>(w)/static_cast<float>(h);
    }

    void Renderer::begin(void)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glScalef(scale,scaleY*scale,1.0);
        glTranslatef(center.getX(), center.getY(),0.0);
    }

    void Renderer::end(void)
    {
        swapBuffers();
    }

    void Renderer::draw(const Vect2D& pt)
    {
        glBegin(GL_POINTS);
            glColor3ub(255,0,0);
            glVertex2f(pt.getX(),pt.getY());
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
            glVertex2f(mid.getX(), mid.getY());
            glColor3ub(255,255,255);
            glVertex2f(e.getX(), e.getY());
        glEnd();
    }

    void Renderer::draw(const SpriteSet& set, unsigned int sprite, const Vect2D& center, const Vect2D& diag, const Vect2D& loop)
    {
        const SpriteRect& rect = set.getSpriteRect(sprite);

        set.bind();
        glBegin(GL_QUADS);
            glColor3ub(255,255,255); //reset filter to white

            glTexCoord2f(rect.getULC().getX()+loop.getX(),rect.getULC().getY()+loop.getY());
            glVertex2f(center.getX()-diag.getX()/2.0f, center.getY()+diag.getY()/2.0f);

            glTexCoord2f(rect.getLRC().getX()+loop.getX(),rect.getULC().getY()+loop.getY());
            glVertex2f(center.getX()+diag.getX()/2.0f, center.getY()+diag.getY()/2.0f);

            glTexCoord2f(rect.getLRC().getX()+loop.getX(),rect.getLRC().getY()+loop.getY());
            glVertex2f(center.getX()+diag.getX()/2.0f, center.getY()-diag.getY()/2.0f);

            glTexCoord2f(rect.getULC().getX()+loop.getX(),rect.getLRC().getY()+loop.getY());
            glVertex2f(center.getX()-diag.getX()/2.0f, center.getY()-diag.getY()/2.0f);
        glEnd();
    }

    void Renderer::drawBackground(void)
    {
        for(unsigned int i=0; i<NLayer; i++)
        {
            if(layer[i]!=NULL)
                draw(*layer[i], 0, -center, Vect2D(2.0,2.0), center*coeffLayer[i]);
        }
    }

