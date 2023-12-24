#include "Essentials.h"
#include "Utils/Utils.h"

void ADD(string reg, map<char, string>& registers, vector<bool>& flag, map<string, string>& memory){
    if(reg.length()==1){
        if(validateMemRegister(reg) || validateRegister(reg)){
            if(reg=="M"){
                string valueH = registers['H'];
                string valueM = registers['L'];
                string addressM = valueH+valueM;
                if(validateMemory(addressM)){
                    registers['A'] = hexAdd(registers['A'], memory[addressM], flag);
                }
                else{
                    cout << "Invalid address" << endl;
                    exit(1);
                }
            }
            else{
                registers['A'] = hexAdd(registers['A'], registers[reg[0]], flag);
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

void ADI(string data, map<char, string>& registers, vector<bool>& flag){
    if(data.length()!=2 || !validateImmediateData(data)){
        cout << "Invalid value";
        exit(1);
    }
    else{
        registers['A'] = hexAdd(registers['A'], data, flag);
    }
}

void SUB(string reg, map<char, string>& registers, vector<bool>& flag, map<string, string>& memory){
    if(reg.length()==1){
        if(validateMemRegister(reg) || validateRegister(reg)){
            if(reg=="M"){
                string valueH = registers['H'];
                string valueM = registers['L'];
                string addressM = valueH+valueM;
                if(validateMemory(addressM)){
                    registers['A'] = hexSub(registers['A'], memory[addressM], flag);
                }
                else{
                    cout << "Invalid address" << endl;
                    exit(1);
                }
            }
            else{
                registers['A'] = hexSub(registers['A'], registers[reg[0]], flag);
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

void SUI(string data, map<char, string>& registers, vector<bool>& flag){
    if(data.length()!=2 || !validateImmediateData(data)){
        cout << "Invalid value";
        exit(1);
    }
    else{
        registers['A'] = hexSub(registers['A'], data, flag);
    }
}

void INR(string reg, map<char, string>& registers, vector<bool>& flag, map<string, string>& memory){
    if(reg.length()==1){
        if(validateMemRegister(reg) || validateRegister(reg)){
            if(reg=="M"){
                string valueH = registers['H'];
                string valueM = registers['L'];
                string addressM = valueH+valueM;
                if(validateMemory(addressM)){
                    memory[addressM] = hexAdd(memory[addressM], "01", flag);
                    flag[0]=false;
                    flag[4]=false;
                }
                else{
                    cout << "Invalid address" << endl;
                    exit(1);
                }
            }
            else{
                registers[reg[0]] = hexAdd(registers[reg[0]], "01", flag);
                flag[0]=false;
                flag[4]=false;
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

void INX(string reg, map<char, string>& registers, vector<bool>& flag){
    if(reg.length()==1){
        if(validRegisterPair(reg)){
            string valueA = registers[reg[0]];
            char regPair;
            if(reg=="B")
                regPair = 'C';
            else if(reg=="D")
                regPair = 'E';
            else
                regPair = 'L';
            string valueB = registers[regPair];
            string result = valueA+valueB;
            result = hexAdd16(result, "0001", flag, false);

            registers[reg[0]] = string(1,result[0])+string(1,result[1]);
            registers[regPair] = string(1, result[2])+string(1, result[3]);
        }
        else{
            cout << "Invalid register pair" << endl;
            exit(1);
        }
    }
    else{
        cout << "Invalid register";
        exit(1);
    }
}


void DCR(string reg, map<char, string>& registers, vector<bool>& flag, map<string, string>& memory){
    if(reg.length()==1){
        if(validateMemRegister(reg) || validateRegister(reg)){
            if(reg=="M"){
                string valueH = registers['H'];
                string valueM = registers['L'];
                string addressM = valueH+valueM;
                if(validateMemory(addressM)){
                    memory[addressM] = hexSub(memory[addressM], "01", flag);
                    flag[0]=false;
                    flag[4]=false;
                }
                else{
                    cout << "Invalid address" << endl;
                    exit(1);
                }
            }
            else{
                registers[reg[0]] = hexSub(registers[reg[0]], "01", flag);
                flag[0]=false;
                flag[4]=false;
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

void DCX(string reg, map<char, string>& registers, vector<bool>& flag){
    if(reg.length()==1){
        if(validRegisterPair(reg)){
            string valueA = registers[reg[0]];
            char regPair;
            if(reg=="B")
                regPair = 'C';
            else if(reg=="D")
                regPair = 'E';
            else
                regPair = 'L';
            string valueB = registers[regPair];
            string result = valueA+valueB;
            result = hexAdd16(result, twosComplement16("0001", flag), flag, false);

            registers[reg[0]] = string(1,result[0])+string(1,result[1]);
            registers[regPair] = string(1, result[2])+string(1, result[3]);
        }
        else{
            cout << "Invalid register pair" << endl;
            exit(1);
        }
    }
    else{
        cout << "Invalid register";
        exit(1);
    }
}

void DAD(string reg, map<char, string>& registers, vector<bool>& flag){
    if(reg.length()==1){
        if(validRegisterPair(reg)){
            string valueA = registers[reg[0]];
            char regPair;
            if(reg=="B")
                regPair = 'C';
            else if(reg=="D")
                regPair = 'E';
            else
                regPair = 'L';
            string valueB = registers[regPair];
            string result = valueA+valueB;

            string HL = registers['H']+registers['L'];
            result = hexAdd16(HL, result, flag, true);

            registers['H'] = string(1,result[0])+string(1,result[1]);
            registers['L'] = string(1, result[2])+string(1, result[3]);
        }
        else{
            cout << "Invalid register pair" << endl;
            exit(1);
        }
    }
    else{
        cout << "Invalid register";
        exit(1);
    }
}
