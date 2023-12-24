#include <fstream>
#include "Essentials.h"
#include "Utils/Utils.h"
#include "Debugger.h"

class Emulator8085 {
    map<string, string> memory;
    vector<bool> flag; // CY _ P _ AC _ Z S
    map<char, string> registers; // A B C D E H L
    string start;
    string pc;
    vector<string> programList;
public:
    Emulator8085() {
        flag = vector<bool>(8, false);
        registers = {{'A', "NULL"},
                     {'B', "NULL"},
                     {'C', "NULL"},
                     {'D', "NULL"},
                     {'E', "NULL"},
                     {'H', "NULL"},
                     {'L', "NULL"}};
        start = "";
        pc = "";
    }

    void init() {
        cout << "Enter a starting address: ";
        cin >> start;

        if (!validateMemory(start)) {
            cout << "Invalid address." << endl;
            exit(1);
        }
        pc = start;
        programList.push_back(pc);
    }


//    void dummyProcess() {
////        ADD INSTRUCTION CHECK - DONE
////        registers['A']="FF";
////        registers['D']="34";
////
////        ADD("D", registers, flag, memory);
////
////        memory["2050"]="34";
////        registers['A'] = "FF";
////        registers['H'] = "20";
////        registers['L'] = "50";
////        ADD("M", registers, flag, memory);
//
//
////        ADI INSTRUCTION CHECK
////        registers['A'] = "FF";
////        ADI("0F", registers, flag);
//
////            registers['A'] = "01";
////            registers['D'] = "02";
////            //0000 0011
////            SUB("D", registers, flag, memory);
////            registers['A'] = "01";
////            registers['B'] = "01";
////            CMP("B", registers, flag, memory );
////            registers['A'] = "02";
////            CMP("B", registers, flag, memory);
//
//            registers['A'] = "05";
//            registers['B'] = "07";
//            registers['H'] = "20";
//            registers['L'] = "50";
//            memory["2070"] = "30";
//            MOV("M", "B", registers, memory);
//            MVI("A", "10", registers, memory);
//            LXI("B", "1000", registers);
//            LDA("2070", registers, memory);
//            STA("3050", registers, memory);
//
//            memory["2050"] = "10";
//            memory["2051"] = "20";
//            LHLD("2050", registers, memory);
//
//            SHLD("FFFF", registers, memory);
//
//            memory["4020"]="30";
//            registers['B'] = "40";
//            registers['C'] = "20";
//            STAX("B", registers, memory);
//
//            registers['D'] = "60";
//            registers['E'] = "70";
//            XCHG(registers);
//            cout << validateLine("LXI H 2050") << endl;
//    }

    void userInput(){
        string in;
        cin.ignore();
        cout << "Type '.' to exit" << endl;
        cout << pc << " : ";
        string lastPC;
        while(true){
            getline(cin, in);
            if(validateLine(in)){
                memory[pc]=in;
                lastPC=pc;
                pc = updatePC(pc, memory);
                cout << pc << " : ";
            }
            else if(in=="."){
                break;
            }
            else{
                cout << in << endl;
                cout << "Wrong instruction" << endl;
                exit(1);
            }
        }
        memory.erase(pc);
        pc=lastPC;
        executionNoDebugger(start, pc, memory, flag, registers);
    }

    void userInputDebugger(){
        string in;
        cin.ignore();
        cout << "Type '.' to exit" << endl;
        cout << pc << " : ";
        string lastPC;
        while(true){
            getline(cin, in);
            if(validateLine(in)){
                memory[pc]=in;
                lastPC=pc;
                pc = updatePC(pc, memory);
                cout << pc << " : ";
                programList.push_back(pc);
            }
            else if(in=="."){
                break;
            }
            else{
                cout << in << endl;
                cout << "Wrong instruction" << endl;
                exit(1);
            }
        }
        programList.pop_back();
        memory.erase(pc);
        pc=lastPC;
        executeDebugger(start, pc, memory, registers, flag, programList);
    }

    void programFile(string name){
        string in;
        ifstream file(name);

        if(!file.is_open()) {
            cout << "Error opening file." << endl;
            exit(1);
        }
        string lastPC;

        while(getline(file, in)){
            if(validateLine(in)){
                memory[pc]=in;
                lastPC=pc;
                pc = updatePC(pc, memory);
            }
            else{
                cout << in << endl;
                cout << "Wrong instruction" << endl;
                exit(1);
            }
        }
        memory.erase(pc);
        pc=lastPC;
        executionNoDebugger(start, pc, memory, flag, registers);
    }

    void programFileDebugger(string name){
        cin.ignore();
        string in;
        ifstream file(name);

        if(!file.is_open()) {
            cout << "Error opening file." << endl;
            exit(1);
        }
        string lastPC;

        while(getline(file, in)){
            if(validateLine(in)){
                memory[pc]=in;
                lastPC=pc;
                pc = updatePC(pc, memory);
                programList.push_back(pc);
            }
            else{
                cout << in << endl;
                cout << "Wrong instruction" << endl;
                exit(1);
            }
        }
        programList.pop_back();
        memory.erase(pc);
        pc=lastPC;
        executeDebugger(start, pc, memory, registers, flag, programList);
    }

    void display() {
        vector<string> flags = {"CY", "_", "P", "_", "AC", "_", "Z", "S"};
        cout << endl;
        cout << "FLAGS: " << endl;
        for (int i = 0; i < static_cast<int>(flag.size()); i++) {
            cout << flags[i] << " : ";
            cout << flag[i] << endl;
        }
        cout << endl;

        cout << "USED MEMORY: " << endl;
        for (auto it: memory) {
            cout << it.first << " : " << it.second << endl;
        }
        cout << endl;

        cout << "REGISTERS: " << endl;
        for (auto it: registers) {
            cout << it.first << " : " << it.second << endl;
        }

    }
};

int main(int argc, char *args[]) {
    Emulator8085 emu;
    emu.init();

//    string result;
//    result = hexAdd("FF", "34", emu.flag);
//    cout << result;

    cout << endl;
    if (argc == 1) {
        cout << "Input the code" << endl; //User inputs code
        emu.userInput();
    } else if (argc == 2) {
        if (!strcmp(args[1], "--debugger")) {
            cout << "Opening debugger" << endl;
            emu.userInputDebugger();
        } else {
            cout << "Executing code from " << args[1] << endl;
            emu.programFile(args[1]);
        }
    } else if (argc == 3) {
        if (strcmp(args[2], "--debugger")) {
            cout << "Invalid argument" << endl;
            exit(1);
        } else {
            cout << "Opening debugger with program from " << args[1] << endl;
            emu.programFileDebugger(args[1]);
        }
    }

    emu.display();
}