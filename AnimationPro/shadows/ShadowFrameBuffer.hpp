//
//  ShadowFrameBuffer.hpp
//  AnimationPro
//
//  Created by 陈主润 on 06/06/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef ShadowFrameBuffer_hpp
#define ShadowFrameBuffer_hpp

#include <iostream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include "../utils/Utils.hpp"


class ShadowFrameBuffer {
    
private:
    
    void initialFrameBuffer();
    GLuint createFrameBuffer();
    GLuint createDepthBufferAttachment();
    
    void bindFrameBuffer(GLuint fbo, int width, int height);
    
    
    int WIDTH;
    int HEIGHT;
    
    GLuint FBO;
    GLuint shadowMap;
    
    
public:
    ShadowFrameBuffer(int width, int height);
    
    void bindFrameBuffer();
    void unbindFrameBuffer();
    
    GLuint getShadowMap();
    

};

#endif /* ShadowFrameBuffer_hpp */
