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
    if (sp >= STACK_SIZE - 1) {  // uint8_t는 0~255만 표현 가능하므로 255 이상이면 overflow
        throw std::runtime_error("Stack overflow");
    }
    // SP가 가리키는 위치에 값을 넣고
    stack_[sp] = value;
    // SP를 1 증가시켜 다음 빈 칸을 가리키게 함
    regs_[(int)Reg::SP - 1] = sp + 1;
}

std::uint8_t VMContext::pop() {
    std::uint8_t sp = regs_[(int)Reg::SP - 1];
    if (sp == 0) {
        throw std::runtime_error("Stack underflow");
    }
    // 정석적인 LIFO 스택 구현
    // SP는 다음에 push할 위치를 가리키므로, SP-1이 실제 스택의 최상단 인덱스
    sp -= 1;                              // SP를 먼저 감소시킴
    regs_[(int)Reg::SP - 1] = sp;         // SP 업데이트
    return stack_[sp];                    // 감소된 SP 위치의 값 반환
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
