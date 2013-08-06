#ifndef				__ENTITY_MANAGER_HPP__
# define			__ENTITY_MANAGER_HPP__

#include			<vector>
#include			<bitset>
#include			<allegro5/allegro.h>
#include			"Singleton.hpp"
#include			"EntityData.hpp"

class				EntityManager : public Singleton<EntityManager>
{
public:
  typedef std::vector<EntityData>::iterator iterator;

  unsigned int			newEntity();
  void				eraseEntity(unsigned int id);
  EntityData			&getEntityData(unsigned int id);

  unsigned int			end()
  {
    return list_.size();
  }

  std::vector<EntityData>	&getList()
  {
    return list_;
  }
private:
  unsigned int			idCounter_;
  std::vector<EntityData>	list_;
  std::vector<unsigned int>	freeIds_;
private:
  friend class Singleton<EntityManager>;
  EntityManager(): idCounter_(1)
  {
  };
  virtual ~EntityManager(){};
};

#endif				// __ENTITY_MANAGER_HPP__
