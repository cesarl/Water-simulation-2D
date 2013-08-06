#ifndef					__IMAGE_LOADER_HH__
# define				__IMAGE_LOADER_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				"Loader.hpp"
#include				"Image.hpp"

class					ImageLoader : public Loader<Image>
{
public:
  ImageLoader() : Loader<Image>()
  {
    // al_set_new_bitmap_flags(ALLEGRO_NO_PREMULTIPLIED_ALPHA);
  }

  virtual ~ImageLoader()
  {}
  virtual Image				*load(const File &file, bool force = false)
  {
    ALLEGRO_BITMAP			*bmp;
    GLuint				tex;

    bmp = al_load_bitmap(file.getFullName().c_str());
    if (!bmp)
      throw LoadingFailed(file.getFullName(), "ImageLoader failed to load image.");
    // al_convert_mask_to_alpha(bmp, al_map_rgb(255, 0, 0));
    tex = al_get_opengl_texture(bmp);
    if (tex == 0)
      throw LoadingFailed(file.getFullName(), "ImageLoader failed to load texture.");
    return new Image(bmp, tex, file.getFileName(), force);
  }
  virtual void				save(const Image *, const std::string &name)
  {
    throw LoadingFailed(name, "ImageLoader doesn't support SAVE.");
  }
};

#endif					// __IMAGE_LOADER_HH__
