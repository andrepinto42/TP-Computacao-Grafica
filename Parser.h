//
// Created by pinto on 04/03/22.
//

#ifndef MAIN_CPP_PARSER_H
#define MAIN_CPP_PARSER_H


#include "CameraStatus.h"
#include "tinyxml/tinyxml.h"
#include "TransformationsDataStruct/Transformations.h"
#include "LightComponent.h"
#include <vector>

class Parser {
public:
    static void XML_Parse(CameraStatus **cam, vector<LightComponent*> lights, Transformations** rootTransformation);

    static CameraStatus *getCameraStatus(TiXmlElement *pBody, TiXmlElement *pParms);

    static void TransformGroupElement(TiXmlElement *pElement,Transformations** root);

    static void InsertTransformations(Transformations *const *root, TiXmlElement *pTransform);

    static void InsertNextChildrenTransformation(Transformations *const *root, TiXmlElement *pAnotherGroup);

    static void InsertModelsName(Transformations *const *root, TiXmlElement *pModels);

    static void
    CreateCatmull(Transformations *const *root, float x, float y, float z, TiXmlElement *iterator, const char *time,
                  const char *align);

    static void InitializeMaterials(Transformations *const *root, TiXmlElement *pColor);

    static void getLightsScene(TiXmlElement *pElement, vector<LightComponent *> vector1);

    static void XML_Parse(CameraStatus **cam, vector<LightComponent *> *lights, Transformations **rootTransformations);

    static void getLightsScene(TiXmlElement *pElement, vector<LightComponent *> *vector1);
};


#endif //MAIN_CPP_PARSER_H
