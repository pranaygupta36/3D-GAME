#include "enemy.h"
#include "main.h"

Enemy::Enemy(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    this->pieces[0] = Cube(x, y, z, 0.4, 2, 0.5, color);
    this->pieces[1] = Cube(x, y, z + 0.7, 0.4, 2, 0.5, color);
    this->pieces[2] = Cube(x, y + 2, z, 0.4, 1.75, 1.2, color);
    this->pieces[3] = Cube(x, y + 3.75, z+ 0.4, 0.4, 0.4, 0.4, color);
    this->pieces[4] = Cube(x, y + 3.25, z, 0.4, 1, 0.5, color);//hand l
    this->pieces[4].rotation = -90;
    this->pieces[5] = Cube(x, y + 3.75, z + 1.2, 0.4, 1, 0.5, color);//hand r
    this->pieces[5].rotation = 90;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    this->pieces[0].draw(MVP);
    this->pieces[1].draw(MVP);
    this->pieces[2].draw(MVP);
    this->pieces[3].draw(MVP);
    this->pieces[4].draw(MVP);
    this->pieces[5].draw(MVP);
}

void Enemy::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Enemy::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
