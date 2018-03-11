#include "main.h"
#include "cube.h"

#ifndef ROCKS_H
#define ROCKS_H


class Rock {
public:
    Rock() {}
    Rock(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    Cube pieces[3];
private:
    VAO *object;
};

#endif // ROCKS_H
