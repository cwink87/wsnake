#include "display.hpp"
#include "food.hpp"
#include "grid.hpp"
#include "input.hpp"
#include "snake.hpp"
#include "system.hpp"
#include "timestep.hpp"

int main()
{
  auto system = System();
  auto display = Display("Snake", 1024, 768);
  auto event = Event();
  auto grid = Grid(display, 32, 32);
  auto food = Food(grid);
  auto snake = Snake(grid, food);
  auto timestep = Timestep(150);

  display.font("../snake/rubik.ttf");

  auto game_over = false;
  auto score = 0;

  while (!event.is_closing() && !pressed(Key::escape)) {
    timestep.update();
    event.poll();

    if (pressed(Key::a)) {
      snake.direction(Direction::west);
    }
    if (pressed(Key::d)) {
      snake.direction(Direction::east);
    }
    if (pressed(Key::w)) {
      snake.direction(Direction::north);
    }
    if (pressed(Key::s)) {
      snake.direction(Direction::south);
    }

    while (timestep.accumulating()) {
      if (!game_over) {
        snake.move();
      }
      if (snake.hit_itself() || snake.out_of_bounds(grid)) {
        game_over = true;
        break;
      }
      if (snake.touched(food)) {
        snake.add_tail();
        food = Food(grid);
        ++score;
        timestep.delta_time(timestep.delta_time() - 2);
      }
      timestep.accumulate();
    }

    display.color(0, 0, 0);
    display.clear();

    draw(grid, display, 255, 255, 255, 64);
    draw(food, grid, display, 255, 0, 0);
    draw(snake, grid, display, 0, 255, 0);
    display.text("Score: " + std::to_string(score), 24, 5, 5, 255, 255, 255);

    if (game_over) {
      display.text_centered("Game Over", 72, 255, 255, 255);
    }

    display.present();
    delay_for(1);
  }

  display.destroy();
  system.terminate();
  return 0;
}
