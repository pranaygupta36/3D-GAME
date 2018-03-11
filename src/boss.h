#include "main.h"
#include "cube.h"

#ifndef BOSS_H
#define BOSS_H


class Boss {
public:
    Boss() {}
    Boss(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    int life;
    double speed;
    Cube pieces[6];
private:
    VAO *object;
};

#endif // BOSS_H
