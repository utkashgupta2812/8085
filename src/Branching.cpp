#include "Essentials.h"
#include "Utils/Utils.h"

string increaseAddr(string pc){
    vector<bool> dummy;
    return hexAdd16(pc, "0003", dummy, false);
}
string JMP(string addr){
    if(validateMemory(addr))
        return addr;
    exit(1);
}

string JNC(string addr, string pc, vector<bool>& flag){
    if(!flag[0]){
        if(validateMemory(addr))
            return addr;
        else exit(1);
    }
    else{
        return increaseAddr(pc);
    }
}
string JC(string addr, string pc, vector<bool>& flag){
    if(flag[0]){
        if(validateMemory(addr))
            return addr;
        else exit(1);
    }
    else{
        return increaseAddr(pc);
    }
}

string JZ(string addr, string pc, vector<bool>& flag){
    if(flag[6]){
        if(validateMemory(addr))
            return addr;
        else exit(1);
    }
    else{
        return increaseAddr(pc);
    }
}

string JNZ(string addr, string pc, vector<bool>& flag){
    if(!flag[6]){
        if(validateMemory(addr))
        return addr;
        else exit(1);
    }
    else
        return increaseAddr(pc);
}