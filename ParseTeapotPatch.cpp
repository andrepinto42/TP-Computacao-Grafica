//
// Created by pinto on 30/04/22.
//

#include "ParseTeapotPatch.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
using std::ifstream;
using std::endl;
using std::cout;

int ParseTeapotPatch::Stuff() {



    ifstream indata; // indata is like cin
    char stringOuput[100]; // variable for input value
    indata.open("../teapot.patch"); // opens the file
    if(!indata) { // file couldn't be opened
        cout << "Error: file could not be opened" << endl;
        exit(1);
    }
    indata >> stringOuput;
    int numberPatches = atoi(stringOuput);

    //Just here to remove some trash
    std::string trash;
    getline(indata, trash);
    int *arrAll[numberPatches];

    int totalSize = numberPatches;

    while(numberPatches>0)
    {
        std::string dataStuff;
        getline(indata, dataStuff);

        int *arr = static_cast<int *> (malloc(sizeof(int) * 16));

        sscanf(&dataStuff[0], "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,%d",
               arr,arr+1,arr+2,arr+3,arr+4,arr+5,arr+6,arr+7,arr+8,arr+9,arr+10,arr+11,arr+12,arr+13,arr+14,arr+15 );

        arrAll[totalSize-numberPatches] = arr;

        numberPatches--;
    }

    for (int i = 0; i < totalSize; ++i) {
        for (int j = 0; j < 16; ++j) {
            cout << arrAll[i][j]<<", ";
        }
        cout<<"\n";
    }
    std::string numberPointsString;
    getline(indata, numberPointsString);

    int numberPoints = atoi(&numberPointsString[0]);

    float *allPoints[numberPoints];

    for (int i = 0; i < numberPoints; ++i) {
        std::string PointString;
        getline(indata, PointString);

        float* pointVector = static_cast<float *> (malloc(sizeof(float) * 3));

        sscanf(&PointString[0],"%f, %f, %f",pointVector,pointVector+1,pointVector+2);

        //Store the point that contains the informations about a 3d Vector;
        allPoints[i] = pointVector;
    }

    for (int i = 0; i < numberPoints; ++i) {
        cout<<allPoints[i][0]<<","<<allPoints[i][1]<< ","<<allPoints[i][2] <<"\n";

    }
    indata.close();
    cout << "End-of-file reached.." << endl;
}