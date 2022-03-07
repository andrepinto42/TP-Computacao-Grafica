//
// Created by pinto on 07/03/22.
//

#include "CameraStatus.h"

CameraStatus::CameraStatus(float posX, float posY, float posZ, float lookX, float lookY, float lookZ, float upX,
                           float upY, float upZ, float fov, float near, float far) :
        posX(posX), posY(posY), posZ(posZ),
        lookX(lookX), lookY(lookY),
        lookZ(lookZ), upX(upX), upY(upY),
        upZ(upZ), fov(fov), near(near),
        far(far)
        {

        }
