# 아키텍처 문서

## 컴포넌트 다이어그램

```
┌─────────────┐
│  main.cpp   │
└──────┬──────┘
       │
       ├──> InstructionParser ──> ParsedInstruction
       │
       ├──> InstructionFactory ──> Instruction*
       │
       └──> VMContext
            ├── 레지스터 (R0, R1, R2, PC, SP, BP)
            ├── 플래그 (ZF, CF, OF)
            └── 스택
```

## 데이터 흐름

1. **파일 입력**: 바이너리 파일(.bin)을 32bit 단위로 읽음
2. **파싱**: InstructionParser가 32bit 원시 명령어를 opcode/flag/operand로 분해
3. **팩토리**: InstructionFactory가 opcode/flag에 따라 적절한 Instruction 객체 생성
4. **실행**: 생성된 Instruction 객체의 execute() 메서드를 VMContext와 함께 호출
5. **출력**: PRINT 명령 시 콘솔에 결과 출력

## 역할 분담 요약

| 역할 | 담당 파일                       | 주요 책임                                                                       |
| ---- | ------------------------------- | ------------------------------------------------------------------------------- |
| A    | InstructionParser.\*            | 32bit 명령어 비트 파싱                                                          |
| B    | Instructions.\*                 | 모든 구체 명령어 구현 (MOV, ADD, SUB, MUL, CMP, PUSH, POP, JMP, BE, BNE, PRINT) |
| C    | VMContext.\*                    | VM 상태 관리 (레지스터, 스택, 플래그, 코드 메모리)                              |
| D    | InstructionFactory.\*, main.cpp | Instruction 객체 생성 및 전체 실행 흐름 제어                                    |

## 설계 의도

- **Command 패턴**: 각 명령어를 Instruction 객체로 캡슐화하여 확장성 확보
- **옵션 B 구조**: 모든 구체 명령어를 Instructions.h/.cpp 한 쌍에 모아 간결성 유지
- **분리된 책임**: 파싱, 생성, 실행, 상태 관리가 각각 독립된 컴포넌트로 분리
