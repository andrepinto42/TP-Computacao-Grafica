#include "bezierPatch.h"
#include "../TransformationsDataStruct/Transformations.h"
#include "main.h"

int* patches;
vector<Vector3*> allControlPoints;
int numeroPatches;
int numeroPontosControlo;


Vector3* get3D_PointBezier(float t, float* point1, float* point2, float* point3, float* point4) {
    float inverse_t = 1.0 - t;

    float weight0 = inverse_t * inverse_t * inverse_t;
    float weight1 = 3 * t * inverse_t * inverse_t;
    float weight2 = 3 * t * t * inverse_t;
    float weight3 = t * t * t;

    float x = weight0 * point1[0] + weight1 * point2[0] + weight2 * point3[0] + weight3 * point4[0];
    float y = weight0 * point1[1] + weight1 * point2[1] + weight2 * point3[1] + weight3 * point4[1];
    float z = weight0 * point1[2] + weight1 * point2[2] + weight2 * point3[2] + weight3 * point4[2];

    return new Vector3(x, y, z);
}


Vector3* findPointInGrid(float u, float v, int patch) {
    float matrix[4][3], finalQuadPoint[4][3];
    int j = 0, k = 0;
    for (int i = 0; i < 16; i++) {
        matrix[j][0] = allControlPoints[patches[16 * patch + i]]->x;
        matrix[j][1] = allControlPoints[patches[16 * patch + i]]->y;
        matrix[j][2] = allControlPoints[patches[16 * patch + i]]->z;

        j++;

        if (j % 4 == 0)
        {
            Vector3* p =
                    get3D_PointBezier(u, matrix[0], matrix[1], matrix[2], matrix[3]);
            finalQuadPoint[k][0] = p->x;
            finalQuadPoint[k][1] = p->y;
            finalQuadPoint[k][2] = p->z;
            j = 0;
            k++;
        }
    }
    return get3D_PointBezier(v, finalQuadPoint[0], finalQuadPoint[1], finalQuadPoint[2], finalQuadPoint[3]);

}

void renderBezierPatch(int tess, int n) {
    float shift = 1.0f / tess;

    float line, collum, next_line, next_collum;

    for (int i = 0; i < tess; i++) {
        for (int j = 0; j < tess; j++) {
            line = (float)i * shift;
            collum = (float)j * shift;
            next_line = (float)(i + 1) * shift;
            next_collum = (float)(j + 1) * shift;

            Vector3* p0 = findPointInGrid(line, collum, n);
            Vector3* p1 = findPointInGrid(line, next_collum, n);
            Vector3* p2 = findPointInGrid(next_line, collum, n);
            Vector3* p3 = findPointInGrid(next_line, next_collum, n);

            //First Triangle
            main::PushVertex(p0->x,p0->y,p0->z);
            main::PushVertex(p2->x,p2->y,p2->z);
            main::PushVertex(p3->x,p3->y,p3->z);

            //Second Triangle
            main::PushVertex(p0->x,p0->y,p0->z);
            main::PushVertex(p3->x,p3->y,p3->z);
            main::PushVertex(p1->x,p1->y,p1->z);
        }
    }
}

int ParserBezierFile(int tess, string file) {
    string filePath = "../" + file;

    string line;
    ifstream in(filePath);

    if (!in.is_open())
    {
        cout << "There was a error opening "<< filePath << " patch file" << "\n";
        return 0;
    }

    //Descobrir o numero de patches do ficheiro
    in >> numeroPatches;
    in.ignore(1, '\n');

    patches = (int*) malloc(sizeof(int) * numeroPatches * 16);

    for (int i = 0; i < numeroPatches; i++) {
        getline(in, line);

        istringstream lineStream(line);
        string a;

        for (int k = 0; k < 16; k++) {
            getline(lineStream, a, ',');
            patches[i * 16 + k] = stoi(a);
        }
    }

    in >> numeroPontosControlo;
    in.ignore(1, '\n');

    for (int i = 0; i < numeroPontosControlo; i++) {
        string a;
        string b;
        string c;

        getline(in, line);

        istringstream lineStream(line);

        getline(lineStream, a, ',');
        getline(lineStream, b, ',');
        getline(lineStream, c, '\n');
        allControlPoints.push_back(new Vector3(stof(a), stof(b), stof(c)));
    }

    for (int i = 0; i < numeroPatches; i++)
        renderBezierPatch(tess, i);

    std::cout << "File has been sucessfully interpreted!\n";
}
