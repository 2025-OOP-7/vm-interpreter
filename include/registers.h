#pragma once

#include <cstdint>

// [역할] 레지스터/플래그 심볼 정의
// 레지스터 번호 정의 (요구사항에 따라 1부터 시작)
// R0, R1, R2 는 일반 레지스터
// PC = Program Counter, SP = Stack Pointer, BP = Base Pointer
// ZF, CF, OF는 플래그 레지스터 (boolean으로 관리하되 레지스터 접근도 지원)
enum class Reg : std::uint8_t {
    R0 = 1,   // 0000 0001
    R1 = 2,   // 0000 0010
    R2 = 3,   // 0000 0011
    PC = 4,   // 0000 0100
    SP = 5,   // 0000 0101
    BP = 6,   // 0000 0110
    ZF = 7,   // 0000 0111
    CF = 8,   // 0000 1000
    OF = 9    // 0000 1001
};
