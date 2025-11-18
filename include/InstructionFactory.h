#pragma once

// [Owner: D]
// [Role] opcode + flag + operands 기반으로 적절한 Instruction 객체 생성
// [Notes] Command 패턴의 "생성 책임" 담당

#include <memory>
#include "Instructions.h"
#include "InstructionParser.h"

class InstructionFactory {
public:
    static std::unique_ptr<Instruction> create(const ParsedInstruction& pi);
};
