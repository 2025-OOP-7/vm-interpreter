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

| 역할   | 담당자                        | 담당 파일                                                    |
| ------ | ----------------------------- | ------------------------------------------------------------ |
| 박유경 | InstructionParser 담당        | `InstructionParser.h`, `InstructionParser.cpp`               |
| 고윤서 | Instructions 담당             | `Instructions.h`, `Instructions.cpp`                         |
| 이혜린 | VMContext 담당                | `VMContext.h`, `VMContext.cpp`                               |
| 이호재 | InstructionFactory, main 담당 | `InstructionFactory.h`, `InstructionFactory.cpp`, `main.cpp` |

## 빌드 방법

```bash
mkdir -p build
clang++ -std=c++17 -Iinclude -Isrc -g src/*.cpp -o build/interpreter
```

## 실행 방법

```bash
./build/interpreter <바이너리_파일_경로>
```

예시:

```bash
./build/interpreter print5.bin
./build/interpreter addNprint.bin
./build/interpreter stack.bin
```

## 테스트 케이스 기대 출력

### print5.bin

```
5
```

### addNprint.bin

```
10
10
20
```

### stack.bin

```
1
2
3
4
5
5
4
3
2
1
```

## 구현된 명령어

- **MOV**: 레지스터 간 또는 레지스터-값 간 데이터 이동
- **ADD**: 덧셈 연산 (ZF/CF/OF 플래그 설정)
- **SUB**: 뺄셈 연산 (ZF/CF/OF 플래그 설정)
- **MUL**: 곱셈 연산 (ZF/CF/OF 플래그 설정)
- **CMP**: 비교 연산 (ZF/CF/OF 플래그 설정, 레지스터 변경 없음)
- **PUSH**: 스택에 값 푸시
- **POP**: 스택에서 값 팝하여 레지스터에 저장
- **JMP**: 무조건 점프
- **BE**: ZF가 1일 때 점프
- **BNE**: ZF가 0일 때 점프
- **PRINT**: 레지스터 또는 즉값 출력

## 기술 스택

- **언어**: C++17
- **컴파일러**: clang++
- **아키텍처**: Command 패턴, 인터프리터 패턴
