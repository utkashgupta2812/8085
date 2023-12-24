#include "Essentials.h"
#include "Utils/Utils.h"

void CMA(map<char, string>& registers){
    string comp = complement(registers['A']);
    registers['A'] = comp;
}

void CMP(string reg, map<char, string>& registers, vector<bool>& flags, map<string, string>& memory){
    if(reg.length()==1){
        if(validateMemRegister(reg) || validateRegister(reg)){
            string value = "";
            if(reg=="M"){
                string address = registers['H']+registers['L'];
                if(validateMemory(address)){
                    value = memory[address];
                }
                else{
                    cout << "Invalid memory address" << endl;
                    exit(1);
                }
            }
            else{
                value = registers[reg[0]];
            }
            if(!value.empty()){
                compare(registers['A'], value, flags);
            }
        }
        else{
            cout << "Invalid register" << endl;
            exit(1);
        }
    }
    else{
        cout << "Invalid register";
        exit(1);
    }
}
