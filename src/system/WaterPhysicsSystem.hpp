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
						 WaterBox *wb,
						 float time)
  {
    glm::vec2 d = w2.pos - w1.pos;
    int distCenter = glm::length(d);
    float penetration = distCenter - ((int)wb->density * 2);
    Contact contact;

    if (distCenter == 0)
      {
	contact = Contact(glm::vec2(1, 0), -((int)wb->density * 2));
      }
    else
      contact = Contact(glm::normalize(d), penetration);

    glm::vec2 relV = w2.force - w1.force;
    float relNv = glm::dot(relV, contact.normal);
    float remove = relNv + contact.dist;// / time; /// dt // dt = le temp je coirs
    if (remove < 0)
      {
	float impulse = remove * 0.8f;
	w1.force += glm::vec2(contact.normal.x * (impulse * 1), contact.normal.y * (impulse * 1));
	w2.force -= glm::vec2(contact.normal.x * (impulse * 1), contact.normal.y * (impulse * 1));
      }

    (void)wb;
    (void)time;
  }
  
  virtual void			update(unsigned int entity, float time, const ALLEGRO_EVENT &)
  {
    WaterBox			*wb = ComponentManager::getInstance().getComponent<WaterBox>(entity);

    WaterBox::spIt		spIt = wb->spaceGrid.begin();
    while (spIt != wb->spaceGrid.end())
      {
	spIt->second.clear();
	++spIt;
      }

    unsigned int cellSize = wb->density * 5;
    glm::vec2 halfSize = glm::vec2(wb->density, wb->density) / 2.0f;

    for (unsigned int i = 0; i < wb->list.size(); ++i)
      {
	glm::vec2 from = wb->list[i].pos - halfSize;
	from /= cellSize;
	glm::vec2 to = wb->list[i].pos + halfSize;
	to /= cellSize;

	for (int h = from.x; h <= to.x; ++h)
	  {
	    for (int j = from.y; j <= to.y; ++j)
	      {
		wb->spaceGrid[h * 10000 + j].push_back(i);	
	      }
	  }
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

		if (i != j && d <= r)
		  {
		    resolveCollision(wb->list[spIt->second.at(i)], wb->list[spIt->second[j]], wb, time);
		  }
	      }
	  }
	++spIt;
      }

    unsigned int size = wb->list.size();
    unsigned int it;

    for (it = 0; it < size; ++it)
      {
	// glm::vec2 lastAcc = it->force;
	// it->pos += it->force * time + (0.5f * lastAcc * (time * time));
	// glm::vec2 avgAcc = (lastAcc + wb->worldForce) / 2.0f;
	// it->force += avgAcc * time;

	wb->list[it].force += wb->worldForce * time;
	wb->list[it].pos += wb->list[it].force * time;

	if (wb->list[it].pos.x < 0.0f || wb->list[it].pos.x > wb->dim.x)
	  {
	    wb->list[it].force.x *= -0.1f;
	    wb->list[it].pos.x = wb->list[it].pos.x < 0.0f ? 0.0f : wb->dim.x;
	  }
	if (wb->list[it].pos.y <= 0.0f || wb->list[it].pos.y >= wb->dim.y)
	  {
	    wb->list[it].force.y *= -0.1f;
	    wb->list[it].pos.y = wb->list[it].pos.y < 0.0f ? 0.0f : wb->dim.y;
	  }
      }
  }

private:
};

#endif				// __WATER_PHYSICS_SYSTEM_HPP__
