#pragma once

#include <cstdint>

// [역할] 레지스터/플래그 심볼 정의
// 레지스터 번호 정의
// R0, R1, R2 는 일반 레지스터
// PC = Program Counter, SP = Stack Pointer, BP = Base Pointer(옵션)
enum class Reg : std::uint8_t {
    R0 = 0,
    R1 = 1,
    R2 = 2,
    PC = 3,
    SP = 4,
    BP = 5
};
