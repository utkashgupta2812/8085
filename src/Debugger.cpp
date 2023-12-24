#include "Essentials.h"
#include "Utils/Utils.h"

void executeDebugger(string start, string end, map<string, string>& memory, map<char, string>& registers, vector<bool>& flag, vector<string>& programList){
    set<int> breakpoints;
    string in;
    cout << endl << "DEBUGGER MODE" << endl;
    cout << "(To check all commands, enter help)" << endl;
    while(true) {
        cout << "> ";
        getline(cin, in);

        string split;
        vector<string> inArr;

        for(char i : in){
            if(i!=' '){
                split+=i;
            }
            else if(!split.empty()){
                inArr.push_back(split);
                split="";
            }
        }
        if(!split.empty())
            inArr.push_back(split);

        if(in=="help"){
            cout << "break or b `line no.`: Set breakpoint"
                     << endl << "run or r: Run the program until breakpoint(s)"
                    << endl << "step or s: Run one instruction"
                    << endl << "print or p `register/memory address`: Print the value at register/memory address"
                    << endl << "quit or q:  Quits the debugger" << endl;
        }
        else if(in=="q" || in=="quit"){
            break;
        }
        else if(inArr[0]=="break" || inArr[0]=="b"){
            int lineNum = stoi(inArr[1]);
            if(lineNum<=static_cast<int>(programList.size()) && lineNum>0)
                breakpoints.insert(lineNum);
            else
                cout << "Invalid line number" << endl;
        }
        else if((inArr[0]=="print" || inArr[0]=="p")){
            if(inArr[1].length()==1 && validateRegister(inArr[1])){
                cout << "Value at " << inArr[1] << ": " << registers[inArr[1][0]] << endl;
            }
            else if(inArr[1].length()==4 && validateMemory(inArr[1])){
                cout << "Value at " << inArr[1] << ": " << memory[inArr[1]] << endl;
            }
            else{
                cout << "Invalid!" << endl;
            }
        }
        else if(in=="step" || in=="s"){
            if(!start.empty() && start.compare(end)<=0){
                execute(memory[start], start, memory, flag, registers);
            }
            else{
                cout << "Program has finished executing." << endl;
            }
        }
        else if(in=="run" || in=="r"){
            if(!start.empty() && start.compare(end)<=0){
                if(breakpoints.empty()){
                    while(start.compare(end)<=0){
                        execute(memory[start], start, memory, flag, registers);
                    }
                }
                else{
                    auto it = breakpoints.begin();
                    int lineNum = *it;

                    while(start.compare(programList[lineNum-1]) <= 0){
                        execute(memory[start], start, memory, flag, registers);
                    }

                    breakpoints.erase(it);
                }
            }
            else{
                cout << "End of the program" << endl;
                cout << "Exit? (Y/N): ";
                cin >> in;
                if(in == "Y" || in == "y"){
                    exit(0);
                }
                else if(in=="N" || in=="n"){
                    cin.ignore();
                    continue;
                }
                else{
                    cout << "Invalid option" << endl;
                    exit(1);
                }
            }
        }
        else{
            cout << "Wrong command" << endl;
        }
    }
}