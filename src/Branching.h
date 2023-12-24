//
// Created by anike on 27-04-2023.
//

#ifndef INC_8085_CPP_BRANCHING_H
#define INC_8085_CPP_BRANCHING_H
#include "Essentials.h"

string JMP(string);

string JNC(string, string, vector<bool>&);

string JC(string, string , vector<bool>& );

string JZ(string, string , vector<bool>&);

string JNZ(string, string, vector<bool>&);
#endif //INC_8085_CPP_BRANCHING_H
