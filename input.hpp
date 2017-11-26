#ifndef INPUT_HPP
#define INPUT_HPP

#include <memory>

enum class Key {
  zero,
  one,
  two,
  three,
  four,
  five,
  six,
  seven,
  eight,
  nine,
  a,
  b,
  c,
  d,
  e,
  f,
  g,
  h,
  i,
  j,
  k,
  l,
  m,
  n,
  o,
  p,
  q,
  r,
  s,
  t,
  u,
  v,
  w,
  x,
  y,
  z,
  escape
};

class Event final {
public:
  Event() noexcept;

  ~Event() noexcept = default;
  Event(const Event &) = delete;
  Event(Event &&) noexcept = default;
  Event &operator=(const Event &) = delete;
  Event &operator=(Event &&) noexcept = default;

  auto poll() const noexcept -> void;
  auto is_closing() const noexcept -> bool;

private:
  struct Impl;
  std::shared_ptr<Impl> impl;
};

auto pressed(const Key &key) noexcept -> bool;

#endif // INPUT_HPP
