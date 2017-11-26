#include "display.hpp"
#include "Font.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <cmath>

namespace {
constexpr auto pi = 3.14159265359;

auto surface_from(const Font &font, const std::string &text, const std::size_t size, const std::uint8_t red,
                  const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha)
    -> std::shared_ptr<SDL_Surface>
{
  if (font.data() == nullptr) {
    throw std::runtime_error("Please load a font first via Display::font.");
  }
  SDL_RWops *ops = SDL_RWFromConstMem(font.data(), static_cast<std::int32_t>(font.data_size()));
  if (ops == nullptr) {
    throw std::runtime_error(SDL_GetError());
  }
  auto ttf = TTF_OpenFontRW(ops, 0, static_cast<std::int32_t>(size));
  if (ttf == nullptr) {
    throw std::runtime_error(TTF_GetError());
  }
  auto surface = TTF_RenderUTF8_Blended(ttf, text.c_str(), SDL_Color{red, green, blue, alpha});
  SDL_RWclose(ops);
  TTF_CloseFont(ttf);
  if (surface == nullptr) {
    throw std::runtime_error(TTF_GetError());
  }
  return std::shared_ptr<SDL_Surface>(surface, [](auto surface) { SDL_FreeSurface(surface); });
}

auto texture_from(SDL_Renderer *renderer, SDL_Surface *surface) -> std::shared_ptr<SDL_Texture>
{
  auto texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture == nullptr) {
    throw std::runtime_error(SDL_GetError());
  }
  return std::shared_ptr<SDL_Texture>(texture, [](auto texture) { SDL_DestroyTexture(texture); });
}

auto render(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect &rect)
{
  if (SDL_RenderCopy(renderer, texture, nullptr, &rect) < 0) {
    throw std::runtime_error(SDL_GetError());
  }
}
} // namespace

struct Display::Impl final {
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  Font font = Font();
  std::string title = "";
  std::size_t width = 0;
  std::size_t height = 0;

  ~Impl() noexcept
  {
    if (renderer != nullptr) {
      SDL_DestroyRenderer(renderer);
      renderer = nullptr;
    }
    if (window != nullptr) {
      SDL_DestroyWindow(window);
      window = nullptr;
    }
  }
};

Display::Display(std::string title, const std::size_t width, const std::size_t height) : impl(std::make_shared<Impl>())
{
  impl->title = std::move(title);
  impl->width = width;
  impl->height = height;
  impl->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  static_cast<int>(width), static_cast<int>(height), 0);
  if (impl->window == nullptr) {
    throw std::runtime_error(SDL_GetError());
  }
  impl->renderer = SDL_CreateRenderer(impl->window, -1, SDL_RENDERER_ACCELERATED);
  if (impl->window == nullptr) {
    throw std::runtime_error(SDL_GetError());
  }
  if (SDL_SetRenderDrawBlendMode(impl->renderer, SDL_BLENDMODE_BLEND) < 0) {
    throw std::runtime_error(SDL_GetError());
  }
}

const std::string &Display::title() const noexcept { return impl->title; }

auto Display::width() const noexcept -> std::size_t { return impl->width; }

auto Display::height() const noexcept -> std::size_t { return impl->height; }

auto Display::destroy() noexcept -> void { impl.reset(); }

auto Display::present() const noexcept -> void { SDL_RenderPresent(impl->renderer); }

auto Display::clear() const -> void
{
  if (SDL_RenderClear(impl->renderer) < 0) {
    throw std::runtime_error(SDL_GetError());
  }
}

auto Display::color(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue,
                    const std::uint8_t alpha) const -> void
{
  if (SDL_SetRenderDrawColor(impl->renderer, red, green, blue, alpha) < 0) {
    throw std::runtime_error(SDL_GetError());
  }
}

auto Display::font(const std::string &ttf_file) -> void { impl->font = Font(ttf_file); }

auto Display::point(const std::int32_t x, const std::int32_t y) const -> void
{
  if (SDL_RenderDrawPoint(impl->renderer, static_cast<int>(x), static_cast<int>(y)) < 0) {
    throw std::runtime_error(SDL_GetError());
  }
}

auto Display::line(const std::int32_t x1, const std::int32_t y1, const std::int32_t x2, const std::int32_t y2) const
    -> void
{
  if (SDL_RenderDrawLine(impl->renderer, static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2),
                         static_cast<int>(y2)) < 0) {
    throw std::runtime_error(SDL_GetError());
  }
}

auto Display::rectangle(const std::int32_t x, const std::int32_t y, const std::size_t width, const std::size_t height,
                        const bool fill) const -> void
{
  const auto rect = SDL_Rect{x, y, static_cast<std::int32_t>(width), static_cast<std::int32_t>(height)};
  if (fill) {
    if (SDL_RenderFillRect(impl->renderer, &rect) < 0) {
      throw std::runtime_error(SDL_GetError());
    }
    return;
  }
  if (SDL_RenderDrawRect(impl->renderer, &rect) < 0) {
    throw std::runtime_error(SDL_GetError());
  }
}

auto Display::circle(const std::int32_t x, const std::int32_t y, const std::size_t radius, const bool fill) const
    noexcept -> void
{
  if (fill) {
    // TODO(cwink) - Implement a stable algorithm for a filled circle.
  }
  for (auto angle = 0.0; angle < 2.0 * pi + 0.00001; angle += 1.0 / static_cast<double>(radius)) {
    point(x + static_cast<std::int32_t>(static_cast<double>(radius) * std::cos(angle)),
          y + static_cast<std::int32_t>(static_cast<double>(radius) * std::sin(angle)));
  }
}

auto Display::text(const std::string &text, const std::size_t size, const std::int32_t x, const std::int32_t y,
                   const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue,
                   const std::uint8_t alpha) const -> void
{
  auto surface = surface_from(impl->font, text, size, red, green, blue, alpha);
  auto texture = texture_from(impl->renderer, surface.get());
  auto rect = SDL_Rect{x, y, surface->w, surface->h};
  render(impl->renderer, texture.get(), rect);
}

auto Display::text_centered(const std::string &text, const std::size_t size, const std::uint8_t red,
                            const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha) const -> void
{
  auto surface = surface_from(impl->font, text, size, red, green, blue, alpha);
  auto texture = texture_from(impl->renderer, surface.get());
  auto x = static_cast<std::int32_t>((impl->width - static_cast<std::size_t>(surface->w)) / 2);
  auto y = static_cast<std::int32_t>((impl->height - static_cast<std::size_t>(surface->h)) / 2);
  auto rect = SDL_Rect{x, y, surface->w, surface->h};
  render(impl->renderer, texture.get(), rect);
}
