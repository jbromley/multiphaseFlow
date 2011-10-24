#include "Particle.h"
#include "Fluid.h"
#include "Neighbor.h"


Particle::Particle(float x_, float y_, int type_) :
    x(x_), y(y_), gx(0), gy(0), vx(0), vy(0), fx(0), fy(0), density(0),
    densityNear(0), type(type_)
{
    switch (type) {
    case 0:
        color = ofColor(96, 96, 255, 255);
        break;
    case 1:
        color = ofColor(255, 96, 0, 255);
        break;
    case 2:
        color = ofColor(255, 0, 96, 255);
        break;
    case 3:
        color = ofColor(0, 224, 96, 255);
        break;
    case 4:
        color = ofColor(224, 224, 0, 255);
        break;
    default:
        color = ofColor(128, 128, 128, 255);
        break;
    }
}

void
Particle::update()
{
    vy += Fluid::GRAVITY;
    if (density > 0) {
        vx += fx / (density * 0.9 + 0.1);
        vy += fy / (density * 0.9 + 0.1);
    }
    x += vx;
    y += vy;

    int rightEdge = ofGetWidth() - 5;
    if (x < 5) {
        vx += (5 - x) * 0.5 - vx * 0.5;
    }
    if (x > rightEdge) {
        vx += (rightEdge - x) * 0.5 - vx * 0.5;
    }

    int bottomEdge = ofGetHeight() - 5;
    if (y < 5) {
        vy += (5 - y) * 0.5 - vy * 0.5;
    }
    if (y > bottomEdge) {
        vy += (bottomEdge - y) * 0.5 - vy * 0.5;
    }
}

void
Particle::draw()
{
    ofSetColor(color);
    ofRect(x - 1, y - 1, 3, 3);
}


