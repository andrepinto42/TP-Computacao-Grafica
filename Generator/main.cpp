#include <iostream>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include <math.h>
#include "GenerateCube.h"


void DrawSquare(float x, float z, float length);




void SaveBoxAllVertexXML(char* nameFile) {
    TiXmlDocument doc;
    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
    doc.LinkEndChild( decl );

    TiXmlElement * root = new TiXmlElement( "Model" );
    doc.LinkEndChild( root );

    std::vector<Vector3> allVectors = GenerateCube::GetAllVertices();

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

        SaveBoxAllVertexXML(argv[4]);
    }
    if (strcmp("plane",argv[1]) == 0)
    {
        std::cout << "hello";
        float size = atof( argv[2]);
        float divisions = atof( argv[3]);
        GenerateCube::DrawPlaneY(size,divisions);

        SaveBoxAllVertexXML(argv[4]);
    }



    return 0;
}

