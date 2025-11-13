#pragma once

// [Owner: B] 파일명: Instructions.h
// [Role] 모든 구체 명령어 "선언"을 한 파일에 모음
// [Interfaces] 각 Instruction 클래스의 execute 선언
// [Notes] 옵션 B 사용: 모든 구체 명령어를 Instructions.h/.cpp 한 쌍에 모음

// [담당: B] 모든 구체 명령어 "선언"을 한 파일에 모음
// [구성 가이드] 아래 섹션별로 선언만(구현 X)
//
// ===== MOV =====
// class MovInstr : public Instruction { /* execute 선언 예시 주석 */ };
//
// ===== ADD =====
// class AddInstr : public Instruction { /* ... */ };
//
// ===== SUB =====
// ...
//
// ===== MUL =====
// ...
//
// ===== CMP =====  // 결과에 따라 ZF/CF/OF 설정(세부 규칙을 주석으로 문서화)
// ...
//
// ===== PUSH / POP =====
// ...
//
// ===== JMP / BE / BNE =====
// ...
//
// ===== PRINT =====
// ...

