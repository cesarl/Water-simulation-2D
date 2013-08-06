#ifndef				__COMPONENT_HPP__
# define			__COMPONENT_HPP__

static				int uniqueId()
{
  static int			id = 0;
  return id++;
}

template			<class T>
struct				Component
{
  static unsigned int		getTypeId()
  {
    static unsigned int		 id = uniqueId();
    return id;
  }
};


#endif				// __COMPONENT_HPP__
