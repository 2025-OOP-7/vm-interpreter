#pragma once
#include <cstdint>

// [Owner: A]
// [Role] 32bit 명령어 파싱 담당 (Opcode / Flag / Operand 추출)
// [Note] 비트 연산 정확성 중요. 엔디언 문제, 매직넘버 주의.
// [Output] ParsedInstruction {opcode, flag, op1, op2}

struct ParsedInstruction {
    std::uint8_t opcode{0};
    std::uint8_t flag{0};
    std::uint8_t op1{0};
    std::uint8_t op2{0};
};

class InstructionParser {
public:
    static ParsedInstruction parse(std::uint32_t raw);
};

