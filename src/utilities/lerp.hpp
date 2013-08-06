#ifndef				__LERP_HPP__
# define			__LERP_HPP_

namespace			Utils
{
  template			<typename T, typename D>
  static const			T lerp(T src, T dest, D duration, D time)
  {
    // return src + (dest - src) * delta;
    // return (src * (1.0 - (time / duration)) + time / duration * dest);
    return (src + (dest - src) * (time / duration));
  }
};
#endif				// __LERP_HPP__
