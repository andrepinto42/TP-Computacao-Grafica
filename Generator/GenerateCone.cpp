//
// Created by edu on 12/03/22.
//

#include "GenerateCone.h"
#include <vector>
#include <math.h>
#include "main.h"

void GenerateCone::GenerateConeFunc(float radius, float height, int slices, int stacks){
    float x, y=0, z, xl, yl, zl;
    float xV  = 0, yV = height, zV = 0;
    float angle1 = 360/slices;
    float raio = radius;
    int j;
    for(int j=0;j<stacks;j++) {
        for (int i = 0; i < slices;) {
            float curr_angle = ((angle1 * M_PI) / 180) * (-i);
            i++;
            x = radius * sinf(curr_angle);
            z = radius * cosf(curr_angle);
            curr_angle = ((angle1 * M_PI) / 180) * (-i);
            xl = radius * sinf(curr_angle);
            zl = radius * cosf(curr_angle);
            //desenha base de baixo
            if (j == 0) {
                main::PushVertex(0.0f, 0.0f, 0.0f);
                main::PushVertex(x, 0.0f, z);
                main::PushVertex(xl, 0.0f, zl);

                main::PushVertex(x+((xV-x)/stacks), y+((height)/stacks), z+((zV-z)/stacks));
                main::PushVertex(xl,y,zl);
                main::PushVertex(x,y,z);

                main::PushVertex(x+((xV-x)/stacks), y+((height)/stacks), z+((zV-z)/stacks));
                main::PushVertex(xl+((xV-xl)/stacks), y+((height)/stacks), zl+((zV-zl)/stacks));
                main::PushVertex(xl,y,zl);
            }
            else if(j==stacks-1){
                main::PushVertex(xV,height,zV);
                main::PushVertex(xl,y,zl);
                main::PushVertex(x,y,z);
            }
            else{
                main::PushVertex(x+((xV-x)/(stacks-j)), y+((height)/stacks), z+((zV-z)/(stacks-j)));
                main::PushVertex(xl,y,zl);
                main::PushVertex(x,y,z);

                main::PushVertex(x+((xV-x)/(stacks-j)), y+((height)/stacks), z+((zV-z)/(stacks-j)));
                main::PushVertex(xl+((xV-xl)/(stacks-j)), y+((height)/stacks), zl+((zV-zl)/(stacks-j)));
                main::PushVertex(xl,y,zl);
            }

        }
        y = y + height/stacks;
        radius = radius - raio/stacks;
    }
}