#include "InstructionParser.h"

// [Owner: A]
// [Role] InstructionParser 구현 (비트 연산)
// [Note] 비트 시프트 위치와 마스크의 일관성이 중요. 엔디언 주의.

namespace {
constexpr std::uint32_t OPCODE_MASK   = 0x3Fu;
constexpr std::uint32_t FLAG_MASK     = 0x03u;
constexpr std::uint32_t OPERAND_MASK  = 0xFFu;
}  // namespace

// InstructionParser.cpp

ParsedInstruction InstructionParser::parse(std::uint32_t raw) {
    // 요구사항에 따른 32bit 명령어 구조:
    // 31-26: opcode (6bit)
    // 25-24: flag (2bit)
    // 23-16: op1 (8bit)
    // 15-8:  op2 (8bit)
    // 7-0:   reserved (8bit, 무시)
    
    const std::uint8_t opcode = static_cast<std::uint8_t>((raw >> 26) & OPCODE_MASK);
    const std::uint8_t flag   = static_cast<std::uint8_t>((raw >> 24) & FLAG_MASK);
    const std::uint8_t op1    = static_cast<std::uint8_t>((raw >> 16) & OPERAND_MASK);
    const std::uint8_t op2    = static_cast<std::uint8_t>((raw >> 8)  & OPERAND_MASK);
    
    // ParsedInstruction: (opcode, flag, op1=dest, op2=src)
    return ParsedInstruction{opcode, flag, op1, op2};
}

