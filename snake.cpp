#include "snake.hpp"
#include "system.hpp"
#include <list>

struct Snake::Impl final {
  std::list<Body_part> body = std::list<Snake::Body_part>();
  Direction direction = Direction::north;
  char padding[4] = {0};
};

Snake::Snake(const Grid &grid, const Food &food) : impl(std::make_shared<Impl>())
{
  auto min_x = static_cast<std::int32_t>(grid.width()) / 4;
  auto min_y = static_cast<std::int32_t>(grid.height()) / 4;
  auto max_x = static_cast<std::int32_t>(grid.width()) - min_x;
  auto max_y = static_cast<std::int32_t>(grid.height()) - min_y;
  auto part = Body_part{random<std::int32_t>(min_x, max_x), random<std::int32_t>(min_y, max_y)};
  if (part.x == food.x() && part.y == food.y()) {
    part.x -= 1;
    part.y -= 1;
  }
  impl->body.push_front(part);
}

auto Snake::draw(const Grid &grid, const Display &display, const std::uint8_t red, const std::uint8_t green,
                 const std::uint8_t blue, const std::uint8_t alpha) const noexcept -> void
{
  for (const auto &part : impl->body) {
    draw_pixel_for(grid, display, part.x, part.y, red, green, blue, alpha);
  }
}

auto Snake::direction(const Direction &direction) const noexcept -> void
{
  if ((direction == Direction::north && impl->direction == Direction::south) ||
      (direction == Direction::south && impl->direction == Direction::north) ||
      (direction == Direction::east && impl->direction == Direction::west) ||
      (direction == Direction::west && impl->direction == Direction::east)) {
    return;
  }
  impl->direction = direction;
}

auto Snake::move() const noexcept -> void
{
  auto v_x = 0;
  auto v_y = 0;
  switch (impl->direction) {
  case Direction::north:
    v_y = -1;
    break;
  case Direction::south:
    v_y = 1;
    break;
  case Direction::east:
    v_x = 1;
    break;
  case Direction::west:
    v_x = -1;
    break;
  }
  const auto x = impl->body.front().x + v_x;
  const auto y = impl->body.front().y + v_y;
  impl->body.push_front(Body_part{x, y});
  impl->body.pop_back();
}

auto Snake::touched(const Food &food) const noexcept -> bool
{
  const auto x = impl->body.front().x;
  const auto y = impl->body.front().y;
  return x == food.x() && y == food.y();
}

auto Snake::out_of_bounds(const Grid &grid) const noexcept -> bool
{
  const auto x = impl->body.front().x;
  const auto y = impl->body.front().y;
  return x < 0 || y < 0 || x >= static_cast<std::int32_t>(grid.width()) ||
         y >= static_cast<std::int32_t>(grid.height());
}

auto Snake::add_tail() const noexcept -> void
{
  auto v_x = 0;
  auto v_y = 0;
  switch (impl->direction) {
  case Direction::north:
    v_y = 1;
    break;
  case Direction::south:
    v_y = -1;
    break;
  case Direction::east:
    v_x = -1;
    break;
  case Direction::west:
    v_x = 1;
    break;
  }
  const auto x = impl->body.front().x + v_x;
  const auto y = impl->body.front().y + v_y;
  impl->body.push_back(Body_part{x, y});
}

auto Snake::hit_itself() const noexcept -> bool
{
  auto i = std::cbegin(impl->body);
  ++i;
  for (auto j = std::cend(impl->body); i != j; ++i) {
    if (impl->body.front().x == i->x && impl->body.front().y == i->y) {
      return true;
    }
  }
  return false;
}

auto draw(const Snake &snake, const Grid &grid, const Display &display, const std::uint8_t red,
          const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha) noexcept -> void
{
  snake.draw(grid, display, red, green, blue, alpha);
}
