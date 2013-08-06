#ifndef				__WATER_BOX_COMPONENT_HPP__
# define			__WATER_BOX_COMPONENT_HPP__

# define			GLM_FORCE_INLINE
# define			GLM_FORCE_RADIANS
#include			<glm/glm.hpp>
#include			<list>
#include			"Component.hpp"

struct				WaterParticle
{
  glm::vec2			pos;
  glm::vec2			force;

  WaterParticle() :
    pos(glm::vec2(0.0f, 0.0f)),
    force(glm::vec2(0.0f, 0.0f))
  {}

  WaterParticle(const WaterParticle &o)    
  {
    pos = o.pos;
    force = o.force;
  }

  WaterParticle			&operator=(const WaterParticle &o)
  {
    pos = o.pos;
    force = o.force;
    return *this;
  }
};

struct				WaterBox : public Component<WaterBox>
{
  glm::vec2			pos;
  glm::vec2			dim;
  glm::vec2			center;
  unsigned int			nbrOfPart;	//number of particles
  unsigned int			density;	//space between particles
  glm::vec2			worldForce;	// gravity
  std::vector<WaterParticle>	list;
  std::map<unsigned int, std::vector<unsigned int> > spaceGrid;
  typedef std::vector<WaterParticle>::iterator iterator;
  typedef std::map<unsigned int, std::vector<unsigned int> >::iterator spIt;
  typedef std::vector<unsigned int>::iterator cellIt;

  WaterBox() :
    pos(glm::vec2(0.0f, 0.0f)),
    dim(glm::vec2(0.0f, 0.0f)),
    center(glm::vec2(0.0f, 0.0f)),
    nbrOfPart(0),
    density(0),
    worldForce(glm::vec2(0.0f, 0.0f))
  {}

  void				set(const glm::vec2 & _pos, const glm::vec2 & _dim, unsigned int _n = 100)
  {
    pos = _pos;
    dim = _dim;
    center = pos + dim / 2.0f;
    nbrOfPart = _n;
    list.resize(nbrOfPart);

    std::vector<WaterParticle>::iterator it = list.begin();
    while (it != list.end())
      {
	(*it).pos = glm::vec2(float(rand() % (int)dim.x), float(rand() % (int)dim.y));
	++it;
      }

    std::cout << pos.x << " " << pos.y << std::endl;
    std::cout << dim.x << " " << dim.y << std::endl;
    std::cout << center.x << " " << center.y << std::endl;
  }

  void				setPhysics(const glm::vec2 & _worldForce, float _density)
  {
    worldForce = _worldForce;
    density = _density;
    for (unsigned int i = 0; i < (dim.x * dim.y) / (density * 5); ++i)
      {
	spaceGrid.insert(std::pair<unsigned int, std::vector<unsigned int> >((i % (int)density * 10000) + i / (int)density, std::vector<unsigned int>()));
      }
  }
};

#endif				// __WATER_BOX_COMPONENT_HPP__
