//
// Created by anike on 13-04-2023.
//

#ifndef INC_8085_CPP_LOAD_AND_STORE_H
#define INC_8085_CPP_LOAD_AND_STORE_H
#include "Essentials.h"

void MOV(string, string, map<char, string>&, map<string, string>&);
void MVI(string, string, map<char, string>&, map<string, string>&);
void LXI(string, string, map<char, string>&);
void LDA(string, map<char, string>&, map<string, string>&);
void STA(string, map<char, string>&, map<string, string>&);
void LHLD(string, map<char, string>&, map<string, string>& );
void SHLD(string, map<char, string>&, map<string, string>& );
void STAX(string, map<char, string>&, map<string, string>& );
void XCHG(map<char, string>&);
void SET(string, string, map<string, string>&);
#endif //INC_8085_CPP_LOAD_AND_STORE_H
