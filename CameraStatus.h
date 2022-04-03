//
// Created by pinto on 07/03/22.
//

#ifndef PARSER_CPP_CAMERASTATUS_H
#define PARSER_CPP_CAMERASTATUS_H

#include "Generator/Vector3.h"

class CameraStatus {
public:
    float posX;
    float posY;
    float posZ;

    float lookX;
    float lookY;
    float lookZ;

    float upX;
    float upY;
    float upZ;

    float fov;
    float near;
    float far;

    CameraStatus(float posX, float posY, float posZ, float lookX, float lookY, float lookZ, float upX, float upY,
                 float upZ, float fov, float near, float far);
    CameraStatus();

    Vector3 *GetDirection(float x1, float y1, float z1, float x2, float y2, float z2);

    static Vector3 *GetDirection(Vector3 position, Vector3 lookPosition);

    void MoveCameraForward();

    void MoveCameraRight();

    void MoveCameraLeft();

    void MoveCameraBackwards();

    void AddVectorCamera(Vector3 *direction);

    void RenderCameraScene();

    static Vector3 * CalculateNormalVector(Vector3 *direction, float angleZXRight);

    void RenderCameraPerspective(float ratio);

    void CameraLookUp();
};


#endif //PARSER_CPP_CAMERASTATUS_H
