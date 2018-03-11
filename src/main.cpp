#include "main.h"
#include "timer.h"
#include "cube.h"
#include "boat.h"
#include "sea.h"
#include "rocks.h"
#include "cannon.h"
#include "cannonball.h"
#include "health.h"
#include "enemy.h"
#include "boss.h"
#include "man.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
int width;
int height;

float eye_x = -5.5;
float eye_y = 1;
float eye_z = 0;
float target_x = 0;
float target_y = -1.6;
float target_z = 0;


/**************************
* Customizable functions *
**************************/

Boat boat;
Sea sea;
Health cube;
Cube island;
Rock rocks[250];
Cannon cannon;
Cannonball cannonball;
Health hblocks[10];
Enemy enemies[20];
Boss boss[5];
Man man;
int nenemies = 20;
int nhblocks = 10;
int nrock = 250;
int fire = 0;
int nboss = 5;
int started = 0;
int hit[3] = {0};
int flag = 0;
int bflag = 0;
int flag2 = 0;
int boat_cam = 0;
int follow_cam = 0;
int tower_cam = 0;
int top_cam = 0;
int heli_cam = 0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float cam_x = -10;
float cam_y = 20;
float cam_z = 0;
Timer t60(1.0 / 60);

/* Render the scene with openGL *//* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    if(boat_cam == 1) {
        eye_x = man.position.x + 2.5*cos(man.rotation * M_PI/180.0);
        eye_y = man.position.y+1;
        eye_z = man.position.z - 2.5*sin(man.rotation * M_PI/180.0);

        target_x = man.position.x + 4*cos(man.rotation * M_PI/180.0);
        target_y = man.position.y;
        target_z = man.position.z - 4*sin(man.rotation * M_PI/180.0);

        // far = 50;
    }

    if(follow_cam == 1) {
        eye_x = man.position.x - 5*cos(man.rotation * M_PI/180.0);
        eye_y = man.position.y + 5;
        eye_z = man.position.z + 5*sin(man.rotation * M_PI/180.0);

        target_x = man.position.x;
        target_y = man.position.y;
        target_z = man.position.z;

        // far = 50;
    }

    if(tower_cam == 1) {
        eye_x = 100;
        eye_y = 20;
        eye_z = 0;

        target_x = man.position.x;
        target_y = man.position.y;
        target_z = man.position.z;

        // far = 150;
    }

    if(top_cam == 1) {
        eye_x = man.position.x - 5*cos(man.rotation * M_PI/180.0);
        eye_y = man.position.y + 20;
        eye_z = man.position.z + 5*sin(man.rotation * M_PI/180.0);

        target_x = man.position.x;
        target_y = man.position.y;
        target_z = man.position.z;

        // far = 50;
    }

    if(heli_cam == 1) {
        eye_x = cam_x ;
        eye_y = cam_y;
        eye_z = cam_z;

        target_x = man.position.x;
        target_y = man.position.y;
        target_z = man.position.z;

        // far = 50;
    }

    // Eye - Location of camera. Don't change unless you are sure!!
    //glm::vec3 eye (boat.position.x - 5*cos(boat.rotation*M_PI/180.0), boat.position.y+ 5, boat.position.z + 5*sin(boat.rotation*M_PI/180.0));
    glm::vec3 eye(eye_x, eye_y, eye_z);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    //glm::vec3 target (boat.position.x, boat.position.y , boat.position.z);
    glm::vec3 target(target_x, target_y, target_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    sea.draw(VP);

    boat.draw(VP);
    cannon.draw(VP);
    if (started == 1 && bflag == 1) for(int i=0;i<nboss;i++) boss[i].draw(VP);
    for(int i=0;i<nrock;rocks[i++].draw(VP));
    if (started == 1) for(int i=0;i<nhblocks;hblocks[i++].draw(VP));
    if (started == 1) for(int i=0;i<nenemies;enemies[i++].draw(VP));
    cube.draw(VP);
    if (fire == 1) cannonball.draw(VP);
    if (started == 1) island.draw(VP);
    man.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int f = glfwGetKey(window, GLFW_KEY_F);
    int o = glfwGetKey(window, GLFW_KEY_O);
    int p = glfwGetKey(window, GLFW_KEY_P);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int one = glfwGetKey(window, GLFW_KEY_1);
    int two = glfwGetKey(window, GLFW_KEY_2);
    int three = glfwGetKey(window, GLFW_KEY_3);
    int four = glfwGetKey(window, GLFW_KEY_4);
    int five = glfwGetKey(window, GLFW_KEY_5);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int x = glfwGetKey(window, GLFW_KEY_X);
    int z = glfwGetKey(window, GLFW_KEY_Z);
    if(one) {
        boat_cam = 1;
        follow_cam = 0;
        tower_cam = 0;
        top_cam = 0;
        heli_cam = 0;
    }

    if(two) {
        boat_cam = 0;
        follow_cam = 1;
        tower_cam = 0;
        top_cam = 0;
        heli_cam = 0;
    }

    if(three) {
        boat_cam = 0;
        follow_cam = 0;
        tower_cam = 1;
        top_cam = 0;
        heli_cam = 0;
    }

    if(four) {
        boat_cam = 0;
        follow_cam = 0;
        tower_cam = 0;
        top_cam = 1;
        heli_cam = 0;
    }

    if(five) {
        boat_cam = 0;
        follow_cam = 0;
        tower_cam = 0;
        top_cam = 0;
        heli_cam = 1;
    }
    if (left) {
        if(flag2 == 0) boat.rotation += 1;
        man.rotation += 1;
    }
    if (right) {
        if (flag2 == 0) boat.rotation -= 1;
        man.rotation -= 1;
        camera_rotation_angle -= 1;
    }
    if (up) {
        if(boat.position.x > -10 && boat.position.x < 280) {
            if(flag2 == 0) {
                boat.position.x += 0.3*cos(boat.rotation*M_PI/180.0f);
                boat.position.z -= 0.3*sin(boat.rotation*M_PI/180.0f);
            }
            man.position.x += 0.3*cos(man.rotation*M_PI/180.0f);
            man.position.z -= 0.3*sin(man.rotation*M_PI/180.0f);
        }
        else {
            if(boat.position.x > 0) boat.position.x = 278;
            if(boat.position.x < 0) boat.position.x = -9;
            man.position.x = boat.position.x;
            man.position.z = boat.position.z;
        }
    }
    if (down) {
        if(boat.position.x > -10 && boat.position.x < 280) {
            if (flag2==0) {
                boat.position.x -= 0.3*cos(boat.rotation*M_PI/180.0f);
                boat.position.z += 0.3*sin(boat.rotation*M_PI/180.0f);
            }
            man.position.x -= 0.3*cos(man.rotation*M_PI/180.0f);
            man.position.z += 0.3*sin(man.rotation*M_PI/180.0f);
        }
        else {
            if(boat.position.x > 0) boat.position.x = 278;
            if(boat.position.x < 0) boat.position.x = -9;
            man.position.x = boat.position.x;
            man.position.z = boat.position.z;
        }
    }
    if(o) {
        reset_screen();
    }
    if(p) {
        reshapeWindow (window, width, height);
    }
    if(space) {
        boat.speed_y += boat.acclr_y;
    }
    if (f && fire == 0) {
        //cout<<"hello"<<endl;
        fire = 1;
        cannonball.speed_x = 1;
        cannonball.speed_z = 1;
    }
    if(w) {
        cam_x += 0.3*cos(camera_rotation_angle*M_PI/180.0f);
        cam_z -= 0.3*sin(camera_rotation_angle*M_PI/180.0f);
    }
    if(s) {
        cam_x -= 0.3*cos(camera_rotation_angle*M_PI/180.0f);
        cam_z += 0.3*sin(camera_rotation_angle*M_PI/180.0f);
    }
    if(a) {
        camera_rotation_angle += 1;
    }
    if(d) {
        camera_rotation_angle += 1;
    }
    if (z) {
        if(cam_y < 45) cam_y += 1;
    }
    if (x) {
        if (cam_y > 5) cam_y -= 1;
    }

}

void tick_elements() {
    boat.tick();
    sea.tick();
    //camera_rotation_angle = man.rotation;
    // man things
    //cout<<man.position.x<<" "<<man.position.y<<" "<<man.position.z<<endl;
    if(flag2 == 0) {
        man.position.x = boat.position.x;
        man.position.z = boat.position.z;
        man.rotation = boat.rotation;
    }

    //camera_rotation_angle += 1;
    //hit rock to start playing
    if((abs(boat.position.x - rocks[0].position.x) < 2) && (abs(boat.position.z - rocks[0].position.z) < 2) && (abs(boat.position.y - rocks[0].position.y) < 2)) {
        for (int i=0;i<nrock;i++) rocks[i].position = glm::vec3 (rand()%200, -1.6, (rand()%400) - 200);
        rocks[0].position.y -= 100;
        for (int i=0;i<nhblocks;i++) hblocks[i].position = glm::vec3 (rand()%200, -1.6, (rand()%400) - 200);
        for (int i=0;i<nenemies;i++) enemies[i].position = glm::vec3 (rand()%200, -1.6, (rand()%400) - 200);
        for (int i=0;i<nboss;i++) boss[i].position = glm::vec3 (rand()%200 + 50, -1.6, (rand()%400) - 200);
        cube.position = glm::vec3(rand()%50 + 220, 2, rand()%50);
        island.position = glm::vec3(220, -2, 0);
        boat.life = 100;
        started = 1;
    }
    // rock collision
    for(int i=0;i<nrock;i++) {
        if((abs(boat.position.x - rocks[i].position.x) < 2) && (abs(boat.position.z - rocks[i].position.z) < 2) && abs(boat.position.y - rocks[i].position.y) < 2) {
            man.position.x -= 2*cos(boat.rotation*M_PI/180.0f);
            man.position.z += 2*sin(boat.rotation*M_PI/180.0f);
            boat.life -= 10;
        }
    }

    //cannon things
    cannon.rotation = boat.rotation;
    cannon.position = boat.position;

    //cannonball firings
    cannonball.rotation = boat.rotation;
    if (fire == 0) {
        cannonball.position = boat.position;
    }
    //cout<<cannonball.position.x<<" "<<cannonball.position.y<<" "<<cannonball.position.z<<endl;
    cannonball.tick(fire);
    if(cannonball.position.y < -4.5) {
        fire = 0;
        flag = 0;
    }
    //cannonball vs rock
    for(int i=0;i<nrock;i++) {
        hit[0] = 0;
        if((abs(cannonball.position.x - rocks[i].position.x) < 2) && (abs(cannonball.position.z - rocks[i].position.z) < 2) && cannonball.position.y - rocks[i].position.y < 2 && fire ==1 ) {
            rocks[i].position = glm::vec3 (rand()%200, -1.6, (rand()%400) - 200);
            boat.score += 10;
            hit[0] = 1;
            break;
        }
    }
    //cout<<"rock position"<<rocks[0].position.x<<" "<<rocks[0].position.z<<endl;

    //health block pickup
    //if((abs(boat.position.x - hblocks[0].position.x) < 2) && ((boat.position.z - hblocks[0].position.z) > -2)) for (int i=0;i<nhblocks;i++) hblocks[i].position = glm::vec3 (rand()%200, -1.6, (rand()%400) - 200);
    for(int i=0;i<nhblocks;i++) {
        if((abs(boat.position.x - hblocks[i].position.x) < 2) && (abs(boat.position.z - hblocks[i].position.z) < 2) && abs(boat.position.y - hblocks[i].position.y) < 2) {
            hblocks[i].position.y -= 1000;
            boat.life += 20;
            if (boat.life > 100) boat.life = 100;
        }
    }
    //enemy collision
    //if((abs(boat.position.x - enemies[0].position.x) < 2) && ((boat.position.z - enemies[0].position.z) > -3.75)) for (int i=0;i<nenemies;i++) enemies[i].position = glm::vec3 (rand()%200, -1.6, (rand()%400) - 200);
    for(int i=0;i<nenemies;i++) {
        if((abs(boat.position.x - enemies[i].position.x) < 2) && (abs(boat.position.z - enemies[i].position.z) < 2) && abs(boat.position.y - enemies[i].position.y) < 3.75) {
            man.position = glm::vec3(0,10,0);
            boat.rotation = 0;
            boat.life -= 30;
        }
    }
    // enemy vs cannonball
    for(int i=0;i<nenemies;i++) {
        hit[1] = 0;
        if((abs(cannonball.position.x - enemies[i].position.x) < 0.5) && (abs(cannonball.position.z - enemies[i].position.z) < 1.2) && cannonball.position.y - enemies[i].position.y < 3.75 && fire ==1 ) {
            enemies[i].position.y -= 1000;
            boat.score += 40;
            hit[1] = 1;
            break;
        }
    }
    //cout<<pow((boat.position.x - cube.position.x),2) + pow((boat.position.z - cube.position.z),2)<<endl;
    if(pow((boat.position.x - cube.position.x),2) + pow((boat.position.z - cube.position.z),2) < 2500 && started == 1) {
        bflag = 1;
    }
    // boss movement
    if (started == 1 && bflag == 1 && flag2 == 0) {
        for(int i=0; i<nboss; i++) {
//            cout<<atan((boat.position.z - boss[i].position.z)/(boat.position.x - boss[i].position.x))<<" "<<boss[i].position.x<<" "<<boss[i].position.y<<" "<<boss[i].position.z<<endl;
            float temp = atan((boat.position.z - boss[i].position.z)/(boat.position.x - boss[i].position.x));
            if(boss[i].position.y <= -7.6 ) {
                boss[i].speed = 0;
            }
            if (temp >= 0) {
                if (boat.position.x >= boss[i].position.x) {
                    boss[i].position.x += boss[i].speed*cos(temp);
                    boss[i].position.z += boss[i].speed*sin(temp);
                }
                else {
                    boss[i].position.x -= boss[i].speed*cos(temp);
                    boss[i].position.z -= boss[i].speed*sin(temp);
                }
            }
            if (temp < 0) {
                if (boat.position.x >= boss[i].position.x) {
                    boss[i].position.x += boss[i].speed*cos(abs(temp));
                    boss[i].position.z -= boss[i].speed*sin(abs(temp));
                }
                else {
                    boss[i].position.x -= boss[i].speed*cos(abs(temp));
                    boss[i].position.z += boss[i].speed*sin(abs(temp));
                }
            }

            // boss collision
            if((abs(boat.position.x - boss[i].position.x) < 1) && (abs(boat.position.z - boss[i].position.z) < 1) && (boat.position.y - boss[i].position.y < 5.5)) {
                boss[i].position = glm::vec3(rand()%200, -1.6, (rand()%400) - 200);
                man.rotation = 0;
                man.position = glm::vec3(-5,10,0);
                boat.life -= 50;
            }

            //boss vs cannonball
            hit[2] = 0;
            if((abs(cannonball.position.x - boss[i].position.x) < .4) && (abs(cannonball.position.z - boss[i].position.z) < 1.2) && (abs(cannonball.position.y - boss[i].position.y) < 5.5) && fire ==1 ) {
                if(boss[i].position.y >= -7) boss[i].position.y -= 2.4;
                boat.score += 60;
                hit[2] = 1;
            }
        }
    }
        //victory cube collision
        if((abs(cube.position.x-man.position.x) < 2) && (abs(man.position.z - cube.position.z) < 2) ) {
            int sum = 0;
            for(int i=0;i<nboss;i++) {
                if (boss[i].position.y <= -7) {
                    sum++;
                }
            }
            if (sum == 5) {
                cout<<"You Won"<<endl;
                quit(window);
            }
        }

        //island things
        if(man.position.x >= 220 && man.position.x <= 270 && man.position.z>0 && man.position.z<50) {
            flag2 = 1;
            boat.position.x = 217;
            boat.position.z = 2;
            boat.rotation = 0;
            man.position.y = 0.4;
        }
        if((man.position.x < 217 || man.position.x > 270) || (man.position.z < 0 || man.position.z > 50) ) {
            flag2 = 0;
            boat.position.z = man.position.z;
            boat.position.x = man.position.x;
            boat.rotation = man.rotation;
            man.position.y = boat.position.y + 1.75;

        }

    if (hit[0] == 0 && hit[1] == 0 && hit[2] == 0 && fire == 1 && flag == 0) {
        boat.score -= 10;
        flag = 1;
    }
    if(boat.life <= 0) quit(window);
    cout<<boat.score<<" "<<boat.life<<endl;
    //cout<<cube.position.x<<" "<<cube.position.y<<" "<<cube.position.z<<endl;
    //cout<<"boat "<<boat.position.x<<" "<<boat.position.y<<" "<<boat.position.z<<endl;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    boat       = Boat(-8, -2, 0, COLOR_BROWN);
    man        = Man(-1.3, -0.25, -0.25, COLOR_RED);//man definition
    sea        = Sea(-100, -1.6, -250, COLOR_BLUE);
    cannon     = Cannon(0, 1, -0.15, COLOR_BLACK);
    cannonball = Cannonball(0, 1, 0, COLOR_RED);
    for (int i=0;i<nboss;i++) boss[i]       = Boss(0,-1.6,0, COLOR_BLACK);
    for(int i=0;i<nrock;i++) {
        //rocks[i] = Rock((rand()%25 + 10), -1.6, ((rand()%50) - 25), COLOR_GREY);
        //cout<<"rock position"<<rocks[i].position.x<<" "<<rocks[i].position.z<<endl;
        rocks[i] = Rock(0, -1.6, 0, COLOR_GREY);
    }
    for(int i=0;i<nhblocks;i++) {
        hblocks[i] = Health(0, -1.6, 0, COLOR_GREEN);
    }
    for(int i=0;i<nenemies;i++) {
        enemies[i] = Enemy(0, -1.6, 0, COLOR_DARKRED);
    }
    cube       = Health(0, -1.6, 0, COLOR_GOLD);
    island     = Cube(220, -1.6, 0, 50, 2,50,COLOR_GREEND);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for ur "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    width  = 1960;
    height = 1024;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands

            draw();
            //cout<<"happy"<<endl;
            // Swap Frame Buffer in double buffering
            //reshapeWindow (window, width, height);
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
