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
    // 실제 바이너리 파일의 바이트 순서: [opcode+flag, reserved, source, dest]
    // Little-endian으로 읽은 raw 값을 바이트 배열로 해석
    const std::uint8_t* bytes = reinterpret_cast<const std::uint8_t*>(&raw);
    
    // 바이트 순서: [bytes[0], bytes[1], bytes[2], bytes[3]]
    // = [opcode+flag, reserved, source, dest]
    const std::uint8_t opcode_flag = bytes[0];
    // const std::uint8_t reserved = bytes[1];  // 무시
    const std::uint8_t source = bytes[2];
    const std::uint8_t dest = bytes[3];
    
    // opcode+flag에서 분리
    const std::uint8_t opcode = (opcode_flag >> 2) & OPCODE_MASK;  // 상위 6bit
    const std::uint8_t flag = opcode_flag & FLAG_MASK;              // 하위 2bit
    
    // ParsedInstruction: (opcode, flag, op1=dest, op2=src)
    // 주의: op1은 destination, op2는 source (MOV dest, src 형태)
    return ParsedInstruction{opcode, flag, dest, source};
}

