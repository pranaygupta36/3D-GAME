#include "cannonball.h"
#include "main.h"

Cannonball::Cannonball(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->g = 0.01;
    this->speed_x = 0;
    this->speed_y = 0;
    this->speed_z = 0;

    this->shape = Cube(x, y, z, .4, .4, .4, color);
        // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

}

void Cannonball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    this->shape.draw(MVP);
}

void Cannonball::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannonball::tick(int fire) {
    //std::cout<<"fire"<<fire<<std::endl;
    this->position.x += this->speed_x*cos(this->rotation*M_PI/180.0f);
    this->position.z -= this->speed_z*sin(this->rotation*M_PI/180.0f);
    this->position.y += this->speed_y;
    if (fire == 1) {
        if (this->position.y > -4.5) {
            this->speed_y -= this->g;
        }
        else {
            //std::cout<<"else me nahi ghusa"<<std::endl;
            this->speed_y = 0;
            this->speed_x = 0;
            this->speed_z = 0;
        }
    }
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
