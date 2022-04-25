//
// Created by pinto on 25/04/22.
//

#ifndef MAIN_CPP_CATMULL_ROM_H
#define MAIN_CPP_CATMULL_ROM_H

#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class catmull_rom {

public:
    static void RenderCatmull(float **arrayPoints,int numberPoints,float posicaoTeaPotCurva,bool align);

    static void ApplyRotation(const float *deriv);
};


#endif //MAIN_CPP_CATMULL_ROM_H
