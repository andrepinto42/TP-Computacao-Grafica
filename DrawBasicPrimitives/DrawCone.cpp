//
// Created by edu on 12/03/22.
//

#include "DrawCone.h"
#include <math.h>
#include <GL/glut.h>

void DrawCone::DrawConeFunc(float radius, float height, int slices, int stacks) {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);
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
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(x, 0.0f, z);
                glVertex3f(xl, 0.0f, zl);

                glVertex3f(x+((xV-x)/stacks), y+((height)/stacks), z+((zV-z)/stacks));
                glVertex3f(xl,y,zl);
                glVertex3f(x,y,z);

                glVertex3f(x+((xV-x)/stacks), y+((height)/stacks), z+((zV-z)/stacks));
                glVertex3f(xl+((xV-xl)/stacks), y+((height)/stacks), zl+((zV-zl)/stacks));
                glVertex3f(xl,y,zl);
            }
            else if(j==stacks-1){
                glVertex3f(xV,height,zV);
                glVertex3f(xl,y,zl);
                glVertex3f(x,y,z);
            }
            else{
                glVertex3f(x+((xV-x)/(stacks-j)), y+((height)/stacks), z+((zV-z)/(stacks-j)));
                glVertex3f(xl,y,zl);
                glVertex3f(x,y,z);

                glVertex3f(x+((xV-x)/(stacks-j)), y+((height)/stacks), z+((zV-z)/(stacks-j)));
                glVertex3f(xl+((xV-xl)/(stacks-j)), y+((height)/stacks), zl+((zV-zl)/(stacks-j)));
                glVertex3f(xl,y,zl);
            }

            /*  //desenha triangulos laterais
              glColor3f(1.0f,1.0f,0.0f);
              glVertex3f(xV, yV, zV);
              glVertex3f(x, 0.0f, z);
              glVertex3f(xl, 0.0f, zl);*/
        }
        y = y + height/stacks;
        radius = radius - raio/stacks;
    }

    glEnd();
}