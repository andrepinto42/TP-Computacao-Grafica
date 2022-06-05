//
// Created by pinto on 07/03/22.
//

#include <valarray>
#include <GL/glu.h>
#include <iostream>
#include "CameraStatus.h"
#include "../Generator/Vector3.h"

static int speed = 1.f;
Vector3* normalize(Vector3* v)
{
    float magnitude = sqrt(v->x * v->x + v->y*v->y + v->z*v->z);
    v->x = v->x/magnitude;
    v->y = v->y/magnitude;
    v->z = v->z/magnitude;
}

/*
 * Constructors
 */
CameraStatus::CameraStatus(float posX, float posY, float posZ,
                           float lookX, float lookY, float lookZ,
                           float upX,float upY, float upZ,
                           float fov, float near, float far) :
                           posX(posX), posY(posY), posZ(posZ),
                           upX(upX), upY(upY),upZ(upZ), fov(fov), near(near),far(far)
{

    auto dir = GetDirection(lookX,lookY,lookZ,posX,posY,posZ);
    normalize(dir);

    this->lookX = posX + dir->x;
    this->lookY = posY + dir->y;
    this->lookZ = posZ + dir->z;

    std::cout << this->lookX<<" " <<this->lookY<< " "<< this->lookZ << "\n";

    free(dir);
}

#include <math.h>

const static float angleIncrement = 5.f;
static int currentAngleHorizontal = 0.f;
static int currentAngleVertical = 0.f;

void CameraStatus::LookNewDir()
{
    float x = cos(currentAngleVertical * M_PI/180.f) * cos(currentAngleHorizontal * M_PI / 180.f);
    float z = cos(currentAngleVertical * M_PI/180.f) * sin(currentAngleHorizontal * M_PI / 180.f);
    float y = sin(currentAngleVertical * M_PI / 180.f);

    this->lookX = posX + x;
    this->lookY = posY + y;
    this->lookZ = posZ + z;

    std::cout << lookX<<" " <<lookY<< " "<< lookZ << "\n";
}
void CameraStatus::RotateRightNew()
{
    currentAngleHorizontal += angleIncrement;
    LookNewDir();
}

void CameraStatus::RotateLeftNew()
{
    currentAngleHorizontal -= angleIncrement;
    LookNewDir();
}

void CameraStatus::RotateUpNew()
{
    currentAngleVertical += angleIncrement;
    LookNewDir();
}


void CameraStatus::RotateDownNew()
{
    currentAngleVertical -= angleIncrement;
    LookNewDir();
}
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
//    roll++;

    auto direction =GetDirection(
            posX,posY,posZ,
            lookX,lookY,lookZ);

    auto dir = CrossProduct(Vector3(0.f,1.f,0.f),*direction);

    auto interpolatedVector = Interpolate(dir,direction,0.1f);

    float distance = Distance(posX,posY,posZ,
                              lookX,lookY,lookZ);

    interpolatedVector->x = interpolatedVector->x * distance;
    interpolatedVector->y = interpolatedVector->y * distance;
    interpolatedVector->z = interpolatedVector->z * distance;

    lookX = interpolatedVector->x;
    lookY = interpolatedVector->y;
    lookZ = interpolatedVector->z;

    free(dir);
    free(interpolatedVector);
}
void CameraStatus::CameraLookDown(){
//    roll--;
    auto direction =GetDirection(
            posX,posY,posZ,
            lookX,lookY,lookZ);

    float distXZ = sqrt( direction->x * direction->x + direction->z * direction->z);
    double angle =asin( direction->x / distXZ);

    float dist = DistanceLookAt();
    std::cout << "Polar : dist= " <<dist<<" angle-> "<<angle<<"\n";

    //Increase by a little
    angle +=0.01f;

    lookX = sin(angle) * dist;
    lookZ = cos(angle) * dist;

    std::cout << lookX<<" " <<lookY<<" "<< lookZ<<"\n";
    free(direction);
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

Vector3* CameraStatus::Interpolate(Vector3 *vector1, Vector3 *vector2, float interpolation) {
    Vector3* vect = new Vector3(
            vector1->x * (1 - interpolation) + vector2->x * interpolation,
            vector1->y * (1 - interpolation) + vector2->y * interpolation,
            vector1->z * (1 - interpolation) + vector2->z * interpolation);
    return vect;
}

float CameraStatus::Distance(float x, float y, float z, float x1, float y1, float z1) {
    return sqrt( pow(x-x1,2) + pow(y-y1,2) +pow(z-z1,2));
}

float CameraStatus::DistanceLookAt() {
    return Distance(posX,posY,posZ,
             lookX,lookY,lookZ);
}
