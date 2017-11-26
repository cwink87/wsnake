#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "food.hpp"

enum class Direction { north, south, east, west };

class Snake final {
public:
  Snake(const Grid &grid, const Food &food);

  Snake() = delete;
  ~Snake() noexcept = default;
  Snake(const Snake &) noexcept = default;
  Snake(Snake &&) noexcept = default;
  Snake &operator=(const Snake &) noexcept = default;
  Snake &operator=(Snake &&) noexcept = default;

  auto draw(const Grid &grid, const Display &display, const std::uint8_t red, const std::uint8_t green,
            const std::uint8_t blue, const std::uint8_t alpha = 255) const noexcept -> void;
  auto direction(const Direction &direction) const noexcept -> void;
  auto move() const noexcept -> void;
  auto touched(const Food &food) const noexcept -> bool;
  auto out_of_bounds(const Grid &grid) const noexcept -> bool;
  auto add_tail() const noexcept -> void;
  auto hit_itself() const noexcept -> bool;

private:
  struct Body_part {
    std::int32_t x;
    std::int32_t y;
  };

  struct Impl;
  std::shared_ptr<Impl> impl;
};

auto draw(const Snake &snake, const Grid &grid, const Display &display, const std::uint8_t red,
          const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha = 255) noexcept -> void;

#endif // SNAKE_HPP
