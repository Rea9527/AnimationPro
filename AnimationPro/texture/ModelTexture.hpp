//
//  ModelTexture.hpp
//  glfwTest
//
//  Created by 陈主润 on 21/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef ModelTexture_hpp
#define ModelTexture_hpp

#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>


class ModelTexture {
    
public:
    ModelTexture();
    ModelTexture(GLuint textureId);
    GLuint getId();
    
private:
    GLuint TextureId;
};


#endif /* ModelTexture_hpp */
