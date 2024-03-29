#include "main.h"
#include "cube.h"

#ifndef MAN_H
#define MAN_H


class Man {
public:
    Man() {}
    Man(float x, float y, float z, color_t color);
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

#endif // MAN_H
