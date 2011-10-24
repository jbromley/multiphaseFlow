#pragma once


class Particle;


class Neighbor
{
public:
    Neighbor(Particle* p1_, Particle* p2_);
    void calculateForce();

    Particle* p1;
    Particle* p2;
    float distance;
    float nx;
    float ny;
    float weight;
};

