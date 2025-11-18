#pragma once

#include <cstdint>
#include <vector>
#include <stdexcept>
#include "registers.h"

// [Owner: C] 파일명: VMContext.h
// [Role] VM 상태 관리(레지스터, 스택, 코드 메모리, PC/플래그 API)
// [Interfaces] 레지스터 get/set, 스택 push/pop, 코드 로딩, 플래그 관리
// [Notes] 가상 머신의 전체 실행 상태를 보관하고 관리

// VMContext: 가상 머신의 전체 실행 상태 보관
class VMContext {
public:
    VMContext();

    // 레지스터 접근
    std::uint8_t getRegister(Reg r) const;
    void setRegister(Reg r, std::uint8_t value);

    // PC 조작
    void incrementPC();       // PC++
    void jump(std::uint8_t target); // PC = target

    // 스택 조작
    void push(std::uint8_t value);
    std::uint8_t pop();

    // 플래그 조작
    void setFlagZF(bool v) { ZF_ = v; }
    void setFlagCF(bool v) { CF_ = v; }
    void setFlagOF(bool v) { OF_ = v; }

    bool getFlagZF() const { return ZF_; }
    bool getFlagCF() const { return CF_; }
    bool getFlagOF() const { return OF_; }

    // 프로그램 코드(바이트코드) 로딩
    void loadCode(const std::vector<std::uint32_t>& code);

    // 현재 PC 위치의 명령어 가져오기
    std::uint32_t fetch() const;

    // 프로그램 종료 조건
    bool isFinished() const;

private:
    std::uint8_t regs_[6];  // R0, R1, R2, PC, SP, BP

    bool ZF_;
    bool CF_;
    bool OF_;

    std::vector<std::uint32_t> code_;  // 32bit instruction list
    static constexpr std::size_t STACK_SIZE = 256;
    std::uint8_t stack_[STACK_SIZE];
};
