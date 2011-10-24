#include "Fluid.h"
#include "ofMain.h"
#include "Particle.h"
#include "Neighbor.h"


const float Fluid::GRAVITY = 0.05;
const float Fluid::RANGE = 16.0;
const float Fluid::RANGE2 = Fluid::RANGE * Fluid::RANGE;
const float Fluid::DENSITY = 2.5;
const float Fluid::PRESSURE = 1.0;
const float Fluid::PRESSURE_NEAR = 1.0;
const float Fluid::VISCOSITY = 0.1;
const int Fluid::NUM_GRIDS = 29;
const int Fluid::INV_GRID_SIZE = 1 / (465 / Fluid::NUM_GRIDS);

Fluid::Fluid(ofBaseApp* app_) :
    pourOn(false), count(0),app(app_)
{
}

Fluid::~Fluid()
{
    std::vector<Neighbor*>::iterator neighbor;
    for (neighbor = neighbors.begin(); neighbor != neighbors.end(); ++neighbor) {
        delete (*neighbor);
    }

    std::vector<Particle*>::iterator particle;
    for (particle = particles.begin(); particle != particles.end(); ++particle) {
        delete (*particle);
    }
}

void
Fluid::update()
{
    ++count;

    if (pourOn) {
        pour();
        // std::cout << "Frame " << count << ": " << particles.size()
        //           << " particles" << std::endl;
    }

    updateGrid();
    findNeighbors();
    calculateForce();
    std::vector<Particle*>::iterator iter;
    for (iter = particles.begin(); iter != particles.end(); ++iter) {
        Particle* p = *iter;
        p->update();
    }
}

void
Fluid::draw()
{
    std::vector<Particle*>::iterator iter;
    for (iter = particles.begin(); iter != particles.end(); ++iter) {
        (*iter)->draw();
    }
}

void
Fluid::updateGrid()
{
    for (int i = 0; i < NUM_GRIDS; ++i) {
        for (int j = 0; j < NUM_GRIDS; ++j) {
            grid[i][j].clear();
        }
    }

    std::vector<Particle*>::iterator iter;
    for (iter = particles.begin(); iter != particles.end(); ++iter) {
        Particle* p = (*iter);
        p->fx = p->fy = p->density = p->densityNear = 0.0;
        p->gx = p->x * INV_GRID_SIZE;
        p->gy = p->y * INV_GRID_SIZE;
        if (p->gx < 0) {
            p->gx = 0;
        } else if (p->gx > NUM_GRIDS - 1) {
            p->gx = NUM_GRIDS - 1;
        }
        if (p->gy < 0) {
            p->gy = 0;
        } else if (p->gy > NUM_GRIDS - 1) {
            p->gy = NUM_GRIDS - 1;
        }
    }
}

void
Fluid::findNeighbors()
{
    // Clear out the old neighbors list.
    std::vector<Neighbor*>::iterator nIter;
    for (nIter = neighbors.begin(); nIter != neighbors.end(); ++nIter) {
        delete (*nIter);
    }
    neighbors.clear();

    std::vector<Particle*>::iterator iter;
    for (iter = particles.begin(); iter != particles.end(); ++iter) {
        Particle* p = *iter;

        const bool xMin = p->gx != 0;
        const bool xMax = p->gx != NUM_GRIDS - 1;
        const bool yMin = p->gy != 0;
        const bool yMax = p->gy != NUM_GRIDS - 1;
        findNeighborsInGrid(p, grid[p->gx][p->gy]);
        if (xMin) findNeighborsInGrid(p, grid[p->gx - 1][p->gy]);
        if (xMax) findNeighborsInGrid(p, grid[p->gx + 1][p->gy]);
        if (yMin) findNeighborsInGrid(p, grid[p->gx][p->gy - 1]);
        if (yMax) findNeighborsInGrid(p, grid[p->gx][p->gy + 1]);
        if (xMin && yMin) findNeighborsInGrid(p, grid[p->gx - 1][p->gy - 1]);
        if (xMin && yMax) findNeighborsInGrid(p, grid[p->gx - 1][p->gy + 1]);
        if (xMax && yMin) findNeighborsInGrid(p, grid[p->gx + 1][p->gy - 1]);
        if (xMax && yMax) findNeighborsInGrid(p, grid[p->gx + 1][p->gy + 1]);
        grid[p->gx][p->gy].push_back(p);
    }
    // std::cout << "Neighbors: " << neighbors.size() << ", capacity: "
    //           << neighbors.capacity() << std::endl;
}

void
Fluid::findNeighborsInGrid(Particle* pi, const std::vector<Particle*>& g)
{
    unsigned int numParticles = g.size();
    for (unsigned int j = 0; j < numParticles; ++j) {
        Particle* pj = g[j];
        float dx = pi->x - pj->x;
        float dy = pi->y - pj->y;
        const float distance =  dx * dx +  dy * dy;
        if (distance < Fluid::RANGE2) {
            neighbors.push_back(new Neighbor(pi, pj));
        }
    }
}

void
Fluid::calculateForce()
{
    std::vector<Neighbor*>::iterator iter;
    for (iter = neighbors.begin(); iter != neighbors.end(); ++iter) {
        (*iter)->calculateForce();
    }
}

void
Fluid::pour()
{
    for (int i = -4; i <= 4; ++i) {
        Particle* p = new Particle(app->mouseX + i * 10, app->mouseY,
                                   count / 10 % 5);
        p->vy = 5;
        particles.push_back(p);
    }
}


