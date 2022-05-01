//
// Created by pinto on 31/03/22.
//

#ifndef CLASS1_TRANSFORM_H
#define CLASS1_TRANSFORM_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include "../catmull_rom.h"
#include "../Timer.h"

class Transform {
public:
//    Transform()= default;
    virtual void Print()
    {
        std::cout<< "hello ma man\n";
    }

    virtual void Apply() {

    }
};

class T_Scale : public Transform{
public:
    float x,y,z;
    T_Scale(float x,float y,float z):x(x),y(y),z(z){}
    virtual void Print(){
        std::cout << " I am Scale";
    }
    virtual void Apply()
    {
        glScalef(x,y,z);
    }
};

class T_Translate : public Transform{
public:
    float x,y,z;
    T_Translate(float x,float y,float z):x(x),y(y),z(z){}
    void Print() override{
        std::cout << " I am Transform";
    }
    virtual void Apply()
    {
        glTranslatef(x,y,z);
    }
};
class T_Rotate : public Transform{
public:
    float angle,x,y,z;
    T_Rotate(float angle,float x,float y,float z):angle(angle),x(x),y(y),z(z){}
    void Print() override{
        std::cout << " I am Rotate";
    }

    virtual void Apply()
    {
        glRotatef(angle,x,y,z);
    }
};


class T_Rotate_Time : public Transform{

public:
    float time,x,y,z;
    float current_angle=0.f;
    T_Rotate_Time(float time,float x,float y,float z):time(time*1000),x(x),y(y),z(z){}
    void Print() override{
        std::cout << " I am Rotate with Time";
    }

    virtual void Apply()
    {
        //10 ms ultima frame
        //10000ms para chegar a 360
        //Regra de 3 simples
        // 10 000 - 360
        // 10     - a
        //Tem de incrementar cerca de 10*360/10 000

        current_angle += ((float) Timer::GetTime() * 360)/ time ;
        glRotatef(current_angle,x,y,z);
    }

};
//3 PHASE OF PROJECT
//CATMULL ROM CURVES STRUCTURE

class T_Catmull_Rom : public Transform{
    // Points that make up the loop for catmull-rom interpolation
    float **all_Points;
    int number_Points;
    bool align;
    float time;
    float posicaoTeaPotCurva = 0;
    float increaseInterpolation;

public:
    T_Catmull_Rom(float **allPoints, int numberPoints, bool align, float time) :
    all_Points(allPoints),number_Points(numberPoints),align(align), time(time*1000)
    {
    }

    void Print() override{
        std::cout << " I am Catmull";
    }

    virtual void Apply()
    {
//        glPushMatrix();
        catmull_rom::RenderCatmull(all_Points,number_Points,posicaoTeaPotCurva,align);

        //To make sure that no more models are affected by the rotations and translations of the catmull curve
//        glPopMatrix();
        float increase = Timer::GetTime() / time;
        posicaoTeaPotCurva+= increase;
    }
};

#endif //CLASS1_TRANSFORM_H