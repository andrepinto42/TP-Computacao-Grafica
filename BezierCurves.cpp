//
// Created by pinto on 29/04/22.
//
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "math.h"
#include "BezierCurves.h"
#include "Generator/Vector3.h"
void DrawStuff(Vector3 P1,Vector3 P2,Vector3 P3,Vector3 P4);

Vector3 mult(Vector3 v,float f)
{
    return {v.x *f,v.y*f,v.z*f};
}


Vector3 add(Vector3 v,float f)
{
    return {v.x +f,v.y+f,v.z+f};

}
Vector3 add(Vector3 v,Vector3 v2)
{
    return {v.x +v2.x,v.y+v2.y,v.z+v2.z};
}
float radius = 1.f;
int maxNumberSegmentsCurve = 20;
void BezierCurves::DrawBezier()
{
    float angleDiff = (1.f/(float) maxNumberSegmentsCurve) *M_PI*2;
    float currentAngle=0.f;



    for (int i = 0; i < maxNumberSegmentsCurve; ++i) {
        float radiusUpperX = cos(currentAngle) * radius;
        float radiusUpperZ = sin(currentAngle) * radius;

        float radiusBiggerX = radiusUpperX * 1.3f;
        float radiusBiggerZ = radiusUpperZ * 1.3f;

        DrawStuff(
                Vector3 (radiusUpperX,sin(0.f),radiusUpperZ),
                Vector3 (radiusBiggerX,sin(M_PI/3.f),radiusBiggerZ),
                Vector3 (radiusBiggerX,sin(2.f*M_PI/3.f),radiusBiggerZ),
                Vector3 (radiusUpperX,sin(M_PI/2.f),radiusUpperZ)
        );
        currentAngle += angleDiff;
    }
//    DrawStuff(
//             Vector3 (1.f,sin(0.f),1.f),
//             Vector3 (1.3f,sin(M_PI/3.f),1.3f),
//             Vector3 (1.3f,sin(2.f*M_PI/3.f),1.3f),
//             Vector3 (1.f,sin(M_PI/2.f),1.f)
//            );
}

void DrawStuff(Vector3 P1,Vector3 P2,Vector3 P3,Vector3 P4)
{
    glBegin(GL_LINE_STRIP);
    int numSegments = 10;
    for (int i = 0; i <= numSegments; ++i) {
        float t = i / (float)numSegments;
        // compute coefficients
        float k1 = (1 - t) * (1 - t) * (1 - t);
        float k2 = 3 * (1 - t) * (1 - t) * t;
        float k3 = 3 * (1 - t) * t * t;
        float k4 = t * t * t;
        // weight the four control points using coefficients
        Vector3 Pt =
                add(
                add(
                add(
                        mult(P1, k1) ,
                        mult(P2 , k2) ) ,
                        mult(P3 , k3) ) ,
                        mult(P4 , k4));
        glVertex3d(Pt.x,Pt.y,Pt.z);
    }
    glEnd();
}
