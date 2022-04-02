//
// Created by pinto on 07/03/22.
//

#ifndef PARSER_CPP_TRANSFORMATIONS_H
#define PARSER_CPP_TRANSFORMATIONS_H
#include <vector>
using namespace std;

class Transformations {
public:
    Transformations(vector<const char *> *allNamesModels);

    vector<const char*> allNamesModels;
};


#endif //PARSER_CPP_TRANSFORMATIONS_H
