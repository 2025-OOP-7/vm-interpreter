# VM-INTERPRETER

## 프로젝트 소개

가상 명령어 해석기(Virtual Instruction Interpreter) 프로젝트입니다.
32bit 바이너리 명령어 스트림을 해석하여 가상 머신에서 실행합니다.

## 실행 흐름

```
[바이너리 파일 (.bin)]
        ↓
[파일 읽기 (32bit 단위)]
        ↓
[InstructionParser: 명령어 파싱]
        ↓
[InstructionFactory: Instruction 객체 생성]
        ↓
[VMContext에서 execute 실행]
        ↓
[결과 출력 (PRINT)]
```

## 역할 분담

| 역할 | 담당자                        | 담당 파일                                                    |
| ---- | ----------------------------- | ------------------------------------------------------------ |
| A    | InstructionParser 담당        | `InstructionParser.h`, `InstructionParser.cpp`               |
| B    | Instructions 담당             | `Instructions.h`, `Instructions.cpp`                         |
| C    | VMContext 담당                | `VMContext.h`, `VMContext.cpp`                               |
| D    | InstructionFactory, main 담당 | `InstructionFactory.h`, `InstructionFactory.cpp`, `main.cpp` |

## 빌드 방법

```bash
mkdir build
cd build
cmake ..
make
```

## 실행 방법

```bash
./interpreter <바이너리_파일_경로>
```

예시:

```bash
./interpreter tests/data/lab0.bin
```

## 테스트 케이스 기대 출력

### 공개 TC 1

// TODO: 채우기

### 공개 TC 2

// TODO: 채우기

### 공개 TC 3

// TODO: 채우기
