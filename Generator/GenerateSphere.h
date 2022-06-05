//
// Created by pinto on 12/03/22.
//

#ifndef MAIN_CPP_GENERATESPHERE_H
#define MAIN_CPP_GENERATESPHERE_H

float *GetNormal(float *arr1, float *arr2, float *arr3);
void cross(float *a, float *b, float *res);
void normalize(float *a);
void direction(float *a,float *b, float *res);

class GenerateSphere {
public:
    void static DrawSphere(float radius, int slices, int stacks);
};


#endif //MAIN_CPP_GENERATESPHERE_H
