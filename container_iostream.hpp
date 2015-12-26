#ifndef _CONTAINERS_OSTREAM
#define _CONTAINERS_OSTREAM

#include <functional>
#include <iostream>
#include <utility>

// ostream overload for C++ standard containers

template <typename T0, typename T1>
inline std::ostream& operator<<(std::ostream& os, const std::pair<T0, T1>& p) {
  return os << '(' << p.first << ',' << p.second << ')';
}

template<size_t N>
struct print_tuple {
  template<typename... T>
  static typename std::enable_if<N >= sizeof...(T)>::type
  print(std::ostream& os, const std::tuple<T...>& t) {
  }

  template<typename... T>
  static typename std::enable_if<N + 1 < sizeof...(T)>::type
  print(std::ostream& os, const std::tuple<T...>& t) {
    os << std::get<N>(t) << ',';
    print_tuple<N + 1>::print(os, t);
  }

  template<typename... T>
  static typename std::enable_if<N + 1 == sizeof...(T)>::type
  print(std::ostream& os, const std::tuple<T...>& t) {
    os << std::get<N>(t);
  }
};

template <typename... T>
inline std::ostream& operator<<(std::ostream& os, const std::tuple<T...>& t) {
  os << '[';
  print_tuple<0>::print(os, t);
  return os << ']';
}

template <template <typename...> class TT, typename... T>
inline std::ostream& operator<<(std::ostream &os, const TT<T...> &xs) {
  os << '{';
  for (auto it = xs.begin(); it != xs.end();) {
    os << *(it++);
    if (it != xs.end())
      os << ',';
  }
  return os << '}';
}

#endif // _CONTAINERS_OSTREAM
