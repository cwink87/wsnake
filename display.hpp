#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <memory>

class Display final {
public:
  Display(std::string title, const std::size_t width, const std::size_t height);

  Display() = delete;
  ~Display() noexcept = default;
  Display(const Display &) = delete;
  Display(Display &&) noexcept = default;
  Display &operator=(const Display &) = delete;
  Display &operator=(Display &&) noexcept = default;

  const std::string &title() const noexcept;
  auto width() const noexcept -> std::size_t;
  auto height() const noexcept -> std::size_t;

  auto destroy() noexcept -> void;
  auto present() const noexcept -> void;
  auto clear() const -> void;
  auto color(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue,
             const std::uint8_t alpha = 255) const -> void;
  auto font(const std::string &ttf_file) -> void;
  auto point(const std::int32_t x, const std::int32_t y) const -> void;
  auto line(const std::int32_t x1, const std::int32_t y1, const std::int32_t x2, const std::int32_t y2) const -> void;
  auto rectangle(const std::int32_t x, const std::int32_t y, const std::size_t width, const std::size_t height,
                 const bool fill = false) const -> void;
  auto circle(const std::int32_t x, const std::int32_t y, const std::size_t radius, const bool fill = false) const
      noexcept -> void;
  auto text(const std::string &text, const std::size_t size, const std::int32_t x, const std::int32_t y,
            const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue,
            const std::uint8_t alpha = 255) const -> void;
  auto text_centered(const std::string &text, const std::size_t size, const std::uint8_t red, const std::uint8_t green,
                     const std::uint8_t blue, const std::uint8_t alpha = 255) const -> void;

private:
  struct Impl;
  std::shared_ptr<Impl> impl;
};

#endif // DISPLAY_HPP
