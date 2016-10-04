//
// Created by geronimo on 03/10/16.
//

#include <glew.h>
#include "camera.h"

camera::camera() {
//Defaults não muito burros...
    setEyePosition(0,0,-1);
    setFocusPosition(0,0,0);
    setViewUp(0,1,0);
    view = glm::lookAt(eyePosition, focusPosition, upVector);
    projection = glm::perspective<GLfloat>(45, 1, 0.1f, 100.f);
}

void camera::setEyePosition(float x, float y, float z) {
    this->eyePosition = glm::vec3(x,y,z);
}

void camera::setFocusPosition(float x, float y, float z) {
    this->focusPosition = glm::vec3(x,y,z);
}

void camera::setViewUp(float x, float y, float z) {
    this->upVector = glm::vec3(x,y,z);
}

glm::mat4 camera::getViewPerspectiveMatrix() {
    view = glm::lookAt(eyePosition, focusPosition, upVector);
    glm::mat4 vp = projection * view;
    return vp;
}
