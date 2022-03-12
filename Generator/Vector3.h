//
// Created by pinto on 12/03/22.
//

#ifndef MAIN_CPP_VECTOR3_H
#define MAIN_CPP_VECTOR3_H

#include <string>

class Vector3{
public:
    float x;
    float y;
    float z;
    Vector3(float x1,float y1,float z1){
        x = x1;
        y = y1;
        z = z1;
    }
    std::basic_string<char> PrintVector()
    {
        const std::string s = "x =" + std::to_string(x) + " y =" + std::to_string(y) + " z=" +std::to_string(z);
        return s;
    }
};


#endif //MAIN_CPP_VECTOR3_H
