#include "Boid.h"

// Constructor
Boid::Boid(vec3 pos, ofColor _color){
    cout << "Constructed a Boid" << endl;

    velocity = vec3(ofRandom(-1,1),ofRandom(-1,1),ofRandom(-1,1));
    color = _color;
    
    sphere.set(2,3);
    sphere.setPosition(pos);
    material.setDiffuseColor(_color);
    cone.set(1, 4);
    cone.setPosition(0, 0, -4);
    cone.setOrientation(vec3(90,0,90));
    
    cone.setParent(sphere);
    
    sphereCage.set(4,1); //the second parameter sets the resolution of how many triangles/faces in the mesh
    sphereCage.setParent(sphere);
    
}
// copy constructor
Boid::Boid(const Boid& b){
    cout << "Copied a Boid" << endl;
      
    velocity = b.velocity;
    color = b.color;
    sphere = b.sphere;
    material = b.material;
      
    // Do your custom primitive copying and parenting below instead of my example
    sphereCage = b.sphereCage;
      
    //Here we are making sure that the primitive is pointing to the existing sphere
    sphereCage.setParent(sphere);
      
}

Boid::~Boid(){
    cout << "Destructed a Boid" << endl;
}

//--------------------------------------------------------------
void Boid::update(vector<Boid>& _flock,float speedlimit,float separationFactor, float cohesionFactor, float alignmentFactor,float checkdist,float boundradius, float bouncespeed){
    
    //Set the base distance for flocking nearest neighbors
    distToCheck = checkdist;
    
    //Keep Boids in a sphere
    checkBoundary(bouncespeed,boundradius);

    //Add flocking behavior
    flock(_flock,separationFactor,cohesionFactor,alignmentFactor);
    
    //Limit how fast a boid can go
    if(length(velocity) > speedlimit){
        velocity = normalize(velocity) * speedlimit;
    }
 
    //Move the Boid
    sphere.move(velocity);
    
}

void Boid::draw(){
  
    material.begin();
    sphere.draw();
    material.end();
    
    cone.draw();
    sphereCage.drawWireframe();
    
}

void Boid::flock(vector<Boid>& _flock, float separationFactor, float cohesionFactor, float alignmentFactor){
    vec3 separation = vec3(0,0,0);
    vec3 cohesion = vec3(0,0,0);
    vec3 align = vec3(0,0,0);
    int numCohesionNeighbours = 0;
    int numAlignNeighbours = 0;
    
    // query the entire flock
    for(int i = 0 ; i < _flock.size();i++){
                
        float dist = distance(getPosition(), _flock[i].getPosition());
        
        if(dist < distToCheck){
            // it's close enough >> add a difference vector
            separation -= (_flock[i].getPosition() - getPosition());
        }
        
        if(dist < distToCheck+20 && dist > 10){
            // its close enough >> add its position to the avarage
            cohesion += _flock[i].getPosition();
            numCohesionNeighbours++;
        }
        
        if(dist < distToCheck+10 && dist > 10){
            // it's close enough >> add its velocity to the avarage
            align += _flock[i].getVelocity();
            numAlignNeighbours++;
        }
        
    }
    
    separation *= separationFactor;
    velocity += separation;
    
    if(numCohesionNeighbours == 0){
        cohesion = vec3(0,0,0);
    } else{
        cohesion /= numCohesionNeighbours;
        cohesion -= getPosition();
        cohesion *= cohesionFactor;
    }
    
    velocity += cohesion;
    
    if(numAlignNeighbours == 0){
        align = vec3(0,0,0);
    }else{
        align /= numAlignNeighbours;
        align *= alignmentFactor;
        
        //this will point the sphere in the direction of alignment vector
        vec3 lookAhead = normalize(align) * 50;
        sphere.lookAt(lookAhead);
    }

    
    velocity += align;
    
}

//If the distance between the Boid and the center is greater
//than radius (size) of sphere then reverse the direction
void Boid::checkBoundary(float bouncespeed, float size) {

    vec3 position = getPosition();
    vec3 desired = vec3(0,0,0) - position;
 
    //The size variable is the radius of a sphere around the origin
    if(length(desired) > size){
        desired = normalize(desired)*bouncespeed;
        velocity = desired - velocity;
    }

}

vec3 Boid::getPosition(){
    return sphere.getPosition();
}

vec3 Boid::getVelocity(){
    return velocity;
}
