//
// Created by anike on 08-04-2023.
//

#ifndef INC_8085_CPP_ARITHMETIC_H
#define INC_8085_CPP_ARITHMETIC_H

#include "Essentials.h"

void ADD(string, map<char, string> &, vector<bool> &, map<string, string> &);

void ADI(string, map<char, string> &, vector<bool> &);

void SUB(string , map<char, string>& , vector<bool>& , map<string, string>& );

void SUI(string, map<char, string> &, vector<bool> &);

void INR(string , map<char, string>& , vector<bool>& , map<string, string>& );

void INX(string, map<char, string>&, vector<bool>&);

void DCR(string , map<char, string>& , vector<bool>& , map<string, string>& );

void DCX(string, map<char, string>&, vector<bool>&);

void DAD(string, map<char, string>&, vector<bool>&);
#endif //INC_8085_CPP_ARITHMETIC_H
