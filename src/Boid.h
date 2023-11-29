#pragma once
#include "ofMain.h"

using namespace glm;

class Boid{
    
public:
    
    Boid(vec3  pos, ofColor _color);
    // create this to make a copy
    Boid(const Boid& b); // Const means we won't modify the original
    ~Boid();
    
    void draw();
    void update(vector<Boid>& _flock, float speedlimit, float separationFactor, float cohesionFactor, float alignmentFactor, float checkdist, float boundradius, float bouncespeed);
    vec3 getPosition();
    vec3 getVelocity();
    
private:
    
    void checkBoundary(float speed, float size);
    void flock(vector<Boid>& _flock, float separationFactor, float cohesionFactor, float alignmentFactor);
    
    vec3 velocity;
    float distToCheck;
    ofColor color;
    ofMaterial material;

    ofIcoSpherePrimitive sphere;
    ofConePrimitive cone;
    ofIcoSpherePrimitive sphereCage;

};

