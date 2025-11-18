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
    regs_[(int)Reg::SP] = 0;
}

std::uint8_t VMContext::getRegister(Reg r) const {
    return regs_[(int)r];
}

void VMContext::setRegister(Reg r, std::uint8_t value) {
    regs_[(int)r] = value;
}

void VMContext::incrementPC() {
    regs_[(int)Reg::PC]++;
}

void VMContext::jump(std::uint8_t target) {
    regs_[(int)Reg::PC] = target;
}

void VMContext::push(std::uint8_t value) {
    std::uint8_t sp = regs_[(int)Reg::SP];
    if (sp >= STACK_SIZE) {
        throw std::runtime_error("Stack overflow");
    }
    stack_[sp] = value;
    regs_[(int)Reg::SP] = sp + 1;
}

std::uint8_t VMContext::pop() {
    std::uint8_t sp = regs_[(int)Reg::SP];
    if (sp == 0) {
        throw std::runtime_error("Stack underflow");
    }
    std::uint8_t value = stack_[sp - 1];
    regs_[(int)Reg::SP] = sp - 1;
    return value;
}

void VMContext::loadCode(const std::vector<std::uint32_t>& code) {
    code_ = code;
}

std::uint32_t VMContext::fetch() const {
    std::uint8_t pc = regs_[(int)Reg::PC];
    if (pc >= code_.size()) {
        throw std::runtime_error("PC out of code range");
    }
    return code_[pc];
}

bool VMContext::isFinished() const {
    return regs_[(int)Reg::PC] >= code_.size();
}
