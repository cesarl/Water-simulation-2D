#ifndef				__CORE_HPP__
# define			__CORE_HPP__

#include			"Singleton.hpp"

class				Core : public Singleton<Core>
{
private:
  Core(){}
  virtual ~Core(){}
private:
  friend class Singleton<Core>;
};

#endif				// __CORE_HPP__
