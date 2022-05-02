//
// Created by pinto on 30/04/22.
//
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>

#include "ParseTeapotPatch.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
using std::ifstream;
using std::endl;
using std::cout;


void DONTKNOW();

void DrawQuadsWith2Curves(double **arrayCurve1, double **arrayCurve2, int num);

int numSegments = 16;

int **all_Curves;
float **all_Points;
int totalSize;

void p_2_GL(float* point)
{
    glVertex3d(point[0],point[1],point[2]);
}

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

    totalSize = numberPatches;

    all_Curves = static_cast<int **>(malloc(sizeof(int *) * totalSize));

    while(numberPatches>0)
    {
        std::string dataStuff;
        getline(indata, dataStuff);

        int *arr = static_cast<int *> (malloc(sizeof(int) * 16));

        sscanf(&dataStuff[0], "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,%d",
               arr,arr+1,arr+2,arr+3,arr+4,arr+5,arr+6,arr+7,arr+8,arr+9,arr+10,arr+11,arr+12,arr+13,arr+14,arr+15 );

        all_Curves[totalSize - numberPatches] = arr;

        numberPatches--;
    }

    for (int i = 0; i < totalSize; ++i) {
        for (int j = 0; j < 16; ++j) {
            cout << all_Curves[i][j] << ", ";
        }
        cout<<"\n";
    }
    std::string numberPointsString;
    getline(indata, numberPointsString);

    int numberPoints = atoi(&numberPointsString[0]);

    all_Points= static_cast<float **>(malloc(sizeof(float *) * numberPoints));

    for (int i = 0; i < numberPoints; ++i) {
        std::string PointString;
        getline(indata, PointString);

        float* pointVector = static_cast<float *> (malloc(sizeof(float) * 3));

        sscanf(&PointString[0],"%f, %f, %f",pointVector,pointVector+1,pointVector+2);

        //Store the point that contains the informations about a 3d Vector;
        all_Points[i] = pointVector;
    }

    for (int i = 0; i < numberPoints; ++i) {
        cout << all_Points[i][0] << "," << all_Points[i][1] << "," << all_Points[i][2] << "\n";

    }
    indata.close();
    cout << "End-of-file reached.." << endl;
}

void ParseTeapotPatch::Render() {
//    DONTKNOW();
}

int weight_ARRAY[16]={
        1,15,105,455,
        1365,3003,5005,6435,
        6435,5005,3003,1365,
        455,105,15,1
};

void v3_2_GL(double* d)
{
    glVertex3d(d[0],d[1],d[2]);
}

void DONTKNOW(){

    for (int k = 0; k < totalSize; ++k) {
        int *curva = all_Curves[k];
        glBegin(GL_LINE_STRIP);

        for (int i = 0; i <= numSegments; ++i) {
            float t = i / (float)numSegments;

            double* finalPoint = static_cast<double *>(malloc(sizeof(double) * 3));
            finalPoint[0] =0.f;
            finalPoint[1] =0.f;
            finalPoint[2] =0.f;

            //203, 203, 203, 203, 204, 205, 206, 207, 208, 208, 208, 208, 209, 210, 211, 212

            //Get the 3d_POINT from our struct
            //0,-1.5,2
            for (int j = 0; j < 4; ++j) {
                int index1 = curva[j*4 ];
                int index2 = curva[j*4 +1];
                int index3 = curva[j*4 +2];
                int index4 = curva[j*4 +3];

                float* P1 = all_Points[index1];
                float* P2 = all_Points[index2];
                float* P3 = all_Points[index3];
                float* P4 = all_Points[index4];

                // compute coefficients
                float k1 = (1 - t) * (1 - t) * (1 - t);
                float k2 = 3 * (1 - t) * (1 - t) * t;
                float k3 = 3 * (1 - t) * t * t;
                float k4 = t * t * t;
                // weight the four control points using coefficients
                finalPoint[0] = P1[0] * k1 + P2[0] * k2 + P3[0] * k3 + P4[0] * k4;
                finalPoint[1] = P1[1] * k1 + P2[1] * k2 + P3[1] * k3 + P4[1] * k4;
                finalPoint[2] = P1[2] * k1 + P2[2] * k2 + P3[2] * k3 + P4[2] * k4;

                v3_2_GL(finalPoint);
            }
        }
        glEnd();


    }

    //Start Drawing
//    for (int i = 0; i < totalSize-1; ++i) {
//        DrawQuadsWith2Curves(storePoints[i],storePoints[i+1],numSegments);
//    }

}

void DrawQuadsWith2Curves(double **arrayCurve1, double **arrayCurve2, int numSegments) {
    glBegin(GL_TRIANGLES);
    //Draw 2 triangle based on 2 curves that one next to another
    for (int i = 0; i < numSegments; ++i) {

        v3_2_GL(arrayCurve2[i]);
        v3_2_GL(arrayCurve1[i]);
        v3_2_GL(arrayCurve1[i + 1]);

        v3_2_GL(arrayCurve2[i]);
        v3_2_GL(arrayCurve1[i + 1]);
        v3_2_GL(arrayCurve2[i + 1]);

    }
    glEnd();
}
