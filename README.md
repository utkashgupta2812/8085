# 8085-cpp
An 8085 Simulator written in CPP

## Supported instruction set
Arithmetic: ADD, ADI, SUB, INR, DCR, INX, DCX, DAD, SUI<br>
Logical: CMA,CMP<br>
Branching: JMP, JZ, JNZ, JC, JNC<br>
Load and Store: MOV, MVI, LXI, LDA, STA, LHLD, SHLD, STAX, XCHG<br>
SET instruction to set data into memory locations (Eg- SET 2500,04)

## Build (Windows)

Clone the project

```bash
  git clone https://github.com/theaniketnegi/8085-cpp.git
```

Go to the project directory

```bash
  cd 8085-cpp
```

Build using makefile

```bash
  make & make clean
```

## Run

Go to the build folder
```bash
  cd build
```

For command-line input
```bash
  8085_cpp
```

Through file input
```bash
  8085_cpp <filename>.asm
```

Debugger (with or without file)
```bash
  8085_cpp  --debugger
```
