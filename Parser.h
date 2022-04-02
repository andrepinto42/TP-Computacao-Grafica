//
// Created by pinto on 04/03/22.
//

#ifndef MAIN_CPP_PARSER_H
#define MAIN_CPP_PARSER_H


#include "CameraStatus.h"
#include "tinyxml/tinyxml.h"
<<<<<<< HEAD
#include "TransformationsDataStruct/Transformations.h"
=======
>>>>>>> 767bf6e6f9c1f1d0463993ca5259d5db06a64718
#include <vector>

class Parser {
public:
<<<<<<< HEAD
    static std::vector<const char*> XML_Parse(CameraStatus **cam,Transformations** rootTransformation);

    static CameraStatus *getCameraStatus(TiXmlElement *pBody, TiXmlElement *pParms);

    static void TransformGroupElement(TiXmlElement *pElement,Transformations** root);
=======
    static std::vector<const char*> XML_Parse(CameraStatus **cam);

    static CameraStatus *getCameraStatus(TiXmlElement *pBody, TiXmlElement *pParms);
>>>>>>> 767bf6e6f9c1f1d0463993ca5259d5db06a64718
};


#endif //MAIN_CPP_PARSER_H
