//
// Created by pinto on 04/03/22.
//

#include "Parser.h"
#include <stdio.h>
#include <iostream>
#include <vector>

#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include "CameraStatus.h"
#include "TransformationsDataStruct/Transformations.h"
#include "TextureManager.h"
#include "LightComponent.h"

using namespace std;


void Parser::XML_Parse(CameraStatus **cam,vector<LightComponent*> *lights, Transformations **rootTransformations) {
    char nameFile[] = "../solarsystem_withMeteorite.xml";

    TiXmlDocument doc;
    if (!doc.LoadFile(nameFile)) {
        std::cout << "Error loading file " << nameFile;
    }

    TiXmlElement *pRoot, *pCamera, *pParms;
    pRoot = doc.FirstChildElement("world");

    if (!pRoot)
        return;

    pCamera = pRoot->FirstChildElement("camera");
    //Assign the value so it can be stored in the main class
    if (pCamera)
        *cam = getCameraStatus(pCamera, pParms);

    auto pLights = pRoot->FirstChildElement("lights");
    if (pLights)
    {
        getLightsScene(pLights,lights);
    }
    //Second Phase
    auto pAnotherGroup = pRoot->FirstChildElement("group");
    while (pAnotherGroup) {
        InsertNextChildrenTransformation(rootTransformations, pAnotherGroup);
        pAnotherGroup = pAnotherGroup->NextSiblingElement("group");
    }
}

CameraStatus *Parser::getCameraStatus(TiXmlElement *pBody, TiXmlElement *pParms) {
    pParms = pBody->FirstChildElement("position"); //now params

    float posX = atof(pParms->Attribute("x"));
    float posY = atof(pParms->Attribute("y"));
    float posZ = atof(pParms->Attribute("z"));

    pParms = pParms->NextSiblingElement();
    float lookX = atof(pParms->Attribute("x"));
    float lookY = atof(pParms->Attribute("y"));
    float lookZ = atof(pParms->Attribute("z"));


    pParms = pParms->NextSiblingElement();
    float upX = atof(pParms->Attribute("x"));
    float upY = atof(pParms->Attribute("y"));
    float upZ = atof(pParms->Attribute("z"));


    pParms = pParms->NextSiblingElement();
    float fov = atof(pParms->Attribute("fov"));
    float near = atof(pParms->Attribute("near"));
    float far = atof(pParms->Attribute("far"));

    CameraStatus *cam = new CameraStatus(
            posX, posY, posZ,
            lookX, lookY, lookZ,
            upX, upY, upZ,
            fov, near, far);
    return cam;
}

void Parser::TransformGroupElement(TiXmlElement *pGroup, Transformations **root) {

    auto pTransform = pGroup->FirstChildElement("transform");
    if (pTransform)
        InsertTransformations(root, pTransform);

    auto pModels = pGroup->FirstChildElement("models");
    if (pModels)
        InsertModelsName(root, pModels);

    auto pAnotherGroup = pGroup->FirstChildElement("group");
    while (pAnotherGroup) {
        InsertNextChildrenTransformation(root, pAnotherGroup);
        pAnotherGroup = pAnotherGroup->NextSiblingElement("group");
    }

}

void Parser::InsertModelsName(Transformations *const *root, TiXmlElement *pModels) {
    auto pModel = pModels->FirstChildElement();
    while (pModel) {
        // E necessario duplicar a string por alguma razao estranha
        (*root)->allParentModelsName.push_back(strdup(pModel->Attribute("file")));

        auto pTexture = pModel->FirstChildElement("texture");
        if (pTexture)
        {
            auto texture_ID = InitializeTexture(pTexture->Attribute("file"));

            //Creates a new Structure
            TextureStruct* textureStruct = new TextureStruct();

            textureStruct->texture_ID = texture_ID;
            textureStruct->bufferTexture_ID = Transformations::buffersTexture[Transformations::globalCurrentPositionTexture];
            Transformations::globalCurrentPositionTexture +=1;

            (*root)->arraytextureStruct.push_back(textureStruct);
            //Store the position of the texture
            (*root)->positionOfTexture.push_back((*root)->allParentModelsName.size()-1);

            std::cout<<"Texture id "<<textureStruct->texture_ID<< " ID DO BUFFER ->" << textureStruct->bufferTexture_ID << "\n";
        }
        //Check if has more materials
        auto pColor = pModel->FirstChildElement("color");
        if (pColor)
        {
            InitializeMaterials(root, pColor);
        }
        pModel = pModel->NextSiblingElement("model");
    }
    cout << "Inserted these models ->";
    for (auto string: (*root)->allParentModelsName) {
        cout << string << "\n";
    }
}

void Parser::InitializeMaterials(Transformations *const *root, TiXmlElement *pColor) {
    TypeOfMaterial* newMaterial = new TypeOfMaterial();

    auto pDiffuse = pColor->FirstChildElement("diffuse");
    if (pDiffuse)
    {
        newMaterial->arrDifuse[0] = atof(pDiffuse->Attribute("R"));
        newMaterial->arrDifuse[1] = atof(pDiffuse->Attribute("G"));
        newMaterial->arrDifuse[2] = atof(pDiffuse->Attribute("B"));
    }

    auto pSpecular = pColor->FirstChildElement("specular");
    if (pSpecular)
    {
        newMaterial->arrSpecular[0] = atof(pSpecular->Attribute("R"));
        newMaterial->arrSpecular[1] = atof(pSpecular->Attribute("G"));
        newMaterial->arrSpecular[2] = atof(pSpecular->Attribute("B"));
    }


    auto pAmbient = pColor->FirstChildElement("ambient");
    if (pAmbient)
    {
        newMaterial->arrAmbient[0] = atof(pAmbient->Attribute("R"));
        newMaterial->arrAmbient[1] = atof(pAmbient->Attribute("G"));
        newMaterial->arrAmbient[2] = atof(pAmbient->Attribute("B"));
    }

    auto pEmissive = pColor->FirstChildElement("emissive");
    if (pEmissive)
    {
        newMaterial->arrEmissive[0] = atof(pEmissive->Attribute("R"));
        newMaterial->arrEmissive[1] = atof(pEmissive->Attribute("G"));
        newMaterial->arrEmissive[2] = atof(pEmissive->Attribute("B"));
    }

    auto pShininess = pColor->FirstChildElement("shininess");
    if (pShininess)
    {
        newMaterial->shininess = atof(pShininess->Attribute("value"));
    }

    (*root)->arrayTypeOfMaterials.push_back(newMaterial);
    int indexOfMaterial = (*root)->allParentModelsName.size()-1;
    (*root)->positionOfMaterial.push_back(indexOfMaterial);
}


