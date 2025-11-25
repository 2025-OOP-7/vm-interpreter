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
./build/interpreter test_arith.bin
./build/interpreter test_cmp_flags.bin
./build/interpreter test_branch.bin
./build/interpreter test_stack_extra.bin
```

## 테스트 케이스

### 기본 테스트 케이스

#### print5.bin

**목적**: PRINT 명령어 기본 동작 확인

```
5
```

#### addNprint.bin

**목적**: ADD 연산 및 PRINT 동작 확인

```
10
10
20
```

#### stack.bin

**목적**: PUSH/POP 스택 동작 확인 (LIFO)

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

### 고급 테스트 케이스

#### test_arith.bin

**목적**: 산술 연산(ADD, SUB, MUL) 및 레지스터 간 데이터 이동(MOV) 검증

```
27
22
44
44
```

#### test_cmp_flags.bin

**목적**: CMP 명령어의 플래그 설정 정확성 검증

```
1
0
0
0
1
0
0
0
1
```

**검증 내용**:

- `result == 0` → ZF=1, CF=0, OF=0
- `result > 0` → ZF=0, CF=1, OF=0
- `result < 0` → ZF=0, CF=0, OF=1

#### test_branch.bin

**목적**: 분기 명령어(BE, BNE, JMP) 및 조건부 점프 검증

```
2
4
7
6
```

**검증 내용**:

- BE (Branch if Equal): ZF=1일 때 점프
- BNE (Branch if Not Equal): ZF=0일 때 점프
- JMP (Jump): 무조건 점프
- JMP with Register: 레지스터 값을 PC로 사용

#### test_stack_extra.bin

**목적**: 스택 기본 동작 추가 검증

```
3
2
1
```

### 테스트 결과 요약

| 테스트 케이스        | 목적                     | 결과    |
| -------------------- | ------------------------ | ------- |
| print5.bin           | PRINT 기본 동작          | ✅ 통과 |
| addNprint.bin        | ADD 연산 및 PRINT        | ✅ 통과 |
| stack.bin            | PUSH/POP LIFO 동작       | ✅ 통과 |
| test_arith.bin       | 산술 연산 (ADD/SUB/MUL)  | ✅ 통과 |
| test_cmp_flags.bin   | CMP 플래그 설정          | ✅ 통과 |
| test_branch.bin      | 분기 명령어 (BE/BNE/JMP) | ✅ 통과 |
| test_stack_extra.bin | 스택 기본 동작           | ✅ 통과 |

**전체 테스트 통과율**: 7/7 (100%)

## 구현된 명령어

### 산술 연산

- **MOV**: 레지스터 간 또는 레지스터-값 간 데이터 이동
- **ADD**: 덧셈 연산 (ZF/CF/OF 플래그 설정)
- **SUB**: 뺄셈 연산 (ZF/CF/OF 플래그 설정)
- **MUL**: 곱셈 연산 (ZF/CF/OF 플래그 설정)
- **CMP**: 비교 연산 (ZF/CF/OF 플래그 설정, 레지스터 변경 없음)

### 스택 조작

- **PUSH**: 스택에 값 푸시
- **POP**: 스택에서 값 팝하여 레지스터에 저장

### 제어 흐름

- **JMP**: 무조건 점프 (즉값 또는 레지스터 값으로 점프)
- **BE**: ZF가 1일 때 점프 (Branch if Equal)
- **BNE**: ZF가 0일 때 점프 (Branch if Not Equal)

### 입출력

- **PRINT**: 레지스터 또는 즉값 출력

**총 11개 명령어 구현 완료**

## 기술 스택

- **언어**: C++17
- **컴파일러**: clang++
- **아키텍처**: Command 패턴, Factory 패턴, 인터프리터 패턴

## 구현 완성도

- ✅ 모든 11개 명령어 구현 완료
- ✅ 9개 레지스터 모두 지원 (R0, R1, R2, PC, SP, BP, ZF, CF, OF)
- ✅ 플래그 설정 정확성 검증 완료
- ✅ 스택 오버플로우/언더플로우 안전 처리
- ✅ 비트 파싱 정확성 검증 완료
- ✅ 엔디언 처리 정확성 검증 완료
- ✅ 분기 명령어 정확성 검증 완료
- ✅ 모든 공개 테스트 케이스 통과 (7/7, 100%)

## 프로젝트 구조

```
vm-interpreter/
├── include/              # 헤더 파일
│   ├── Instruction.h
│   ├── InstructionParser.h
│   ├── InstructionFactory.h
│   ├── VMContext.h
│   ├── registers.h
│   └── runner.h
├── src/                  # 소스 파일
│   ├── InstructionParser.cpp
│   ├── Instructions.h
│   ├── Instructions.cpp
│   ├── InstructionFactory.cpp
│   ├── VMContext.cpp
│   ├── runner.cpp
│   └── main.cpp
├── docs/                 # 문서
│   └── architecture.md
├── tests/                # 테스트 파일
│   └── data/
├── *.bin                 # 테스트 바이너리 파일
├── CMakeLists.txt
├── README.md
└── REPORT.md             # 상세 보고서
```

## 상세 문서

더 자세한 내용은 [REPORT.md](./REPORT.md)를 참고하세요.
