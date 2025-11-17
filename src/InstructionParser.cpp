#include "InstructionParser.h"

// [Owner: A]
// [Role] InstructionParser 구현 (비트 연산)
// [Note] 비트 시프트 위치와 마스크의 일관성이 중요. 엔디언 주의.

namespace {
constexpr std::uint32_t OPCODE_MASK   = 0x3Fu;
constexpr std::uint32_t FLAG_MASK     = 0x03u;
constexpr std::uint32_t OPERAND_MASK  = 0xFFu;
}  // namespace

ParsedInstruction InstructionParser::parse(std::uint32_t raw) {
    // Little-endian 입력을 가정.
    // 과제 환경에서는 파일 생성 시점과 실행 환경의 엔디언이 동일하다고 가정하고 구현해도 무방함.
    // 필요하다면 추후 바이트 스왑 함수를 추가하여 확장 가능.

    const auto opcode = static_cast<std::uint8_t>((raw >> 26) & OPCODE_MASK);
    const auto flag   = static_cast<std::uint8_t>((raw >> 24) & FLAG_MASK);
    const auto op1    = static_cast<std::uint8_t>((raw >> 16) & OPERAND_MASK);
    const auto op2    = static_cast<std::uint8_t>((raw >> 8)  & OPERAND_MASK);

    return ParsedInstruction{opcode, flag, op1, op2};
}

