#ifndef				__WATER_PHYSICS_SYSTEM_HPP__
# define			__WATER_PHYSICS_SYSTEM_HPP__

#include			<glm/gtx/vector_angle.hpp>

#include			"System.hpp"
#include			"ComponentManager.hpp"
#include			"Components.hpp"

class				WaterPhysicsSystem : public System
{
public:
  virtual ~WaterPhysicsSystem(){};
  WaterPhysicsSystem()
  {}
  void				init()
  {
    require<WaterBox>();
  }

  void				resolveCollision(WaterParticle & w1,
						 WaterParticle & w2,
						 WaterBox *wb)
  {
    // glm::vec2 direction = w2.pos - w1.pos;
    // float distance = glm::length(direction);
    // glm::normalize(direction);
    // float depth = (wb->density + wb->density) - distance;
    // glm::vec2 d = depth * direction;

    // if (depth > 0)
    //   {
    // 	glm::vec2 halfDepth = d / 2.0f;
    // 	w1.pos -= halfDepth;
    // 	w2.pos += halfDepth;
    //   }

    // --------------------------------------

    glm::vec2 d = w1.pos - w2.pos;
    float angle = glm::atan(d.y, d.x);

    float speed1 = sqrt(w1.force.x * w1.force.x + w1.force.y * w1.force.y);
    float speed2 = sqrt(w2.force.x * w2.force.x + w2.force.y * w2.force.y);

    float dir1 = glm::atan(w1.force.y, w1.force.x);
    float dir2 = glm::atan(w2.force.y, w2.force.x);

    float vx_1 = speed1 * glm::cos(dir1 - angle);
    float vy_1 = speed1 * glm::sin(dir1 - angle);
    float vx_2 = speed2 * glm::cos(dir2 - angle);
    float vy_2 = speed2 * glm::sin(dir2 - angle);

    float vx1 = 0 * vx_1 + 2 * vx_2 / 2;
    float vx2 = 2 * vx_1 + 0 * vx_2 / 2;
    float vy1 = vy_1;
    float vy2 = vy_2;

    w1.force.x = glm::cos(angle) * vx1 + glm::cos(angle + M_PI / 2) * vy1;
    w1.force.y = glm::sin(angle) * vx1 + glm::sin(angle + M_PI / 2) * vy1;
    w2.force.x = glm::cos(angle) * vx2 + glm::cos(angle + M_PI / 2) * vy2;
    w2.force.y = glm::sin(angle) * vx2 + glm::sin(angle + M_PI / 2) * vy2;
    

    // ----------------------------------------------------

    // glm::vec2 d = w1.pos - w2.pos;
    // float angle = atan2(d.y, d.x);
    // float dir1 = atan2(w1.force.y, w1.force.x);
    // float dir2 = atan2(w2.force.y, w2.force.x);
    // w1.force.x = cos(dir1 - angle);
    // w1.force.y = sin(dir1 - angle);
    // w2.force.x = cos(dir2 - angle);
    // w2.force.y = sin(dir2 - angle);


    (void)wb;
  }
  
  virtual void			update(unsigned int entity, float time, const ALLEGRO_EVENT &)
  {
    WaterBox			*wb = ComponentManager::getInstance().getComponent<WaterBox>(entity);
    WaterBox::iterator		it = wb->list.begin();

    WaterBox::spIt		spIt = wb->spaceGrid.begin();
    while (spIt != wb->spaceGrid.end())
      {
	spIt->second.clear();
	++spIt;
      }

    for (unsigned int i = 0; i < wb->list.size(); ++i)
      {
	// wb->spaceGrid[(int)wb->list[i].pos.x / (int)wb->density % (int)wb->density * 10000
	// 	      + wb->list[i].pos.y / (int)wb->density / (int)wb->density].push_back(i);
	wb->spaceGrid[0].push_back(i);
      }

    spIt = wb->spaceGrid.begin();
    float r = (wb->density + wb->density) * (wb->density + wb->density);
    while (spIt != wb->spaceGrid.end())
      {
	for (unsigned int i = 0; i < spIt->second.size(); ++i)
	  {
	    for (unsigned int j = i + 1; j < spIt->second.size(); ++j)
	      {
		float dx = wb->list[spIt->second.at(i)].pos.x - wb->list[spIt->second.at(j)].pos.x;
		float dy = wb->list[spIt->second.at(i)].pos.y - wb->list[spIt->second.at(j)].pos.y;
		float d = dx * dx + dy * dy;
		// float d = glm::distance(wb->list[spIt->second.at(i)].pos, wb->list[spIt->second[j]].pos);

		if (i != j && d <= r)
		  {
		    // std::cout << "col  : " << i << " " << j << std::endl;
		    resolveCollision(wb->list[spIt->second.at(i)], wb->list[spIt->second[j]], wb);
		  }
	      }
	  }
	++spIt;
      }

    while (it != wb->list.end())
      {
	// glm::vec2 lastAcc = it->force;
	// it->pos += it->force * time + (0.5f * lastAcc * (time * time));
	// glm::vec2 avgAcc = (lastAcc + wb->worldForce) / 2.0f;
	// it->force += avgAcc * time;

	it->force += wb->worldForce * time;
	it->pos += it->force * time;

	// glm::vec2 lastAcc = it->force;
	// it->force = wb->worldForce * time;
	// it->pos += it->force * time + (0.5f * lastAcc * (time * time));


	if (it->pos.x < 0.0f || it->pos.x > wb->dim.x)
	  {
	    it->force.x *= -0.1f;
	    it->pos.x = it->pos.x < 0.0f ? 0.0f : wb->dim.x;
	  }
	if (it->pos.y <= 0.0f || it->pos.y >= wb->dim.y)
	  {
	    it->force.y *= -0.1f;
	    it->pos.y = it->pos.y < 0.0f ? 0.0f : wb->dim.y;
	  }

	++it;
      }
    
    // *color = Utils::lerp<Color>(eas->colorOrigin, eas->color, eas->duration, eas->time);

    // eas->time = (float)eas->time + time;
    // if (eas->time >= eas->duration)
    //   ComponentManager::getInstance().removeComponent<ColorEasing>(entity);

    (void)time;
    (void)entity;
  }

private:
};

#endif				// __WATER_PHYSICS_SYSTEM_HPP__
