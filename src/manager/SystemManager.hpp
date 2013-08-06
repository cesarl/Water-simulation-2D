#ifndef				__SYSTEM_MANAGER_HPP__
# define			__SYSTEM_MANAGER_HPP__

#include			<map>
#include			<allegro5/allegro.h>
#include			"Singleton.hpp"
#include			"EntityData.hpp"
#include			"ComponentManager.hpp"
#include			"System.hpp"

class				SystemManager : public Singleton<SystemManager>
{
public:

  void				add(System *sys);

  void				update(float time, const ALLEGRO_EVENT &ev);
  void				draw(float time, const ALLEGRO_EVENT &ev);

  template			<class T>
  T				*add(int priority, bool draw = false)
  {
    std::multimap<const char *, System *>::iterator it;
    T				*sys;

    it = map_.find(typeid(T).name());
    if (it != map_.end())
      return static_cast<T*>(it->second);
    sys = new T;
    if (!sys)
      throw OutOfMemory("Cannot allocate new System");
    map_.insert(std::pair<const char *, System *>(typeid(T).name(), sys));
    if (!draw)
      list_.insert(std::pair<int, System *>(priority, sys));
    else
      drawList_.insert(std::pair<int, System*>(priority, sys));
    sys->init();
    return sys;
  }

  template			<class T>
  T				*getSystem()
  {
    std::multimap<const char *, System *>::iterator it;

    it = map_.find(typeid(T).name());
    if (it != map_.end())
      return static_cast<T*>(it->second);
    return NULL;
  }

private:
  std::multimap<int, System*>	list_;
  std::multimap<const char *, System*> map_;
  std::multimap<int, System*>	drawList_;
private:
  SystemManager()
  {}

  virtual ~SystemManager()
  {
    std::multimap<int, System*>::iterator it;

    it = list_.begin();
    while (it != list_.end())
      {
	delete it->second;
	++it;
      }
  }
private:
  friend class Singleton<SystemManager>;
};

#endif				// __SYSTEM_MANAGER_HPP__
