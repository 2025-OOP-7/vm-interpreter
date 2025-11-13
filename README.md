# vm-interpreter
# 🧠 Virtual Instruction Interpreter  
2025학년도 2학기 객체지향설계(00분반) 텀프로젝트  
Organization: [2025-oop-7](https://github.com/2025-oop-7)  

---

## 📘 프로젝트 개요

이 프로젝트는 **가상 명령어 해석기(Virtual Instruction Interpreter)** 를 구현하는 것을 목표로 합니다.  
입력으로 주어진 **바이너리 명령어 스트림(32bit 단위)** 을 해석하고,  
그에 해당하는 연산(MOV, ADD, PUSH, POP 등)을 수행하는 **가상 머신(Virtual Machine)** 을 설계합니다.

> 🎯 핵심 목표  
> - Command 패턴을 활용한 객체지향적 구조 설계  
> - 레지스터, 스택, 플래그 기반 가상 CPU 구현  
> - `.bin` 파일에 포함된 가상 명령어를 해석 및 실행  

---

## ⚙️ 실행 흐름 요약

```plaintext
[바이너리 입력 파일]
        ↓
 [Instruction Parser]
        ↓
 [Instruction 객체 생성 (Command Pattern)]
        ↓
 [VMContext에서 실행]
        ↓
 [결과 출력 (PRINT)]

🧩 구현 클래스 구조
클래스	설명
VMContext	가상 머신의 실행 상태 관리 (레지스터, 스택, 코드 메모리 등)
Instruction	모든 명령어의 추상 클래스. execute(VMContext&) 메서드 포함
Concrete Instructions	MOV, ADD, SUB, PUSH, POP, JMP, BE, BNE, PRINT 등
InstructionParser	32bit 바이트코드를 파싱하여 opcode / flag / operand 추출
Main (Runner)	프로그램 전체 흐름 제어 (파일 읽기 → 명령 실행 → 출력)


🧮 명령어 집합
명령어	설명
`MOV [REG], [VAL	REG]`
`ADD [REG], [VAL	REG]`
`SUB [REG], [VAL	REG]`
`MUL [REG], [VAL	REG]`
`CMP [REG], [VAL	REG]`
PUSH [REG]	스택에 값 푸시
POP [REG]	스택의 최상단 값을 팝
`JMP [VAL	REG]`
`BE [VAL	REG]`
`BNE [VAL	REG]`
`PRINT [REG	VAL]`
🧠 디자인 패턴

Command Pattern
각 명령어를 객체로 캡슐화하여 실행(execute)을 독립적으로 수행할 수 있게 설계합니다.
새로운 명령어 추가 시 기존 코드 수정 없이 확장 가능하도록 구조화했습니다.