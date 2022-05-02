#include "bezierPatch.h"
#include "../TransformationsDataStruct/Transformations.h"
#include "main.h"

int* patches;
vector<Vector3*> controls;
int n_patches;
int n_controls;
vector<Vector3*> vertexes;


void writePatch(string fileName);

Vector3* evalBezierCurve(float t, float* p1, float* p2, float* p3, float* p4) {
    float it = 1.0 - t;

    float weight0 = it * it * it;
    float weight1 = 3 * t * it * it;
    float weight2 = 3 * t * t * it;
    float weight3 = t * t * t;

    float x = weight0 * p1[0] + weight1 * p2[0] + weight2 * p3[0] + weight3 * p4[0];
    float y = weight0 * p1[1] + weight1 * p2[1] + weight2 * p3[1] + weight3 * p4[1];
    float z = weight0 * p1[2] + weight1 * p2[2] + weight2 * p3[2] + weight3 * p4[2];

    return new Vector3(x, y, z);
}


Vector3* bezierDetermine(float u, float v, int patch) {
    float matrix[4][3], res[4][3];
    int j = 0, k = 0;
    for (int i = 0; i < 16; i++) {
        matrix[j][0] = controls[patches[16 * patch + i]]->x;
        matrix[j][1] = controls[patches[16 * patch + i]]->y;
        matrix[j][2] = controls[patches[16 * patch + i]]->z;

        j++;

        if (j % 4 == 0) {
            Vector3* p =
                    evalBezierCurve(u,
                matrix[0], matrix[1], matrix[2], matrix[3]
            );
            res[k][0] = p->x;
            res[k][1] = p->y;
            res[k][2] = p->z;

            k++;
            j = 0;
        }
    }
    return evalBezierCurve(v,
                           res[0],
                           res[1],
                           res[2],
                           res[3]);

}

void toVector(float* a,float * b, float* res){
    res[0] = b[0]- a[0];
    res[1] = b[1]- a[1];
    res[2] = b[2]- a[2];
}


void renderBezierPatch(int tess, int n) {
    float shift = 1.0f / tess, u, v, u2, v2;


    for (int i = 0; i < tess; i++) {
        for (int j = 0; j < tess; j++) {
            u = i * shift;
            v = j * shift;
            u2 = (i + 1) * shift;
            v2 = (j + 1) * shift;

            Vector3* p0 = bezierDetermine(u, v, n);
            Vector3* p1 = bezierDetermine(u, v2, n);
            Vector3* p2 = bezierDetermine(u2, v, n);
            Vector3* p3 = bezierDetermine(u2, v2, n);

            float res[3];
            float res2[3];
            float resfinal[4];
            float a[3] = {p0->x,p0->y,p0->z};
            float b[3] = {p1->x,p1->y,p1->z};
            float c[3] = {p2->x,p2->y,p2->z};
            float d[3] = {p3->x,p3->y,p3->z};


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

void renderTeapot(int tess)
{
        for (int i = 0; i < n_patches; i++)
            renderBezierPatch(tess, i);
}

int bezierParser(int tess, string file, string nameFile) {
    string filePath = "../" + file;

    string line;
    ifstream inputFileStream(filePath);

    if (!inputFileStream.is_open()) {
        cout << "error opening "<< filePath << " patch file" << endl;
        return 0;
    }

    inputFileStream >> n_patches;
    inputFileStream.ignore(1, '\n');
    patches = (int*) malloc(sizeof(int) * n_patches * 16);

    for (int i = 0; i < n_patches; i++) {
        getline(inputFileStream, line);

        istringstream lineStream(line);
        string a;
        for (int k = 0; k < 16; k++) {
            getline(lineStream, a, ',');
            patches[i * 16 + k] = stoi(a);
        }
    }
    inputFileStream >> n_controls;
    inputFileStream.ignore(1, '\n');

    for (int i = 0; i < n_controls; i++) {
        getline(inputFileStream, line);

        istringstream lineStream(line);
        string a, b, c;
        getline(lineStream, a, ',');
        getline(lineStream, b, ',');
        getline(lineStream, c, '\n');
        controls.push_back(new Vector3(stof(a), stof(b), stof(c)));
        //printf("%f - ",controls[i*3+k]);

        //printf("\n");
    }
    //Dont save no points right now

    for (int i = 0; i < n_patches; i++)
        renderBezierPatch(tess, i);

    //Wait for writing
    writePatch(nameFile);
}



//MOdify to be able to write to xml
void writePatch(string fileName) {

    string filePath =  fileName;
    ofstream file(filePath);
    file << vertexes.size() << endl;
    for (int i = 0; i < vertexes.size(); i++) {
        file << vertexes[i]->x << " " << vertexes[i]->y << " " << vertexes[i]->z << endl;
    }
//    for (int i = 0; i < normal.size(); i++) {
//        file << normal[i]->getX() << " " << normal[i]->getY() << " " << normal[i]->getZ() << endl;
//    }

    file.close();
}