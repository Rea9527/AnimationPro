//
//  Animation.cpp
//  AnimationPro
//
//  Created by 陈主润 on 18/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "Animation.hpp"


Animation::Animation() {
    start_time = end_time = priority = 0;
}

Animation::Animation(string in_name, glm::vec2 times, int in_priority) {
    name = in_name;
    start_time = times.x;
    end_time = times.y;
    priority = in_priority;
}
