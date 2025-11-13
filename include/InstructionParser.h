#pragma once

// [Owner: A] 파일명: InstructionParser.h
// [Role] 32bit 원시 명령어 → opcode/flag/operand 추출
// [Interfaces] ParsedInstruction{opcode,flag,op1,op2}
// [Notes] 비트 시프트/마스크 정확성, 엔디언 주의

// [담당: A] 32bit 원시 명령어 -> opcode/flag/operand 추출
// [구성]
// - struct ParsedInstruction { uint8_t opcode; uint8_t flag; uint8_t op1; uint8_t op2; };
// - class InstructionParser { static ParsedInstruction parse(uint32_t raw); }
//
// [주의] 여기서는 선언 가이드만. 구현은 InstructionParser.cpp의 TODO로.

