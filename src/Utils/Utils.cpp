#include <bitset>
#include "../Essentials.h"
#include "../Arithmetic.h"
#include "../Load_and_Store.h"
#include "../Logical.h"
#include "../Branching.h"

int to_int(char &num) {
    map<char, int> mp ={
            {'0', 0},
            {'1', 1},
            {'2', 2},
            {'3', 3},
            {'4', 4},
            {'5', 5},
            {'6', 6},
            {'7', 7},
            {'8', 8},
            {'9', 9},
            {'A', 10},
            {'B', 11},
            {'C', 12},
            {'D', 13},
            {'E', 14},
            {'F', 15}
    };
    return mp[num];
}

char to_char(int& num){
    map<int, char> mp ={
            {0, '0'},
            {1, '1'},
            {2, '2'},
            {3, '3'},
            {4, '4'},
            {5, '5'},
            {6, '6'},
            {7, '7'},
            {8, '8'},
            {9, '9'},
            {10, 'A'},
            {11, 'B'},
            {12, 'C'},
            {13, 'D'},
            {14, 'E'},
            {15, 'F'}
    };

    return mp[num];
}

bool validateMemory(string &mem) {
    if (mem.length() != 4)
        return false;
    for (char &c: mem) {
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')))
            return false;
    }
    return true;
}

bool validateRegister(string &mem) {
    if (mem == "A" || mem == "B" || mem == "C" || mem == "D" || mem == "E" || mem == "H" || mem == "L")
        return true;
    return false;
}

bool validRegisterPair(string &mem){
    if(mem=="B" || mem=="D" || mem=="H")
        return true;
    return false;
}


bool validateMemRegister(string &mem) {
    return mem == "M";
}

bool validateImmediateData(string& data){
    for(char& c: data){
        if(!((c>='A' && c<='F') || (c>='0' && c<='9')))
            return false;
    }
    return true;
}

void setFlags(vector<bool>& flag, string result){
    flag[6] = (result=="00");
    int hex = stoi(result, nullptr, 16);
    bitset<8> bits(hex);

    if((bits.count()%2)==0)
        flag[2] = true;
    else
        flag[2] = false;

    flag[7] = bits[7];
}

string hexAdd(string regA, string regB, vector<bool>& flag) {
    string result = "  ";
    int carry = 0;
    for (int i = 1; i >= 0; i--) {
        int sum = to_int(regA[i]) + to_int(regB[i]) + carry;
        if(sum>=16){
            carry=1;
            sum = sum - 16;
        }
        else{
            carry=0;
        }

        result[i] = to_char(sum);
        if(i==1)
            flag[4]= carry == 1; //AC
    }
    flag[0]= carry == 1; // CY
    setFlags(flag, result);
    return result;
}

string hexAdd16(string regA, string regB, vector<bool>& flag, bool isDAD) {
    string result = "    ";
    int carry = 0;
    for (int i = 3; i >= 0; i--) {
        int sum = to_int(regA[i]) + to_int(regB[i]) + carry;
        if(sum>=16){
            carry=1;
            sum = sum - 16;
        }
        else{
            carry=0;
        }
        if(isDAD)
            flag[0] = carry==1;
        result[i] = to_char(sum);
    }

    return result;
}

string complement(string& data){
    string result = "  ";
    string comp = "FF";
    for(int i=data.length()-1; i>=0; i--) {
        int diff = to_int(comp[i]) - to_int(data[i]);
        result[i] = to_char(diff);
    }

    return result;
}

void compare(string valA, string valB, vector<bool>& flag){
    int numA = stoi(valA, 0, 16);
    int numB = stoi(valB, 0, 16);
    if(numA < numB) {
        flag[0] = true;
    } else if(numA==numB){
        flag[6]=true;
    }
    else{
        flag[0]=false;
        flag[6]=false;
    }
}
string twosComplement(string& data, vector<bool> flag){
    string result = complement(data);
    result = hexAdd(result, "01", flag);
    return result;
}

string twosComplement16(string data, vector<bool> flag){
    string result = "    ";
    string comp = "FFFF";
    for(int i=data.length()-1; i>=0; i--) {
        int diff = to_int(comp[i]) - to_int(data[i]);
        result[i] = to_char(diff);
    }
    result = hexAdd16(result, "0001", flag, false);
    return result;
}

string hexSub(string regA, string regB, vector<bool>& flag){
    string result = hexAdd(regA, twosComplement(regB, flag), flag);
    flag[4]=false;
    flag[0]=false;

    for(int i=regA.length()-1; i>=0; i--){
        int digitA = to_int(regA[i]);
        int digitB = to_int(regB[i]);
        if(digitA < digitB){
            if(i==1)
                flag[4] = true;
            if(i==0)
                flag[0] = true;
        }
    }
    return result;
}

bool instructionExists(string instruction){
    vector<string> ins = {"ADI", "ADD", "SUB", "SUI", "INX", "INR", "DCR", "DCX", "DAD",
                          "MOV", "MVI", "LXI", "LDA", "STA", "LHLD", "SHLD", "STAX", "XCHG",
                          "CMA", "CMP", "JMP", "JC", "JNC", "JZ", "JNZ", "HLT", "SET"};

    for(auto& i: ins){
        if(i==instruction){
            return true;
        }
    }
    return false;
}

