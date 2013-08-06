#ifndef				__ENTITY_DATA_HPP__
# define			__ENTITY_DATA_HPP__

#include			<bitset>
#include			<string>
#include			"Exception.hh"

#define				TAG_LENGTH (32)
#define				LAYER_LENGTH (32)
#define				DEFAULT_TAG ("Default")
#define				DEFAULT_LAYER ("Default")

struct				EntityData
{
  std::bitset<64>		components;
  unsigned int			id;
  bool				active;
private:
  std::string			tag;
  std::string			layer;

public:
  EntityData(unsigned int entityId = 0,
	     bool active = false,
	     const std::string & _tag = DEFAULT_TAG,
	     const std::string & _layer = DEFAULT_LAYER)
  {
    components.reset();
    id = entityId;
    active = active;
    if (_tag.size() > TAG_LENGTH)
      {
	throw TagToLong(entityId, _tag, true);    
      }
    tag = _tag;
    if (_layer.size() > LAYER_LENGTH)
      {
	throw TagToLong(entityId, _layer, false);    
      }
    layer = _layer;
  }

  EntityData			&operator=(const EntityData &o)
  {
    components = o.components;
    id = o.id;
    active = o.active;
    tag = o.tag;
    layer = o.layer;
    return *this;
  }

  std::string			&getTag()
  {
    return tag;
  }

  std::string			&getLayer()
  {
    return layer;
  }

  void				setTag(const std::string & _tag)
  {
    tag = _tag;
  }

  void				setLayer(const std::string & _layer)
  {
    layer = _layer;
  }


};

#endif				// __ENTITY_DATA_HPP__