void Parser::InsertNextChildrenTransformation(Transformations *const *root, TiXmlElement *pAnotherGroup) {
    //Create a new Tranformation object and store it in the dataStruct of the parent
    Transformations *anotherTransformation = new Transformations();
    (*root)->allChildrenTransformation.push_back(anotherTransformation);

    TransformGroupElement(pAnotherGroup, &anotherTransformation);
}


void Parser::InsertTransformations(Transformations *const *root, TiXmlElement *pTransform) {
    float x, y, z, angle;
    TiXmlElement* iterator = pTransform->FirstChildElement();

    while(iterator)
    {
        auto name =iterator->Value();

        //Check if translate can describe catmull-rom Curves
        if (strcmp(name,"translate") == 0)
        {
            auto time=iterator->Attribute("time");
            auto align =iterator->Attribute("align");
            //Check if its the special behaviour of the catmull-rom
            if (time!= nullptr && align != nullptr)
            {
                CreateCatmull(root, x, y, z, iterator, time, align);

                //Skip to next iteration
                iterator = iterator->NextSiblingElement();
                continue;
            }
        }

        x = atof(iterator->Attribute("x"));
        y = atof(iterator->Attribute("y"));
        z = atof(iterator->Attribute("z"));
        if (strcmp(name,"translate") == 0)
        {
            auto t = new T_Translate(x, y, z);
            (*root)->parentAllTransforms.push_back(t);
        }
        else if (strcmp(name,"scale") == 0)
        {
            auto t = new T_Scale (x, y, z);
            (*root)->parentAllTransforms.push_back(t);
        }
        else if (strcmp(name,"rotate") == 0)
        {
            Transform* t;
            const char* timeRotate;
            //Check if exists the special atribute time
            if ( (timeRotate = iterator->Attribute("time")) != nullptr)
            {
                float timeSeconds = atof(timeRotate);
                t = new T_Rotate_Time(timeSeconds,x,y,z);
            }
            else
            {
                angle = atof(iterator->Attribute("angle"));
                t = new T_Rotate (angle,x, y, z);
            }

            (*root)->parentAllTransforms.push_back(t);
        }
        else
        {
            std::cout <<"Error parsing XML in the transform method";
        }

        iterator = iterator->NextSiblingElement();
    }
}

void Parser::CreateCatmull(Transformations *const *root,
                      float x, float y, float z,
                      TiXmlElement *iterator, const char *time,const char *align)
{
    vector<float> all_points;
    auto points = iterator->FirstChildElement();
    while(points)
    {
        x = atof(points->Attribute("x"));
        y = atof(points->Attribute("y"));
        z = atof(points->Attribute("z"));
        all_points.push_back(x);
        all_points.push_back(y);
        all_points.push_back(z);

        points = points->NextSiblingElement();
    }

    bool align_Value = strcmp(align, "True") == 0;
    int numberOfPoints = all_points.size()/3;

    auto arrayPoints = static_cast<float **>(malloc(sizeof(float *) * numberOfPoints ));
    for (int i = 0; i < numberOfPoints; ++i) {
        arrayPoints[i] = static_cast<float *>(malloc(sizeof(float) * 3));
        //Alocate space for the 3 float coordenates
        for (int j = 0; j < 3; ++j) {
            arrayPoints[i][j] = all_points[i*3 + j];
        }
    }

    //Create a catmull struct to store the necessary data
    auto t = new T_Catmull_Rom(arrayPoints,  numberOfPoints, align_Value, atof(time));
    (*root)->parentAllTransforms.push_back(t);

    all_points.clear();
}

void Parser::getLightsScene(TiXmlElement *pElement, vector<LightComponent *> *vector1) {
    auto lightComp =    pElement->FirstChildElement("light");

    while(lightComp)
    {
        auto tipo =lightComp->Attribute("type");
        if (strcmp(tipo,"point") ==0)
        {
            LightPoint* l1 = new LightPoint();

            l1->currentPos = LightComponent::currentNumberLights;
            LightComponent::currentNumberLights++;

            l1->posX = atof(lightComp->Attribute("posX"));
            l1->posY = atof(lightComp->Attribute("posY"));
            l1->posZ = atof(lightComp->Attribute("posZ"));

            vector1->push_back(l1);
        }
        else if (strcmp(tipo,"directional") == 0)
        {
            LightDirection* l1 = new LightDirection();

            l1->currentPos = LightComponent::currentNumberLights;
            LightComponent::currentNumberLights++;

            l1->posX = atof(lightComp->Attribute("dirX"));
            l1->posY = atof(lightComp->Attribute("dirY"));
            l1->posZ = atof(lightComp->Attribute("dirZ"));

            vector1->push_back(l1);
        }

        lightComp = lightComp->NextSiblingElement();
    }

}

