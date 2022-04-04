//
// Created by pinto on 07/03/22.
//

#include <valarray>
#include <GL/glu.h>
#include <iostream>
#include "CameraStatus.h"
#include "Generator/Vector3.h"

static int speed = 1.f;

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




Vector3* CrossProduct(Vector3 v1,Vector3 v2){
    float x =v1.y*v2.z - v1.z*v2.y;
    float y = - (v1.x*v2.z - v1.z*v2.x);
    float z = v1.x*v2.y - v1.y * v2.x;
    return new Vector3(x,y,z);
}




void CameraStatus::MoveCameraForward() {
    auto direction =GetDirection(
            lookX,lookY,lookZ,
            posX,posY,posZ);

    AddVectorCamera(direction);
}

bool CheckIfCross(Vector3 vector1,Vector3 vector2){
    return (vector1.x -vector2.x + vector1.y -vector2.y + vector1.z - vector2.z) == 0;
}


//void CameraStatus::MoveCameraRight() {
//    auto direction =GetDirection(
//            posX,posY,posZ,
//            lookX,lookY,lookZ);
//
//    float z = direction->z;
//
//    float angleZXRight = cosh(z) + (M_PI/2.f);
//    auto dir = CalculateNormalVector(direction,angleZXRight);
//
//    std::cout << CheckIfCross(*direction,*dir)<<"<- cross\n";
//
//    AddVectorCamera(dir);
//}
void CameraStatus::MoveCameraRight() {
    auto direction =GetDirection(
            posX,posY,posZ,
            lookX,lookY,lookZ);

    auto dir = CrossProduct(Vector3(0.f,1.f,0.f),*direction);
    AddVectorCamera(dir);
}
void CameraStatus::MoveCameraLeft() {
    auto direction =GetDirection(
            posX,posY,posZ,
            lookX,lookY,lookZ);

    auto dir = CrossProduct(*direction, Vector3(0.f,1.f,0.f));
    AddVectorCamera(dir);
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

float pitch = 0.0f; // The rotation along the x axis
float yaw = 0.0f; // The rotation along the y axis
float roll = 0.0f; // The rotation along the z axis

void CameraStatus::CameraLookUp(){
    roll++;
}
void CameraStatus::CameraLookDown(){
    roll--;
}


void CameraStatus::CameraLookRight(){
    yaw--;
}
void CameraStatus::CameraLookLeft(){
    yaw++;
}
void CameraStatus::RenderCameraScene() {
    gluLookAt(posX, posY, posZ,
              lookX, lookY, lookZ,
              upX, upY, upZ);

    glRotatef(pitch, 1.0f, 0.0f, 0.0f);
    glRotatef(yaw, 0.0f, 1.0f, 0.0f);
    glRotatef(roll, 0.0f, 0.0f, 1.0f);

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
