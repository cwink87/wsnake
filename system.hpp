#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <chrono>
#include <random>

class System final {
public:
  System();
  ~System() noexcept;

  System(const System &) = delete;
  System(System &&) noexcept = default;
  System &operator=(const System &) = delete;
  System &operator=(System &&) noexcept = default;

  auto terminate() const noexcept -> void;
};

auto delay_for(const std::size_t milliseconds) -> void;

template <typename Type>
auto random(const Type lower, const Type upper) -> std::enable_if_t<std::is_floating_point<Type>::value, Type>
{
  std::random_device rd;
  static auto mt = std::mt19937(rd());
  mt.seed(static_cast<std::int32_t>(std::chrono::system_clock::now().time_since_epoch().count()));
  auto distribution = std::uniform_real_distribution<Type>(lower, upper);
  return distribution(mt);
}

template <typename Type>
auto random(const Type lower, const Type upper) -> std::enable_if_t<std::is_integral<Type>::value, Type>
{
  std::random_device rd;
  auto mt = std::mt19937(rd());
  mt.seed(static_cast<std::int32_t>(std::chrono::system_clock::now().time_since_epoch().count()));
  auto distribution = std::uniform_int_distribution<Type>(lower, upper);
  return distribution(mt);
}

#endif // SYSTEM_HPP
