#ifndef				__COMPONENT_TYPE_MANAGER_HPP__
# define		        __COMPONENT_TYPE_MANAGER_HPP__

#include			<map>
#include			<typeinfo>
#include			"Singleton.hpp"
#include			"EntityData.hpp"

class				ComponentTypeManager : public Singleton<ComponentTypeManager>
{
public:
  template			<class T>
  unsigned int			getComponentType()
  {
    const char			*t = typeid(T).name();
    std::map<const char *, unsigned int>::iterator it;
    unsigned int		res = type_;

    it = list_.find(t);
    if (it == list_.end())
      {
	list_.insert(std::pair<const char *, unsigned int>(t, res));
	++type_;
	return res;
      }
    return it->second;
  }
private:
  unsigned int			type_;
  std::map<const char *, unsigned int> list_;
private:
  ComponentTypeManager() :
    type_(0)
  {}
  virtual ~ComponentTypeManager(){}
private:
  friend class Singleton<ComponentTypeManager>;
};

#endif				// __COMPONENT_TYPE_MANAGER_HPP__
