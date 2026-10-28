#pragma once
#include "scene2/component.h"

struct [[export]] PlayerController : public Component {
    [[export]] float speed = 2.0f;
    [[export]] float bob_speed = 3.0f;
    [[export]] float bob_height = 0.05f;
};
