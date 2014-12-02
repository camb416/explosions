//
//  Boid.cpp
//  explosions
//
//  Created by Cameron Browning on 11/30/14.
//
//

#include "Boid.h"
#define TAILLENGTH 16

void Boid::setup(){
    // the boid
    // float x,y;
    // float vX,vY,vF;
    // float r;
    // float size;
    x = ofGetWidth()/2;
    y = ofGetHeight()/2;
    vX = vY = vF = 0;
    aX = aF = 0;
    aY = 0.1f;
    // vR = ofRandomf()*0.1f;
    vR = 0;
    vF = ofRandomf()*3.0f;
    r = ofRandomf()*TWO_PI;
    size = 2;
    o = 1.0f;//ofRandomf()*0.25f + 0.25f;
    vX = cos(r)*vF;
    vY = sin(r)*vF;
    
    pX = x;
    pY = y;
    
    for(int i=0;i<TAILLENGTH; i++){
        tail.push_back(ofPoint(x,y));
    }
}
void Boid::update(){
   // size *= 0.99f;

    pX = x;
    pY = y;
    
    for(int i=TAILLENGTH-1;i>0; i--){
        tail.at(i).set(tail.at(i-1).x,tail.at(i-1).y);
    }
   
    
    //vF *= 0.99f;
    //vR *= 0.99f;
    r += vR;
    //vX = cos(r)*vF;
    //vY = sin(r)*vF;
    
    if(ofGetMousePressed()){
        aF = -128.0f/ MAX(ofDistSquared(x, y, ofGetMouseX(), ofGetMouseY()),256);
        
    } else {
        aF = 0;
    }
    float mouseR = atan2(y-ofGetMouseY(),x-ofGetMouseX());
    aX = cos(mouseR)*aF;
    aY = sin(mouseR)*aF;
    
    
    
    vX += aX;
    vY += aY;
    
    //vX = MAX(MIN(vX,5),-5);
    //vY = MAX(MIN(vY,5),-5);
    
    vX *= 0.97f;
    vY *= 0.97f;
    
    
    //vF = sqrt(vX*vX+vY*vY);
    //vF*=0.99f;
    
    
    

    
    x += vX;
    y += vY;
     tail.at(0).set(x,y);
    
    if(y+vY>ofGetHeight()){
        y = ofGetHeight();
        vY*=-0.9f;
        vX*=0.9f;
    }
    size = aF;
    if(size<0) size *= -1.0f;
    size += 0.5f;

    
}
void Boid::draw(){
    ofSetLineWidth(1);
   // ofEnableAlphaBlending();
    // ofSetColor(255,255,255,o*255);
   // ofLine(x-1,y-1,pX-1,pY-1);
    //ofCircle(x-1,y-1,size);
    ofSetColor(255,255,255,64);
    for(int i=1;i<TAILLENGTH; i++){
        
        //ofCircle(x,y,size);
        ofLine(tail.at(i-1).x-1,tail.at(i-1).y-1,tail.at(i).x-1,tail.at(i).y-1);
    }
    
    ofSetColor(0,0,0,64);
for(int i=1;i<TAILLENGTH; i++){

    //ofCircle(x,y,size);
    ofLine(tail.at(i-1).x,tail.at(i-1).y,tail.at(i).x,tail.at(i).y);
}
    
    
    
    ofSetColor(0,0,0,255);
    ofCircle(x,y,size);
    
    
}