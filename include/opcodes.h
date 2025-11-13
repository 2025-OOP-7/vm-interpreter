#pragma once

// [역할] 명령어 opcode/flag 정의(매직 넘버 제거)
// [주의] 여기서는 구현 금지. enum/constexpr "예시"만 주석으로 가이드.
//
// TODO: enum class Opcode { MOV=0x01, ADD=0x02, SUB=0x03, MUL=0x04, CMP=0x05, PUSH=0x06, POP=0x07, JMP=0x08, BE=0x09, BNE=0x0A, PRINT=0x0B };
//
// TODO: enum class Flag { RR=0b00, RV=0b01, R=0b10, V=0b11 };
//
// 사용처: InstructionParser, InstructionFactory, Instructions.*

