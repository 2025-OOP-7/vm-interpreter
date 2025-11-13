#pragma once

// [Owner: D] 파일명: InstructionFactory.h
// [Role] opcode/flag/op1/op2 → 적절한 Instruction 객체 생성 (Command)
// [Interfaces] Instruction* create(uint8_t opcode, uint8_t flag, uint8_t op1, uint8_t op2)
// [Notes] 실제 new 반환/매핑 로직은 작성하지 말고 주석/TODO로만

// [담당: D] opcode/flag/op1/op2 -> 적절한 Instruction 객체 생성 (Command)
// [구성]
// - class InstructionFactory { static Instruction* create(uint8_t opcode, uint8_t flag, uint8_t op1, uint8_t op2); }
//
// [주의] 실제 new 반환/매핑 로직은 작성하지 말고 주석/TODO로만.

