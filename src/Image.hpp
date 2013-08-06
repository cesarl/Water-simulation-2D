#ifndef					__IMAGE_HH__
# define				__IMAGE_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				<GL/glu.h>
#include				"Resource.hh"
#include				"SmartPointer.hpp"
#include				"SmartPointerPolicies.hpp"
#include				"Vector3d.hh"

class					Image : public Resource
{
public:
  Image(ALLEGRO_BITMAP *bmp, GLuint tex, std::string const & name, bool force) :
    Resource(name, force),
    bmp_(bmp),
    tex_(tex)
  {
    displayList_ = glGenLists(1);
    glNewList(displayList_, GL_COMPILE);
    glBindTexture(GL_TEXTURE_2D, tex_);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0); // Top left hand corner
    glVertex3f(0.0, 0.0, 0.0); // X,Y,Z
    glTexCoord2f(1.0, 0.0); // Bottom left hand corner
    glVertex3f(1.0, 0.0, 0.0); // X,Y,Z
    glTexCoord2f(1.0, 1.0); // Bottom right hand corner
    glVertex3f(1.0, 1.0, 0.0); // X,Y,Z
    glTexCoord2f(0.0, 1.0); // Top right hand corner
    glVertex3f(0, 1.0, 0.0); // X,Y,Z
    glEnd();
    glEndList();
  };

  virtual void				operator=(Image & o)
  {
    if (this->bmp_)
      al_destroy_bitmap(this->bmp_);
    this->bmp_ = o.bmp_;
    this->tex_ = o.tex_;
    this->displayList_ = o.displayList_;
  }

  virtual ~Image()
  {
    if (this->bmp_)
      al_destroy_bitmap(this->bmp_);
    glDeleteTextures(1, &tex_);
    glDeleteLists(displayList_, 1);
  }

  const ALLEGRO_BITMAP			&getBitmap() const
  {
    return *bmp_;
  }

  GLuint				getTexture() const
  {
    return tex_;
  }

  GLuint				getDisplayList() const
  {
    return displayList_;
  }
private:
  ALLEGRO_BITMAP			*bmp_;
  GLuint				tex_;
  GLuint				displayList_;
};

typedef					SmartPtr<Image, InternalRef> ImagePtr;

#endif					// __IMAGE_HH__
