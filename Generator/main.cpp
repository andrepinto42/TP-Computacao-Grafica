#include <iostream>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include <math.h>
#include "main.h"
#include "GenerateCube.h"
#include "GenerateSphere.h"
#include "GenerateCone.h"
#include "GenerateRing.h"
#include "Vector3.h"
#include "bezierPatch.h"

void DrawSquare(float x, float z, float length);


static std::vector<Vector3> allVectors;
static std::vector<Vector3> allNormals;

void main::PushVertex(float x, float y, float z) {
    Vector3 *v1 =  new Vector3(x,y,z);
    allVectors.push_back(*v1);
}


void main::PushNormal(float x, float y, float z) {
    Vector3 *v1 =  new Vector3(x,y,z);
    allNormals.push_back(*v1);
}

void SaveAllVerticesXML(char* nameFile) {
    TiXmlDocument doc;
    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
    doc.LinkEndChild( decl );

    TiXmlElement * root = new TiXmlElement( "Model" );
    doc.LinkEndChild( root );


    TiXmlElement * config = new TiXmlElement( "Configuration" );
    root->LinkEndChild( config );
    config->SetDoubleAttribute("VertexCount", allVectors.size());
    config->SetDoubleAttribute("NormalCount",allNormals.size());

    for (int i = 0; i <allVectors.size() ; i++) {
        TiXmlElement * cxn = new TiXmlElement( "Vertex" );
        root->LinkEndChild( cxn );
        cxn->SetDoubleAttribute("x", allVectors[i].x);
        cxn->SetDoubleAttribute("y", allVectors[i].y);
        cxn->SetDoubleAttribute("z", allVectors[i].z);
    }

    for (int i = 0; i < allNormals.size(); ++i) {
        TiXmlElement * cxn = new TiXmlElement( "Normal" );
        root->LinkEndChild( cxn );
        cxn->SetDoubleAttribute("x", allNormals[i].x);
        cxn->SetDoubleAttribute("y", allNormals[i].y);
        cxn->SetDoubleAttribute("z", allNormals[i].z);
    }

    doc.SaveFile(nameFile);
}

void printVertex(float x, float y, float z)
{
    std::cout << "<vertex x="<<x<<" y="<<y<<" z="<<z<<"/>\n";
}

int main(int argc, char* argv[]) {
    if (argc <= 3)
    {
        std::cout << "Not enough arguments provided";
        return -1;
    }

    if (strcmp("box",argv[1]) == 0)
    {
        float size = atof( argv[2]);
        float divisions = atof( argv[3]);
        std::cout << size << "<- size and divisions ->"<<divisions<<"\n";
        GenerateCube::DrawPlanesX(size,divisions);
        GenerateCube::DrawPlanesY(size,divisions);
        GenerateCube::DrawPlanesZ(size,divisions);

        SaveAllVerticesXML(argv[4]);
    }
    else if (strcmp("plane",argv[1]) == 0)
    {
        std::cout << "hello";
        float size = atof( argv[2]);
        float divisions = atof( argv[3]);
        GenerateCube::DrawPlaneY(size,divisions);

        SaveAllVerticesXML(argv[4]);
    }

    else if (strcmp("sphere",argv[1]) == 0)
    {
        if (argc == 4)
        {
            std::cout << "Not enough arguments for the sphere";
            return -1;
        }
        float radius = atof( argv[2]);
        int slices = atoi( argv[3]);
        int stacks = atoi( argv[4]);
        GenerateSphere::DrawSphere(radius,slices,stacks);

        SaveAllVerticesXML(argv[5]);
    }

    else if (strcmp("cone",argv[1]) == 0)
    {
        std::cout << "cone";
        float radius = atof( argv[2]);
        float height = atof( argv[3]);
        int slices = atoi( argv[4]);
        int stacks = atoi( argv[5]);

        GenerateCone::GenerateConeFunc(radius,height,slices,stacks);

        SaveAllVerticesXML(argv[6]);
    }
    else if (strcmp("ring",argv[1]) == 0)
    {
        std::cout << "ring";
        float smallerRadius = atof( argv[2]);
        float biggerRadius = atof( argv[3]);
        int slices = atoi( argv[4]);

        GenerateRing::GenerateRingFunc(smallerRadius,biggerRadius,slices);

        SaveAllVerticesXML(argv[5]);
    }
    else if(strcmp("bezier",argv[1]) == 0)
    {
        auto nameFileIn = argv[2];
        int tesselation = atoi(argv[3]);
        auto nameFileOut = argv[4];

        ParserBezierFile(tesselation, nameFileIn);
        SaveAllVerticesXML(nameFileOut);
    }
    else
    {
        std::cout << "Shape does not exist!\n";
    }

    return 0;
}

