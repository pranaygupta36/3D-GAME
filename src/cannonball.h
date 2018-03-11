#include "main.h"
#include "cube.h"

#ifndef CANNONBALL_H
#define CANNONBALL_H


class Cannonball {
public:
    Cannonball() {}
    Cannonball(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(int fire);
    double speed_x;
    double speed_y;
    double speed_z;
    double g;
    Cube shape;
private:
    VAO *object;
};

#endif // CANNONBALL_H
