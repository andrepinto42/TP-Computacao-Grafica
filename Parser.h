//
// Created by pinto on 04/03/22.
//

#ifndef MAIN_CPP_PARSER_H
#define MAIN_CPP_PARSER_H


#include "CameraStatus.h"
#include "tinyxml/tinyxml.h"
#include "TransformationsDataStruct/Transformations.h"
#include <vector>

class Parser {
public:
    static void XML_Parse(CameraStatus **cam,Transformations** rootTransformation);

    static CameraStatus *getCameraStatus(TiXmlElement *pBody, TiXmlElement *pParms);

    static void TransformGroupElement(TiXmlElement *pElement,Transformations** root);

    static void InsertTransformations(Transformations *const *root, TiXmlElement *pTransform);

    static void InsertNextChildrenTransformation(Transformations *const *root, TiXmlElement *pAnotherGroup);

    static void InsertModelsName(Transformations *const *root, TiXmlElement *pModels);

    static void
    CreateCatmull(Transformations *const *root, float x, float y, float z, TiXmlElement *iterator, const char *time,
                  const char *align);
};


#endif //MAIN_CPP_PARSER_H
