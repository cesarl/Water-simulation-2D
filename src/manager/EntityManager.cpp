#include			"EntityManager.hpp"
#include			"SystemManager.hpp"

#define				RESERVE_ENTITY (100)

unsigned int			EntityManager::newEntity()
{
  unsigned int		res;

  // std::cout << "++ " << idCounter_ << std::endl;
  if (freeIds_.empty())
    {
      if (list_.size() <= idCounter_)
	{
	  std::cout << "Resize list of size " << list_.size() << " -> " << idCounter_ + RESERVE_ENTITY << std::endl;
	  list_.resize(idCounter_ + RESERVE_ENTITY);
	}
      list_[idCounter_] = EntityData(idCounter_, true);
      list_[idCounter_] = true;
      res = idCounter_;
      ++idCounter_;
      return res;
    }
  res = freeIds_.back();
  freeIds_.pop_back();
  list_[res].active = true;
  return res;
}

void				EntityManager::eraseEntity(unsigned int id)
{
  list_[id].components.reset();
  list_[id].active = false;
  freeIds_.push_back(id);
  // std::cout << id << std::endl;
}

EntityData			&EntityManager::getEntityData(unsigned int id)
{
  return list_[id];
}


