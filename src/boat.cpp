#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->acclr_y = 0.2;
    this->g = 0.1;
    this->speed_y = 0;
    this->score = 0;
    speed = 0;
    this->life = 150;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->sides[0] = Cube(-1, 0, 0, 2, 1.45, 0.2, color);
    this->sides[0].rotation = -30;
    this->sides[1] = Cube(-1, 0, 0, 2, 1.52, 0.2, color);
    this->sides[1].rotation = 29;
    this->sides[2] = Cube(-1, 0, 0, 0.1, 1.48, 0.2, color); //back
    this->sides[3] = Cube(-1, 0, 0, 0.1, 1.45, 0.2, color); //back
    this->sides[3].rotation = -22;
    this->sides[4] = Cube(-1, 0, 0, 0.1, 1.5, 0.2, color);
    this->sides[4].rotation = 22;
    this->sides[5] = Cube(0.9, 0, 0, 0.1, 1.48, 0.2, color);
    this->sides[6] = Cube(0.9, 0, 0, 0.1, 1.45, 0.2, color);
    this->sides[6].rotation = -22;
    this->sides[7] = Cube(0.9, 0, 0, 0.1, 1.5, 0.2, color);
    this->sides[7].rotation = 22;
    this->sides[8] = Cube(0.9, 0, 0, 0.1, 1.45, 0.2, color);
    this->sides[8].rotation = -14;
    this->sides[9] = Cube(0.9, 0, 0, 0.1, 1.5, 0.2, color);
    this->sides[9].rotation = 14;
    this->sides[10] = Cube(0.9, 0, 0, 0.1, 1.45, 0.2, color);
    this->sides[10].rotation = -6;
    this->sides[11] = Cube(0.9, 0, 0, 0.1, 1.5, 0.2, color);
    this->sides[11].rotation = 6;
    this->sides[12] = Cube(-1, 0, 0, 0.1, 1.45, 0.2, color);
    this->sides[12].rotation = -14;
    this->sides[13] = Cube(-1, 0, 0, 0.1, 1.5, 0.2, color);
    this->sides[13].rotation = 14;
    this->sides[14] = Cube(-1, 0, 0, 0.1, 1.45, 0.2, color);
    this->sides[14].rotation = -6;
    this->sides[15] = Cube(-1, 0, 0, 0.1, 1.5, 0.2, color);
    this->sides[15].rotation = 6;
    this->sides[16] = Cube(-1, 1.5, 0, 1.9, 1.5, 0.1, COLOR_YELLOW);

}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotat0
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    for (int i=0;i<17; this->sides[i++].draw(MVP));
}
void Boat::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {
    //this->rotation += speed;
    this->position.y += speed_y;
    if(this->position.y > -2) {
        this->speed_y -= this->g;
    }
    else {
        //this->acclr_y = 5;
        this->speed_y = 0;
        this->position.y = -2;
    }
    // this->position.x -= speed;

}

