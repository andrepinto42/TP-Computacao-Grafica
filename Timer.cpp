//
// Created by pinto on 25/04/22.
//

#include <GL/glut.h>
#include "Timer.h"

int currentTimeBetweenFrames=0;
int previousTime=0;
int timeBetweenFrame;

void Timer::AdjustTimeBetweenFrame()
{
    previousTime = currentTimeBetweenFrames;
    currentTimeBetweenFrames = glutGet(GLUT_ELAPSED_TIME);

    timeBetweenFrame = currentTimeBetweenFrames-previousTime;
}

int Timer::GetTime(){
    return timeBetweenFrame;
}