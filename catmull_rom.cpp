//
// Created by pinto on 25/04/22.
//
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <typeinfo>
#include <GL/glut.h>
#include "catmull_rom.h"

//static int POINT_COUNT = 5;
//float **all_Points;

const int TESSELATION = 100;
const float increase_TESSELATION = 1/(float)TESSELATION;

void buildRotMatrix(float *x, float *y, float *z, float *m) {

    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

void cross(float *a, float *b, float *res) {

    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}

void normalize(float *a) {

    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/l;
    a[1] = a[1]/l;
    a[2] = a[2]/l;
}

float length(float *v) {

    float res = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    return res;

}

void multMatrixVector(float *m, float *v, float *res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }

}

void getCatmullRomPoint(float interpolation, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

    // catmull-rom matrix
    float CM_Matrix[4][4] = {{-0.5f, 1.5f,  -1.5f, 0.5f},
                             {1.0f,  -2.5f, 2.0f,  -0.5f},
                             {-0.5f, 0.0f,  0.5f,  0.0f},
                             {0.0f,  1.0f,  0.0f,  0.0f}};


    // For each component i: // x, y, z
    for (int i = 0; i < 3; ++i) {
        float a[4];

        // in component i P is the vector (p0[i], p1[i], p2[i],p3[i]
        float arr_Points[4] = {p0[i], p1[i], p2[i], p3[i] };

        // Compute vector A = M * P // use function multMatrixVector
        multMatrixVector(*CM_Matrix, arr_Points, a);

        // Compute pos[i] = T * A
        pos[i] = pow(interpolation, 3) * a[0] + pow(interpolation, 2) * a[1] + interpolation * a[2] + a[3];

        // compute deriv[i] = T' * A
        deriv[i] = 3 * pow(interpolation, 2) * a[0] + 2 * interpolation * a[1] + a[2];// a[3] * 0
    }

}

// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(float nivelDeInterpolacao, float *pos, float *deriv,float **all_Points,int POINT_COUNT) {

    float t = nivelDeInterpolacao * POINT_COUNT; // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;
    indices[1] = (indices[0]+1)%POINT_COUNT;
    indices[2] = (indices[1]+1)%POINT_COUNT;
    indices[3] = (indices[2]+1)%POINT_COUNT;

    getCatmullRomPoint(t, all_Points[indices[0]], all_Points[indices[1]], all_Points[indices[2]], all_Points[indices[3]],
            /* Fills these variables*/ pos, deriv);
}

void renderCatmullRomCurve(float **all_Points,int numberPoints) {
    float pos[4];
    float deriv[4];
// draw curve using line segments with GL_LINE_LOOP
    glBegin(GL_LINE_LOOP);
    float nivelDeInterpolacao = 0.f;
    float color[4] = {1.f,1.f,1.f,0.f};

    glMaterialfv(GL_FRONT,GL_AMBIENT, color);

    for (int i = 0; i < TESSELATION; ++i) {
        getGlobalCatmullRomPoint(nivelDeInterpolacao,  pos,  deriv,all_Points,numberPoints);
        glVertex3f(pos[0], pos[1], pos[2]);
        nivelDeInterpolacao+=increase_TESSELATION;
    }
    glEnd();
}


void catmull_rom::RenderCatmull(float **all_Points,int numberPoints,float posicaoTeaPotCurva,bool align)
{
    renderCatmullRomCurve(all_Points,numberPoints);

    float pos[3];
    float deriv[3];

    getGlobalCatmullRomPoint(posicaoTeaPotCurva, pos, deriv,all_Points,numberPoints);

    //Very Important translate that defines the position to be drawn
    glTranslatef(pos[0],pos[1],pos[2]);

    if (align)
        ApplyRotation(deriv);

//    glutWireTeapot(0.1);

}

void catmull_rom::ApplyRotation(const float *deriv) {
    float x[3] = {deriv[0], deriv[1], deriv[2]};
    normalize(x);

    float z[3];
    float y_Inicial[3] = {0,1,0};
    cross(x,y_Inicial,z);
    normalize(z);

    float y[3];
    cross(z,x,y);
    normalize(y);

    float m[16];
    buildRotMatrix(x,y,z,m);

    //Builds the rotation matrix that specifies the orientantion to follow the trajectory of the curve
    glMultMatrixf(m);
}

