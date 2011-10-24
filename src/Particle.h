#pragma once
#include "ofMain.h"
#include "Fluid.h"


class Particle
{
public:
    Particle(float x_, float y_, int type_);
    void update();
    void draw();

    float x;
    float y;
    int gx;
    int gy;
    float vx;
    float vy;
    float fx;
    float fy;
    float density;
    float densityNear;
    ofColor color;
    int type;
};

