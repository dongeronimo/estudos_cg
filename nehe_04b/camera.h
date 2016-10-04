//
// Created by geronimo on 03/10/16.
//

#ifndef ESTUDOSCG_CAMERA_H
#define ESTUDOSCG_CAMERA_H
#include <glm/gtc/matrix_transform.hpp>
#include <glm/detail/type_mat.hpp>
/*
 * Uma câmera é responsável pela matriz de projeção e de visão (look-at).
 * Ela provê meios de mudar o look at da câmera e suas propriedades de
 * projeção.*/
class camera {
private:
    glm::vec3 eyePosition, focusPosition, upVector;
    glm::mat4 projection;
    glm::mat4 view;
public:
    camera();
    void setEyePosition(float x, float y, float z);
    void setFocusPosition(float x, float y, float z);
    void setViewUp(float x, float y, float z);
    glm::mat4 getViewPerspectiveMatrix();
//    glm::mat4 projection = glm::perspective<GLfloat>(45, 1, 0.1f, 100.f);
//    glm::mat4 view = glm::lookAt(glm::vec3(1, 10, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
};


#endif //ESTUDOSCG_CAMERA_H