bool validateLength(string instruction, vector<string> argument){
    if(argument.empty() || argument.size()>3)
        return false;

    vector<string> noArgs = {"HLT", "CMA", "XCHG"};
    vector<string> oneArgs = {"CMP", "JMP", "JC", "JNC", "JZ", "JNZ", "LDA", "STA", "LHLD", "SHLD", "STAX",
                              "ADD", "ADI", "SUB", "SUI", "INR", "INX", "DCR", "DCX", "DAD"};
    vector<string> twoArgs = {"SET", "MOV", "MVI", "LXI"};

    if(argument.size()==1){
        for(auto& s: noArgs){
            if(instruction==s)
                return true;
        }
    }
    else if(argument.size()==2){
        for(auto& s: oneArgs){
            if(instruction==s)
                return true;
        }
    }
    else{
        for(auto& s: twoArgs){
            if(instruction==s)
                return true;
        }
    }

    return false;
}

bool validateLine(string line){
    vector<string> lineArr;
    string split;

    for(char i : line){
        if(i!=' ' && i!=','){
            split+=i;
        }
        else if(!split.empty()){
            lineArr.push_back(split);
            split="";
        }
    }
    if(!split.empty())
        lineArr.push_back(split);
    if(instructionExists(lineArr[0]) && validateLength(lineArr[0], lineArr)) {
        bool flag = true;
        if(lineArr.size()>1){
            for(int i=1; i<static_cast<int>(lineArr.size()); i++){
                int argLen = lineArr[i].length();
                switch(argLen){
                    case 1:
                        flag = validateRegister(lineArr[i]) || validateMemRegister(lineArr[i]);
                        break;
                    case 2:
                        flag = validateImmediateData(lineArr[i]);
                        break;
                    case 4:
                        flag = validateMemory(lineArr[i]);
                        break;
                    default:
                        flag = false;
                        break;
                }
                if(!flag)
                    return flag;
            }
        }
        return true;
    }
    return false;
}

int instructionSize(string instruction){
    vector<string> one = {"MOV","ADD", "INR", "DCR", "LDAX", "STAX", "HLT", "SUB", "XCHG", "CMA", "CMP", "INX", "DCX", "DAD"};
    vector<string> two = {"MVI", "ADI", "SUI"};
    vector<string> three = {"LXI", "LDA", "STA", "LHLD", "SHLD", "JMP", "JC", "JNC", "JZ", "JNZ", "SET"};

    for(string& s: one){
        if(instruction==s)
            return 1;
    }
    for(string& s: two){
        if(instruction==s)
            return 2;
    }
    for(string& s: three){
        if(instruction==s)
            return 3;
    }
    return 0;
}

string updatePC(string pc, map<string, string>& memory){
    string instruction = memory[pc];
    string processInstruction;
    if(instruction == "XCHG" || instruction == "HLT" || instruction=="CMA")
        processInstruction = instruction;
    else{
        int j = 0;
        int i;
        for(i = 0; i<static_cast<int>(instruction.length()); i++){
            if(instruction[i]==' ')
                break;
        }
        processInstruction = instruction.substr(j, i-j);
    }
    int size = instructionSize(processInstruction);
    vector<bool> dummyFlag;
    string result = pc;
    for(int i = 0; i<size; i++){
        result = hexAdd16(result, "0001", dummyFlag, false);
        memory[result] = memory[pc];
    }
    pc = result;
    return pc;
}

void execute(string& instruction, string& pc, map<string, string>& memory, vector<bool>& flag, map<char, string>& registers){
    vector<string> insArr;
    string split;

    for(char i : instruction){
        if(i!=' ' && i!=','){
            split+=i;
        }
        else if(!split.empty()){
            insArr.push_back(split);
            split="";
        }
    }
    if(!split.empty())
        insArr.push_back(split);

    vector<bool> dummy;
    if(insArr[0]=="MOV"){
        MOV(insArr[1], insArr[2], registers, memory);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="MVI"){
        MVI(insArr[1], insArr[2], registers, memory);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="LXI"){
        LXI(insArr[1], insArr[2], registers);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="LDA"){
        LDA(insArr[1], registers, memory);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="STA"){
        STA(insArr[1], registers, memory);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="LHLD"){
        LHLD(insArr[1], registers, memory);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="SHLD"){
        SHLD(insArr[1], registers, memory);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="STAX"){
        STAX(insArr[1], registers, memory);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="XCHG"){
        XCHG(registers);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="ADD"){
        ADD(insArr[1], registers, flag, memory);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="ADI"){
        ADI(insArr[1], registers, flag);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="SUB"){
        SUB(insArr[1], registers, flag, memory);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="SUI"){
        SUI(insArr[1], registers, flag);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="INR"){
        INR(insArr[1], registers, flag, memory);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="INX"){
        INX(insArr[1], registers, flag);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="DCR"){
        DCR(insArr[1], registers, flag, memory);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="DCX"){
        DCX(insArr[1], registers, flag);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="DAD"){
        DAD(insArr[1], registers, flag);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="CMA"){
        CMA(registers);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="CMP"){
        CMP(insArr[1], registers, flag, memory);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="SET"){
        SET(insArr[1], insArr[2], memory);
        pc = hexAdd16(pc, "000"+to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="HLT"){
        pc = hexAdd16(pc, "000"+ to_string(instructionSize(insArr[0])), dummy, false);
    }
    else if(insArr[0]=="JMP"){
        pc = JMP(insArr[1]);
    }
    else if(insArr[0]=="JC"){
        pc = JC(insArr[1], pc, flag);
    }
    else if(insArr[0]=="JNC"){
        pc = JNC(insArr[1], pc, flag);
    }
    else if(insArr[0]=="JZ"){
        pc = JZ(insArr[1], pc, flag);
    }
    else if(insArr[0]=="JNZ"){
        pc = JNZ(insArr[1], pc, flag);
    }
    else{
        pc = "";
    }
}

void executionNoDebugger(string start, string end, map<string, string>& memory, vector<bool>& flag, map<char, string>& registers){
    while(start.compare(end)<=0){
        execute(memory[start], start, memory, flag, registers);
    }
}