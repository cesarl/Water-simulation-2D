#ifndef				__WATER_RENDER_SYSTEM_HPP__
# define			__WATER_RENDER_SYSTEM_HPP__

#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"

// for dbug purpose
void				drawCircle(const glm::vec2 & pos, float radius)
{
  float num_segments = 8;
  float theta = 2 * 3.1415926 / (float)num_segments; 
  float c = cosf(theta);//precalculate the sine and cosine
  float s = sinf(theta);
  float t;

  float x = radius;//we start at angle = 0 
  float y = 0; 

  glBegin(GL_LINE_LOOP); 
  for(int ii = 0; ii < num_segments; ii++) 
    { 
      glVertex2f(x + pos.x, y + pos.y);//output vertex 
        
      //apply the rotation matrix
      t = x;
      x = c * x - s * y;
      y = s * t + c * y;
    } 
  glEnd(); 
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
	// glColor3f(it->force.y, - it->force.y, 1.0f);
    	drawCircle(it->pos, wb->density);
    	++it;
      }
    glPopMatrix();
    (void)entity;
  }

private:
};

#endif				// __WATER_RENDER_SYSTEM_HPP__
