//
// Created by edu on 04/04/22.
//

#include <math.h>
#include "GenerateRing.h"
#include "main.h"

void GenerateRing::GenerateRingFunc(float smallerRadius, float biggerRadius, int slices){

    float angle = 360/slices, curr_angle, x, z, bigX, bigZ, lastX, lastZ;
    for(int i = 0; i<slices;){
        curr_angle = ((angle * M_PI) / 180) * i;
        x = smallerRadius * sinf(curr_angle);
        z = smallerRadius * cosf(curr_angle);
        main::PushVertex(x,0.0f,z);
        lastX = x;
        lastZ = z;
        bigX = biggerRadius * sinf(curr_angle);
        bigZ = biggerRadius * cosf(curr_angle);
        main::PushVertex(bigX,0.0f,bigZ);

        curr_angle = ((angle * M_PI) / 180) * ++i;
        bigX = biggerRadius * sinf(curr_angle);
        bigZ = biggerRadius * cosf(curr_angle);
        main::PushVertex(bigX,0.0f,bigZ);

        x = smallerRadius * sinf(curr_angle);
        z = smallerRadius * cosf(curr_angle);
        main::PushVertex(bigX,0.0f,bigZ);
        main::PushVertex(x,0.0f,z);
        main::PushVertex(lastX,0.0f,lastZ);

    }


    /*float angle1 = 360/slices;
    float xaux, zaux, sx, sz;
    for(int i = 0; i<slices;) {
        float curr_angle = ((angle1 * M_PI) / 180) * i;
        float x = smallerRadius * sinf(curr_angle);
        float z = smallerRadius * cosf(curr_angle);
        sx = x;
        sz = z;
        main::PushVertex(x,0.0f,z);
        x = biggerRadius * sinf(curr_angle);
        z = biggerRadius * cosf(curr_angle);
        xaux = x;
        zaux = z;
        i++;
        curr_angle = ((angle1 * M_PI) / 180) * i;
        x = biggerRadius * sinf(curr_angle);
        z = biggerRadius * cosf(curr_angle);
        main::PushVertex(x,0.0f,z);
        main::PushVertex(xaux,0.0f,zaux);

        main::PushVertex(x,0.0f,z);
        main::PushVertex(sx,0.0f,sz);

        x = smallerRadius * sinf(curr_angle);
        z = smallerRadius * cosf(curr_angle);
        main::PushVertex(x,0.0f,z);

    }*/



}