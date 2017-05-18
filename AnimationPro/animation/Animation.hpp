//
//  Animation.hpp
//  AnimationPro
//
//  Created by 陈主润 on 18/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef Animation_hpp
#define Animation_hpp

#include <iostream>
#include "../utils/Utils.hpp"


class Animation {
public:
    std::string name;
    float start_time;
    float end_time;
    int priority;
    
    Animation();
    
    Animation(string in_name, glm::vec2 times, int in_priority);
};

#endif /* Animation_hpp */
