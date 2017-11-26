#include "grid.hpp"

struct Grid::Impl final {
  std::size_t grid_width = 0;
  std::size_t grid_height = 0;
  std::size_t cell_width = 0;
  std::size_t cell_height = 0;
};

Grid::Grid(const Display &display, const std::size_t grid_width, const std::size_t grid_height) noexcept
    : impl(std::make_shared<Impl>())
{
  impl->grid_width = grid_width;
  impl->grid_height = grid_height;
  impl->cell_width = display.width() / grid_width;
  impl->cell_height = display.height() / grid_height;
}

auto Grid::cell_width() const noexcept -> std::size_t { return impl->cell_width; }

auto Grid::cell_height() const noexcept -> std::size_t { return impl->cell_height; }

auto Grid::width() const noexcept -> std::size_t { return impl->grid_width; }

auto Grid::height() const noexcept -> std::size_t { return impl->grid_height; }

auto draw(const Grid &grid, const Display &display, const std::uint8_t red, const std::uint8_t green,
          const std::uint8_t blue, const std::uint8_t alpha) noexcept -> void
{
  display.color(red, green, blue, alpha);
  for (std::int32_t x = 0; x < static_cast<std::int32_t>(display.width()); x += grid.cell_width()) {
    for (std::int32_t y = 0; y < static_cast<std::int32_t>(display.height()); y += grid.cell_height()) {
      display.rectangle(x, y, grid.cell_width(), grid.cell_height());
    }
  }
}

auto draw_pixel_for(const Grid &grid, const Display &display, const std::int32_t x, const std::int32_t y,
                    const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue,
                    const std::uint8_t alpha) noexcept -> void
{
  display.color(red, green, blue, alpha);
  display.rectangle(x * static_cast<std::int32_t>(grid.cell_width()), y * static_cast<std::int32_t>(grid.cell_height()),
                    grid.cell_width(), grid.cell_height(), true);
}
