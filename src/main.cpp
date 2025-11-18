// [Owner: D] 파일명: main.cpp
// [Role] 실행 진입점
// [Interfaces] 파일 경로 인자, VMContext, InstructionParser, InstructionFactory
// [Notes] 테스트용 하드코딩된 명령어로 VM 동작 확인

#include <iostream>
#include <vector>
#include <cstdint>

#include "VMContext.h"
#include "runner.h"
#include <fstream>


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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <program.bin>\n";
        return 1;
    }

    const char* filename = argv[1];

    std::ifstream fin(filename, std::ios::binary);
    if (!fin) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return 1;
    }

    std::vector<std::uint32_t> code;
    std::uint32_t raw = 0;

    while (fin.read(reinterpret_cast<char*>(&raw), sizeof(raw))) {
        code.push_back(raw);
    }

    VMContext ctx;
    ctx.loadCode(code);

    Runner::run(ctx);

    return 0;
}
