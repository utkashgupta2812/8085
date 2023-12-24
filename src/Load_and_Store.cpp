#include "Essentials.h"
#include "Utils/Utils.h"

void MOV(string regA, string regB, map<char, string>& registers, map<string, string>& memory){
    if(regA.length()==1 && regB.length()==1){
        if(regA!="M" && regB!="M"){
            if(validateRegister(regA) && validateRegister(regB)){
                registers[regA[0]] = registers[regB[0]];
            }
            else{
                cout << "Invalid register";
                exit(1);
            }
        }
        else if(regA!="M" && regB=="M"){
            if(validateRegister(regA)){
                string addr = registers['H'] + registers['L'];
                if(validateMemory(addr)){
                    registers[regA[0]] = memory[addr];
                }
                else{
                    cout << "Invalid register";
                    exit(1);
                }
            }
            else{
                cout << "Invalid register";
                exit(1);
            }
        }
        else if(regA=="M" && regB!="M"){
            if(validateRegister(regB)){
                string addr = registers['H'] + registers['L'];
                if(validateMemory(addr)){
                    memory[addr] = registers[regB[0]];
                }
                else{
                    cout << "Invalid register";
                    exit(1);
                }
            }
            else{
                cout << "Invalid register";
                exit(1);
            }
        }
        else{
            cout << "Invalid register";
            exit(1);
        }
    }
    else{
        cout << "Invalid register";
        exit(1);
    }
}

void MVI(string regA, string data, map<char, string>& registers, map<string, string>& memory){
    if(validateImmediateData(data) && data.length()==2){
        if(regA=="M"){
            string addr = registers['H']+registers['L'];
            if(validateMemory(addr)){
                memory[addr] = data;
            }
            else{
                cout << "Invalid data" << endl;
                exit(1);
            }
        }
        else if(validateRegister(regA)){
            registers[regA[0]] = data;
        }
        else{
            cout << "Invalid register" << endl;
            exit(1);
        }
    }
    else{
        cout << "Invalid arguments" << endl;
        exit(1);
    }
}

void LXI(string regA, string data, map<char, string>& registers){
    if(data.length()==4 && validateImmediateData(data) && validRegisterPair(regA)){
        char regPair;

        if(regA=="B")
            regPair='C';
        if(regA=="D")
            regPair='E';
        if(regA=="H")
            regPair='L';

        registers[regA[0]] = data.substr(0, 2);
        registers[regPair] = data.substr(2, 4);
    }
    else{
        cout << "Invalid arguments" << endl;
        exit(1);
    }
}

void LDA(string addr, map<char, string>& registers, map<string, string>& memory){
    if(validateMemory(addr)){
        registers['A'] = memory[addr];
    }
    else{
        cout << "Invalid address";
        exit(1);
    }
}

void STA(string addr, map<char, string>& registers, map<string, string>& memory){
    if(validateMemory(addr)){
        memory[addr] =  registers['A'];
    }
    else{
        cout << "Invalid address";
        exit(1);
    }
}

void LHLD(string addr, map<char, string>& registers, map<string, string>& memory){
    vector<bool> dummy;
    string nextAddr = hexAdd16(addr, "0001", dummy, false);
    if(validateMemory(addr) && validateMemory(nextAddr)){
        registers['L'] = memory[addr];
        registers['H'] = memory[nextAddr];
    }
    else{
        cout << "Invalid address";
        exit(1);
    }
}

void SHLD(string addr, map<char, string>& registers, map<string, string>& memory){
    vector<bool> dummy;
    string nextAddr = hexAdd16(addr, "0001", dummy, false);
    if(validateMemory(addr) && validateMemory(nextAddr)){
        memory[addr] = registers['L'];
        memory[nextAddr] = registers['H'];
    }
    else{
        cout << "Invalid address";
        exit(1);
    }
}

void STAX(string reg, map<char, string>& registers, map<string, string>& memory){
    if(validRegisterPair(reg)){
        char regPair;
        if(reg=="B")
            regPair='C';
        if(reg=="D")
            regPair='E';
        if(reg=="H")
            regPair='L';

        string addr = registers[reg[0]] + registers[regPair];
        if(validateMemory(addr)){
            memory[addr] = registers['A'];
        }
        else{
            cout << "Invalid address" << endl;
            exit(1);
        }
    }
    else{
        cout << "Invalid register pair" << endl;
        exit(1);
    }
}

void XCHG(map<char, string>& registers){
    swap(registers['H'], registers['D']);
    swap(registers['L'], registers['E']);
}
void SET(string addr, string val, map<string, string>& memory){
    if(validateImmediateData(val) && validateMemory(addr)){
        memory[addr]=val;
    }
    else{
        cout << "ERROR" << endl;
        exit(1);
    }
}