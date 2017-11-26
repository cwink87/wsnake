#include "food.hpp"
#include "system.hpp"

struct Food::Impl final {
  std::int32_t x;
  std::int32_t y;
};

Food::Food(const Grid &grid) noexcept : impl(std::make_shared<Impl>())
{
  impl->x = random<std::int32_t>(0, static_cast<std::int32_t>(grid.width()) - 1);
  impl->y = random<std::int32_t>(0, static_cast<std::int32_t>(grid.height()) - 1);
}

auto Food::x() const noexcept -> std::int32_t { return impl->x; }

auto Food::y() const noexcept -> std::int32_t { return impl->y; }

auto draw(const Food &food, const Grid &grid, const Display &display, const std::uint8_t red, const std::uint8_t green,
          const std::uint8_t blue, const std::uint8_t alpha) noexcept -> void
{
  draw_pixel_for(grid, display, food.x(), food.y(), red, green, blue, alpha);
}
