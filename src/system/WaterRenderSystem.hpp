#ifndef				__WATER_RENDER_SYSTEM_HPP__
# define			__WATER_RENDER_SYSTEM_HPP__

#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"


// for dbug purpose
void				drawCircle(const glm::vec2 & pos, float radius)
{
  glPushMatrix();
  glTranslatef(pos.x, pos.y, 0.0f);
  glBegin(GL_LINE_LOOP);
  glColor3f(1.0f, 1.0f, 1.0f);
  for (int i = 0; i < 360; ++i)
    {
      float degInRad = i * 3.14159 / 180;
      glVertex2f(cos(degInRad) * radius, sin(degInRad) * radius);
    }
  glEnd();
  glPopMatrix();
}

class				WaterRenderSystem : public System
{
public:
  virtual ~WaterRenderSystem(){};
  WaterRenderSystem()
  {}
  void				init()
  {
    require<WaterBox>();
  }


  virtual void			update(unsigned int entity, float, const ALLEGRO_EVENT &)
  {
    WaterBox			*wb = ComponentManager::getInstance().getComponent<WaterBox>(entity);
    WaterBox::iterator		it = wb->list.begin();

    glPushMatrix();
    glTranslatef(wb->pos.x, wb->pos.y, 0.0f);
    while (it != wb->list.end())
      {
    	drawCircle(it->pos, wb->density);
    	++it;
      }
    glPopMatrix();
    (void)entity;
  }

private:
};

#endif				// __WATER_RENDER_SYSTEM_HPP__
