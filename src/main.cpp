// [Owner: D] 파일명: main.cpp
// [Role] 실행 진입점
// [Interfaces] 파일 경로 인자, VMContext, InstructionParser, InstructionFactory
// [Notes] 테스트용 하드코딩된 명령어로 VM 동작 확인

#include <iostream>
#include <vector>
#include <cstdint>

#include "VMContext.h"
#include "runner.h"

// 테스팅용 직접 opcode 조립 함수
static std::uint32_t encode(std::uint8_t opcode, std::uint8_t flag, std::uint8_t op1, std::uint8_t op2) {
    // opcode: 상위 6bit (26~31)
    // flag: (24~25)
    // op1: (16~23)
    // op2: (8~15)
    return (static_cast<std::uint32_t>(opcode) << 26)
         | (static_cast<std::uint32_t>(flag) << 24)
         | (static_cast<std::uint32_t>(op1) << 16)
         | (static_cast<std::uint32_t>(op2) << 8);
}

int main() {
    VMContext ctx;

    // 예제 프로그램:
    // R0 = 10
    // R1 = 20
    // ADD R0, R1
    // PRINT R0    → 30 출력
    // END

    std::vector<std::uint32_t> code;

    code.push_back(encode(0x00, 1, 0, 10));   // MOV R0, 10
    code.push_back(encode(0x00, 1, 1, 20));   // MOV R1, 20
    code.push_back(encode(0x01, 0, 0, 1));    // ADD R0, R1
    code.push_back(encode(0x0A, 0, 0, 0));     // PRINT R0

    ctx.loadCode(code);

    Runner::run(ctx);

    return 0;
}
