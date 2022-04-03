//
// Created by pinto on 07/03/22.
//

#include <valarray>
#include <GL/glu.h>
#include "CameraStatus.h"
#include "Generator/Vector3.h"

static int speed = 5.f;

/*
 * Constructors
 */
CameraStatus::CameraStatus(float posX, float posY, float posZ, float lookX, float lookY, float lookZ, float upX,
                           float upY, float upZ, float fov, float near, float far) :
        posX(posX), posY(posY), posZ(posZ), lookX(lookX), lookY(lookY),lookZ(lookZ), upX(upX), upY(upY),
        upZ(upZ), fov(fov), near(near),far(far) {}

CameraStatus::CameraStatus():
    posX(0.f), posY(0.f), posZ(0.f),
    lookX(0.f), lookY(0.f),lookZ(0.f),
    upX(0.f), upY(1.f), upZ(0.f),
    fov(60), near(1),far(1000){}





void CameraStatus::CameraLookUp(){
    auto direction =GetDirection(
            posX,posY,posZ,
            lookX,lookY,lookZ);

    float y = direction->y;

    float angleYX = cosh(y) - (M_PI/2.f);
    float x = cos(angleYX);
    y = sin(angleYX);

    float z;

    if (direction->z != 0)
        z = ( (-direction->x * x) + (- direction->y * y)) / direction->z;
        //Caso esteja a lidar com o plano em que o z = 0
    else z = 0;

    free(direction);

    lookX += x;
    lookY += y;
    lookZ += z;
}

void CameraStatus::MoveCameraForward() {
    auto direction =GetDirection(
            lookX,lookY,lookZ,
            posX,posY,posZ);

    AddVectorCamera(direction);
}
void CameraStatus::MoveCameraRight() {
    auto direction =GetDirection(
            posX,posY,posZ,
            lookX,lookY,lookZ);

    float z = direction->z;

    float angleZXRight = cosh(z) + (M_PI/2.f);

    AddVectorCamera(CalculateNormalVector(direction,angleZXRight));
}

void CameraStatus::MoveCameraLeft() {
    auto direction =GetDirection(
            posX,posY,posZ,
            lookX,lookY,lookZ);

    float z = direction->z;
    float angleZXRight = cosh(z) - (M_PI/2.f);

    AddVectorCamera(CalculateNormalVector(direction,angleZXRight));
}

void CameraStatus::MoveCameraBackwards() {
    auto direction =GetDirection(
            posX,posY,posZ,
            lookX,lookY,lookZ);

    AddVectorCamera(direction);
}

void CameraStatus::AddVectorCamera(Vector3* direction) {
    //Adicionar o vetor direção à camara
    posX += direction->x * speed;
    posY += direction->y * speed;
    posZ += direction->z * speed;

    lookX += direction->x * speed;
    lookY += direction->y * speed;
    lookZ += direction->z * speed;
    free(direction);
}


Vector3* CameraStatus::CalculateNormalVector(Vector3 *direction, float angleZXRight) {
    float x = sin(angleZXRight);
    float z = cos(angleZXRight);
    float y;

    if (direction->y != 0)
        y = ( (-direction->x * x) + (- direction->z * z)) / direction->y;
        //Caso esteja a lidar com o plano em que o y = 0
    else y = 0;

    free(direction);
    direction = new Vector3(x,y,z);
    return direction;
}


void CameraStatus::RenderCameraScene() {
    gluLookAt(posX, posY, posZ,
              lookX, lookY, lookZ,
              upX, upY, upZ);
}

void CameraStatus::RenderCameraPerspective(float ratio) {
    gluPerspective(fov, ratio, near, far);
}

Vector3* CameraStatus::GetDirection(float x1,float y1,float z1,float x2,float y2,float z2){
    return GetDirection(Vector3(x1,y1,z1), Vector3(x2,y2,z2));
}

Vector3* CameraStatus::GetDirection(Vector3 position,Vector3 lookPosition){
    //Calcular a direçao que a camera está a olhar
    float directionX = position.x - lookPosition.x;
    float directionY = position.y - lookPosition.y;
    float directionZ = position.z - lookPosition.z;

    //Descobrir o vetor da direção que tem comprimento 1
    float magnitude = sqrt(directionX*directionX + directionY*directionY + directionZ*directionZ);
    directionX /= magnitude;
    directionY /= magnitude;
    directionZ /= magnitude;

    return new Vector3(directionX,directionY,directionZ);
}
