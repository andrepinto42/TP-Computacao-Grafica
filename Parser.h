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
    static std::vector<const char*> XML_Parse(CameraStatus **cam,Transformations** rootTransformation);

    static CameraStatus *getCameraStatus(TiXmlElement *pBody, TiXmlElement *pParms);

    static void TransformGroupElement(TiXmlElement *pElement,Transformations** root);
};


#endif //MAIN_CPP_PARSER_H
