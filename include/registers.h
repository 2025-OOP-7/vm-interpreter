#pragma once

#include <cstdint>

// [역할] 레지스터/플래그 심볼 정의
// 레지스터 번호 정의 (요구사항에 따라 1부터 시작)
// R0, R1, R2 는 일반 레지스터
// PC = Program Counter, SP = Stack Pointer, BP = Base Pointer
// ZF, CF, OF는 플래그 레지스터 (요구사항상 레지스터 번호로 정의되지만 boolean으로 관리)
enum class Reg : std::uint8_t {
    R0 = 1,
    R1 = 2,
    R2 = 3,
    PC = 4,
    SP = 5,
    BP = 6,
    ZF = 7,
    CF = 8,
    OF = 9
};
