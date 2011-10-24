#pragma once
#include <vector>
#include "ofMain.h"


class Particle;
class Neighbor;


class Fluid
{
public:
    Fluid(ofBaseApp* app_);
    ~Fluid();
    void update();
    void draw();

    static const float GRAVITY;
    static const float RANGE;
    static const float RANGE2;
    static const float DENSITY;
    static const float PRESSURE;
    static const float PRESSURE_NEAR;
    static const float VISCOSITY;
    static const int NUM_GRIDS;
    static const int INV_GRID_SIZE;

    bool pourOn;

private:
    void pour();
    void updateGrid();
    void findNeighbors();
    void findNeighborsInGrid(Particle* pi, const std::vector<Particle*>& g);
    void calculateForce();

    std::vector<Particle*> particles;
    std::vector<Neighbor*> neighbors;
    int count;
    std::vector<Particle*> grid[29][29];
    ofBaseApp* app;
};

