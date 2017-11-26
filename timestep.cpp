#include "timestep.hpp"
#include <SDL.h>

struct Timestep::Impl final {
  double time = 0.0;
  double delta_time = 0.0;
  double current_time = 0.0;
  double accumulator = 0.0;
};

Timestep::Timestep(const double delta_time) noexcept : impl(std::make_shared<Impl>()) { impl->delta_time = delta_time; }

auto Timestep::delta_time() const noexcept -> double { return impl->delta_time; }

auto Timestep::delta_time(const double delta_time) const noexcept -> void { impl->delta_time = delta_time; }

auto Timestep::update() const noexcept -> void
{
  const auto new_time = static_cast<double>(SDL_GetTicks());
  const auto frame_time = new_time - impl->current_time;
  impl->current_time = new_time;
  impl->accumulator += frame_time;
}

auto Timestep::accumulating() const noexcept -> bool { return impl->accumulator >= impl->delta_time; }

auto Timestep::accumulate() const noexcept -> void
{
  impl->accumulator -= impl->delta_time;
  impl->time += impl->delta_time;
}
