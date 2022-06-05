//
// Created by pinto on 12/03/22.
//

#include "GenerateSphere.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <iostream>
#include "main.h"
void drawSideCilinderTriangle(float bottomHeight, float topHeight, float bottomRadius, float topRadius, float angle1, float angle2);

float *GetNormal(float *arr1, float *arr2, float *arr3);

void cross(float *a, float *b, float *res) {

    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}

void direction(float *a,float *b, float *res)
{
    res[0] = b[0] -a[0];
    res[1] = b[1] - a[1];
    res[2] = b[2] - a[2];
}
void normalize(float *a) {

    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/l;
    a[1] = a[1]/l;
    a[2] = a[2]/l;
}

float polar2CartX(float radius, float angle)
{
    return radius * sin(angle * M_PI / 180.f);
}

float polar2CartZ(float radius, float angle)
{
    return radius * cos(angle *  M_PI / 180.f);
}

void GenerateSphere::DrawSphere(float radius, int slices, int stacks)
{

    float step = 360.f / (float) slices;
    float heightStack = 2*radius / (float) stacks;
    float bottomRadius = 0.0f;

    for (int j = 0; j < stacks; ++j) {
        float distance2Center = abs( radius - heightStack*(j+1));
        //Pythagoran theorem to discover the new radius
        float topRadius =  sqrt(pow(radius,2)- pow(distance2Center,2));

        for (float i = 0; i < 360.f; i+=step) {
            drawSideCilinderTriangle( heightStack*j,heightStack*(j+1),bottomRadius,topRadius,i,i+step);
        }
        bottomRadius = topRadius;
    }
}

void drawSideCilinderTriangle(float bottomHeight, float topHeight, float bottomRadius, float topRadius, float angle1, float angle2)
{
    float arr1[3] = {polar2CartX(bottomRadius, angle1), bottomHeight, polar2CartZ(bottomRadius, angle1)};

    float arr2[3] = {polar2CartX(bottomRadius, angle2), bottomHeight, polar2CartZ(bottomRadius, angle2)};
    float arr3[3] = {polar2CartX(topRadius, angle2), topHeight, polar2CartZ(topRadius, angle2)};

    main::PushVertex(arr1[0],arr1[1],arr1[2]);
    main::PushVertex(arr2[0],arr2[1],arr2[2]);
    main::PushVertex(arr3[0],arr3[1],arr3[2]);

    float* upWards1 = GetNormal(arr1, arr2, arr3);
    float* upWards2 = GetNormal(arr2, arr3, arr1);
    float* upWards3 = GetNormal(arr3, arr1, arr2);

    main::PushNormal(upWards1[0],upWards1[1],upWards1[2]);
    main::PushNormal(upWards2[0],upWards2[1],upWards2[2]);
    main::PushNormal(upWards3[0],upWards3[1],upWards3[2]);

    free(upWards1);
    free(upWards2);
    free(upWards3);

    //Second part of the side
    float arr6[3] = {polar2CartX(topRadius, angle1), topHeight, polar2CartZ(topRadius, angle1)};

    main::PushVertex(arr1[0],arr1[1],arr1[2]);
    main::PushVertex(arr3[0],arr3[1],arr3[2]);
    main::PushVertex(arr6[0],arr6[1],arr6[2]);


    float* upWards4 = GetNormal(arr1, arr3, arr6);
    float* upWards5 = GetNormal(arr3, arr6, arr1);
    float* upWards6 = GetNormal(arr6, arr1, arr3);

    main::PushNormal(upWards4[0],upWards4[1],upWards4[2]);
    main::PushNormal(upWards5[0],upWards5[1],upWards5[2]);
    main::PushNormal(upWards6[0],upWards6[1],upWards6[2]);

    free(upWards4);
    free(upWards5);
    free(upWards6);


}

float *GetNormal(float *arr1, float *arr2, float *arr3) {
    float dir1[3];
    float dir2[3];
    direction(arr1,arr2,dir1);
    direction(arr1,arr3,dir2);

    auto upWards1 = static_cast<float *>(malloc(sizeof(float) * 3));

    cross(dir1, dir2, upWards1);
    normalize(upWards1);
    return upWards1;
}


