//
// Created by pinto on 02/05/22.
//

#ifndef MAIN_CPP_BEZIERPATCH_H
#define MAIN_CPP_BEZIERPATCH_H

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "../TransformationsDataStruct/Transformations.h"

using namespace std;

class Patch{
    vector<Vector3*> controlPoints;

public:
    Patch();
    Patch(vector<Vector3*>);
    vector<Vector3*> getCPoints();
    void addPoint(Vector3*);
};

int ParserBezierFile(int tess, string file);
void renderTeapot(int tess);

#endif //MAIN_CPP_BEZIERPATCH_H
