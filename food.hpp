#ifndef FOOD_HPP
#define FOOD_HPP

#include "grid.hpp"

class Food final {
public:
  explicit Food(const Grid &grid) noexcept;

  ~Food() noexcept = default;
  Food(const Food &) noexcept = default;
  Food(Food &&) noexcept = default;
  Food &operator=(const Food &) noexcept = default;
  Food &operator=(Food &&) noexcept = default;

  auto x() const noexcept -> std::int32_t;
  auto y() const noexcept -> std::int32_t;

private:
  struct Impl;
  std::shared_ptr<Impl> impl;
};

auto draw(const Food &food, const Grid &grid, const Display &display, const std::uint8_t red, const std::uint8_t green,
          const std::uint8_t blue, const std::uint8_t alpha = 255) noexcept -> void;

#endif // FOOD_HPP
