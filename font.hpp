#ifndef FONT_HPP
#define FONT_HPP

#include <memory>

class Font final {
public:
  explicit Font(const std::string &ttf_file);
  Font() noexcept;

  ~Font() noexcept = default;
  Font(const Font &) noexcept = default;
  Font(Font &&) noexcept = default;
  Font &operator=(const Font &) noexcept = default;
  Font &operator=(Font &&) noexcept = default;

  const std::uint8_t *data() const noexcept;
  auto data_size() const noexcept -> std::size_t;

  auto load(const std::string &ttf_file) const -> void;

private:
  struct Impl;
  std::shared_ptr<Impl> impl;
};

#endif // FONT_HPP
