#include <SDL2/SDL.h>

namespace jd {
enum button {select, left_axis, right_axis, start, up, left, down, right, l2, r2, l1, r1, triangle, circle, cross, rectangle, logo};

void init();

bool handleEvents(SDL_Event& event);

inline int right_axis_x = 0, right_axis_y = 0, left_axis_x = 0, left_axis_y = 0;
inline bool no_controller_at_start = false;

int getPercentageLevel();
}
