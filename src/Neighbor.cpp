#include "Neighbor.h"
#include "Fluid.h"
#include "Particle.h"


Neighbor::Neighbor(Particle* p1_, Particle* p2_) :
    p1(p1_), p2(p2_), distance(0), nx(0), ny(0), weight(0)
{
    nx = p1->x - p2->x;
    ny = p1->y - p2->y;
    distance = sqrt(nx * nx + ny * ny);
    weight = 1 - distance / Fluid::RANGE;
    float density = weight * weight;
    p1->density += density;
    p2->density += density;
    density *= weight * Fluid::PRESSURE_NEAR;
    p1->densityNear += density;
    p2->densityNear += density;
    const float invDistance = 1.0 / distance;
    nx *= invDistance;
    ny *= invDistance;
}

void
Neighbor::calculateForce()
{
    float p;
    if (p1->type != p2->type) {
        p = (p1->density + p2->density - Fluid::DENSITY * 1.5) * Fluid::PRESSURE;
    } else {
        p = (p1->density + p2->density - Fluid::DENSITY * 2.0) * Fluid::PRESSURE;
    }
    const float pn = (p1->densityNear + p2->densityNear) * Fluid::PRESSURE_NEAR;
    float pressureWeight = weight * (p + weight * pn);
    float viscosityWeight = weight * Fluid::VISCOSITY;
    float fx = nx * pressureWeight;
    float fy = ny * pressureWeight;
    fx += (p2->vx - p1->vx) * viscosityWeight;
    fy += (p2->vy - p1->vy) * viscosityWeight;
    p1->fx += fx;
    p1->fy += fy;
    p2->fx -= fx;
    p2->fy -= fy;
}
