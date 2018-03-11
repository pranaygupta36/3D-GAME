#include "main.h"
#include "cube.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float acclr_y;
    float speed_y;
    float g;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    int life;
    int score;
    Cube sides[20];
private:
    VAO *object;
};

#endif // BOAT_H
