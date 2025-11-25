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
        // 점프 명령어(JMP/BE/BNE)는 내부에서 PC를 변경하므로 Runner에서 증가시키지 않음
        // BE/BNE에서 분기 실패 시에는 명령어 내부에서 이미 PC를 증가시켰으므로
        // Runner에서는 점프 명령어가 아닌 경우에만 PC 증가
        // JMP=8(0x08), BE=9(0x09), BNE=10(0x0A)
        if (pi.opcode != 0x08 && pi.opcode != 0x09 && pi.opcode != 0x0A) {
            ctx.incrementPC();
        }
    }
}

