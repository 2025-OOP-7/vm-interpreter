// [Owner: D] 파일명: runner.cpp
// [Role] VM 실행 루프 구현
// [Notes] fetch → parse → create → execute → PC++ 흐름 제어

#include "runner.h"
#include "InstructionParser.h"
#include "InstructionFactory.h"

void Runner::run(VMContext& ctx) {
    while (!ctx.isFinished()) {
        // 1) PC 위치에서 32bit 명령어 가져오기
        std::uint32_t raw = ctx.fetch();

        // 2) 파싱 (A 역할)
        ParsedInstruction pi = InstructionParser::parse(raw);

        // 3) Instruction 객체 생성 (D 역할)
        auto inst = InstructionFactory::create(pi);

        // 4) 실행 (B/C 협업)
        inst->execute(ctx);

        // 5) 다음 명령으로 이동
        // JMP/BE/BNE 내부에서 PC를 변경했으면 increment 금지
        // JMP=8(0x08), BE=9(0x09), BNE=10(0x0A)
        if (pi.opcode != 0x08 && pi.opcode != 0x09 && pi.opcode != 0x0A) {
            ctx.incrementPC();
        }
    }
}

