// [Owner: A] 파일명: InstructionParser.cpp
// [Role] 32bit 원시 명령어 → ParsedInstruction 파싱
// [Interfaces] ParsedInstruction{opcode,flag,op1,op2}
// [Notes] 비트 시프트/마스크 정확성, 엔디언 주의

// [담당: A] 비트 파싱 TODO 가이드
// - ParsedInstruction parse(uint32_t raw):
//   opcode = (raw >> 26) & 0x3F
//   flag   = (raw >> 24) & 0x03
//   op1    = (raw >> 16) & 0xFF
//   op2    = (raw >> 8)  & 0xFF
// - 엔디언 주의 사항, reserved 8bit 무시
// - 단위 테스트 포인트 주석

