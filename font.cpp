#include "font.hpp"
#include <SDL.h>

struct Font::Impl final {
  std::uint8_t *data = nullptr;
  std::size_t data_size = 0;

  ~Impl() noexcept
  {
    if (data != nullptr) {
      delete[] data;
      data = nullptr;
      data_size = 0;
    }
  }
};

Font::Font(const std::string &ttf_file) : Font() { load(ttf_file); }

Font::Font() noexcept : impl(std::make_shared<Impl>()) {}

const std::uint8_t *Font::data() const noexcept { return impl->data; }

auto Font::data_size() const noexcept -> std::size_t { return impl->data_size; }

auto Font::load(const std::string &ttf_file) const -> void
{
  if (impl->data != nullptr) {
    delete[] impl->data;
  }
  auto ops = SDL_RWFromFile(ttf_file.c_str(), "rb");
  if (ops == nullptr) {
    throw std::runtime_error(SDL_GetError());
  }
  impl->data_size = static_cast<std::size_t>(SDL_RWsize(ops));
  impl->data = new std::uint8_t[impl->data_size];
  SDL_RWread(ops, impl->data, impl->data_size, 1);
  SDL_RWclose(ops);
}
