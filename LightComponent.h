//
// Created by pinto on 05/06/22.
//

#ifndef MAIN_CPP_LIGHTCOMPONENT_H
#define MAIN_CPP_LIGHTCOMPONENT_H
#include <GL/glew.h>
#include <iostream>

const GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

class LightComponent {
public:
    float posX;
    float posY;
    float posZ;
    inline static int currentNumberLights = 0;
    int currentPos;

    void SetLight()
    {
        glEnable(0x4000+currentPos);

        glLightfv(0x4000+currentPos, GL_AMBIENT, light_ambient);
        glLightfv(0x4000+currentPos, GL_DIFFUSE, light_diffuse);
        glLightfv(0x4000+currentPos, GL_SPECULAR, light_specular);
    }
    void virtual RenderLight()
    {

    }
};

class LightPoint : public LightComponent{
    void RenderLight() override{
        float pos[4] = {posX, posY, posZ, 1.0f};
        // Set the position of the light during runtime
        glLightfv(0x4000+currentPos,GL_POSITION, pos);

    }
};


class LightDirection : public LightComponent{
    void RenderLight() override{
        float pos[4] = {posX, posY, posZ, 0.0f};
        // Set the position of the light during runtime
        glLightfv(0x4000+currentPos,GL_POSITION, pos);
    }
};
#endif //MAIN_CPP_LIGHTCOMPONENT_H
