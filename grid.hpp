#ifndef GRID_HPP
#define GRID_HPP

#include "display.hpp"

class Grid final {
public:
  Grid(const Display &display, const std::size_t grid_width, const std::size_t grid_height) noexcept;

  Grid() = delete;
  ~Grid() noexcept = default;
  Grid(const Grid &) = delete;
  Grid(Grid &&) noexcept = default;
  Grid &operator=(const Grid &) = delete;
  Grid &operator=(Grid &&) noexcept = default;

  auto cell_width() const noexcept -> std::size_t;
  auto cell_height() const noexcept -> std::size_t;
  auto width() const noexcept -> std::size_t;
  auto height() const noexcept -> std::size_t;

private:
  struct Impl;
  std::shared_ptr<Impl> impl;
};

auto draw(const Grid &grid, const Display &display, const std::uint8_t red, const std::uint8_t green,
          const std::uint8_t blue, const std::uint8_t alpha = 255) noexcept -> void;

auto draw_pixel_for(const Grid &grid, const Display &display, const std::int32_t x, const std::int32_t y,
                    const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue,
                    const std::uint8_t alpha = 255) noexcept -> void;

#endif // GRID_HPP
