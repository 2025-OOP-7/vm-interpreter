// [Owner: D] 파일명: InstructionFactory.cpp
// [Role] opcode → Instruction 생성 매핑
// [Interfaces] Instruction* create(const ParsedInstruction& pi)
// [Notes] switch(opcode) 매핑, Command 패턴의 팩토리 역할

#include "InstructionFactory.h"
#include <stdexcept>
#include <string>

// InstructionFactory.cpp

std::unique_ptr<Instruction> InstructionFactory::create(const ParsedInstruction& pi) {
    switch (pi.opcode) {
        case 0b000001: // 1: MOV
            return std::make_unique<MovInstruction>(pi.flag, pi.op1, pi.op2);

        case 0b000010: // 2: ADD
            return std::make_unique<AddInstruction>(pi.flag, pi.op1, pi.op2);

        case 0b000011: // 3: SUB
            return std::make_unique<SubInstruction>(pi.flag, pi.op1, pi.op2);

        case 0b000100: // 4: MUL
            return std::make_unique<MulInstruction>(pi.flag, pi.op1, pi.op2);

        case 0b000101: // 5: CMP
            return std::make_unique<CmpInstruction>(pi.flag, pi.op1, pi.op2);

        case 0b000110: // 6: PUSH
            return std::make_unique<PushInstruction>(pi.flag, pi.op1, pi.op2);

        case 0b000111: // 7: POP
            return std::make_unique<PopInstruction>(pi.flag, pi.op1, pi.op2);

        case 0b001000: // 8: JMP
            return std::make_unique<JmpInstruction>(pi.flag, pi.op1, pi.op2);

        case 0b001001: // 9: BE
            return std::make_unique<BeInstruction>(pi.flag, pi.op1, pi.op2);

        case 0b001010: // 10: BNE
            return std::make_unique<BneInstruction>(pi.flag, pi.op1, pi.op2);

        case 0b001011: // 11: PRINT
            return std::make_unique<PrintInstruction>(pi.flag, pi.op1, pi.op2);

        default:
            throw std::runtime_error("Unknown opcode: " + std::to_string(pi.opcode));
    }
}
