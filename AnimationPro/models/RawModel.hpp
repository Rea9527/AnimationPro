//
//  RawModel.hpp
//  CGHws
//
//  Created by 陈主润 on 20/04/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef RawModel_hpp
#define RawModel_hpp

#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>

class RawModel {
public:
    RawModel();
    RawModel(GLuint vaoid, GLsizei count);
    GLuint getVAO();
    GLsizei getVertexCount();
    
private:
    GLuint vaoID;
    GLsizei vertexCount;
};

#endif /* RawModel_hpp */
