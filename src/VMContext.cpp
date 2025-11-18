// [Owner: C] 파일명: VMContext.cpp
// [Role] VMContext 구현
// [Interfaces] 레지스터, 스택, 코드 메모리, 플래그 관리 API
// [Notes] 가상 머신의 전체 실행 상태를 관리하는 구현

#include "VMContext.h"
#include <stdexcept>
#include <iostream>

VMContext::VMContext()
    : ZF_(false), CF_(false), OF_(false), code_()
{
    // 레지스터 초기화
    for (auto &r : regs_) r = 0;

    // 스택 초기값
    for (auto &s : stack_) s = 0;

    // SP는 스택의 최상단을 가리키게 (스택은 상향 성장)
    // Reg::SP = 5이므로 regs_[4]에 접근
    regs_[(int)Reg::SP - 1] = 0;
}

std::uint8_t VMContext::getRegister(Reg r) const {
    // ZF, CF, OF는 boolean 플래그를 uint8_t로 변환하여 반환
    if (r == Reg::ZF) return ZF_ ? 1 : 0;
    if (r == Reg::CF) return CF_ ? 1 : 0;
    if (r == Reg::OF) return OF_ ? 1 : 0;
    // 레지스터는 1부터 시작하므로 인덱스는 (r - 1)
    return regs_[(int)r - 1];
}

void VMContext::setRegister(Reg r, std::uint8_t value) {
    // ZF, CF, OF는 boolean 플래그로 설정
    if (r == Reg::ZF) { ZF_ = (value != 0); return; }
    if (r == Reg::CF) { CF_ = (value != 0); return; }
    if (r == Reg::OF) { OF_ = (value != 0); return; }
    // 레지스터는 1부터 시작하므로 인덱스는 (r - 1)
    regs_[(int)r - 1] = value;
}

void VMContext::incrementPC() {
    regs_[(int)Reg::PC - 1]++;
}

void VMContext::jump(std::uint8_t target) {
    regs_[(int)Reg::PC - 1] = target;
}

void VMContext::push(std::uint8_t value) {
    std::uint8_t sp = regs_[(int)Reg::SP - 1];
    // uint8_t는 최대 255이므로 STACK_SIZE(256)와 비교 시 항상 false
    // 따라서 STACK_SIZE - 1과 비교해야 함
    if (sp >= STACK_SIZE - 1) {
        throw std::runtime_error("Stack overflow");
    }
    stack_[sp] = value;
    regs_[(int)Reg::SP - 1] = sp + 1;
}

std::uint8_t VMContext::pop() {
    std::uint8_t sp = regs_[(int)Reg::SP - 1];
    if (sp == 0) {
        throw std::runtime_error("Stack underflow");
    }
    std::uint8_t value = stack_[sp - 1];
    regs_[(int)Reg::SP - 1] = sp - 1;
    return value;
}

void VMContext::loadCode(const std::vector<std::uint32_t>& code) {
    code_ = code;
}

std::uint32_t VMContext::fetch() const {
    std::uint8_t pc = regs_[(int)Reg::PC - 1];
    if (pc >= code_.size()) {
        throw std::runtime_error("PC out of code range");
    }
    return code_[pc];
}

bool VMContext::isFinished() const {
    return regs_[(int)Reg::PC - 1] >= code_.size();
}
