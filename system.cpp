#include "system.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdexcept>

System::System()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    throw std::runtime_error(SDL_GetError());
  }
  if (TTF_Init() < 0) {
    throw std::runtime_error(TTF_GetError());
  }
}

System::~System() noexcept { terminate(); }

auto System::terminate() const noexcept -> void
{
  SDL_Quit();
  TTF_Quit();
}

auto delay_for(const std::size_t milliseconds) -> void { SDL_Delay(static_cast<Uint32>(milliseconds)); }
