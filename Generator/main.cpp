#include <iostream>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include <math.h>
#include "main.h"
#include "GenerateCube.h"
#include "GenerateSphere.h"
#include "GenerateCone.h"
#include "Vector3.h"

void DrawSquare(float x, float z, float length);


static std::vector<Vector3> allVectors;

void main::PushVertex(float x, float y, float z) {
    Vector3 *v1 =  new Vector3(x,y,z);
    allVectors.push_back(*v1);
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

    for (int i = 0; i <allVectors.size() ; i++) {
        TiXmlElement * cxn = new TiXmlElement( "Vertex" );
        root->LinkEndChild( cxn );
        cxn->SetDoubleAttribute("x", allVectors[i].x);
        cxn->SetDoubleAttribute("y", allVectors[i].y);
        cxn->SetDoubleAttribute("z", allVectors[i].z);
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
        GenerateCube::DrawPlanesY(size,divisions);
        GenerateCube::DrawPlanesX(size,divisions);
        GenerateCube::DrawPlanesZ(size,divisions);

        SaveAllVerticesXML(argv[4]);
    }
    if (strcmp("plane",argv[1]) == 0)
    {
        std::cout << "hello";
        float size = atof( argv[2]);
        float divisions = atof( argv[3]);
        GenerateCube::DrawPlaneY(size,divisions);

        SaveAllVerticesXML(argv[4]);
    }

    if (strcmp("sphere",argv[1]) == 0)
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

    if (strcmp("cone",argv[1]) == 0)
    {
        std::cout << "cone";
        float radius = atof( argv[2]);
        float height = atof( argv[3]);
        int slices = atoi( argv[4]);
        int stacks = atoi( argv[5]);

        GenerateCone::GenerateConeFunc(radius,height,slices,stacks);

        SaveAllVerticesXML(argv[6]);
    }



    return 0;
}

