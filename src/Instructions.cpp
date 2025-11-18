// [Owner: B] 파일명: Instructions.cpp
// [Role] 모든 구체 명령어 "구현"
// [Interfaces] 각 Instruction 클래스의 execute 구현
// [Notes] 공통 규칙: execute(VMContext& ctx)에서 피연산자 타입(flag)에 따라 처리

#include "Instructions.h"
#include "VMContext.h"
#include "registers.h"
#include <iostream>
#include <cstdint>
#include <stdexcept>
#include <string>

// ===== 헬퍼 함수 =====

// flag에 따라 레지스터 또는 즉값을 해석하는 헬퍼 함수
// first = true: dest (op1), false: src (op2)
// flag 0 (RR): op1=reg, op2=reg
// flag 1 (RV): op1=reg, op2=value
// flag 2 (VR): op1=value, op2=reg
// flag 3 (VV): op1=value, op2=value
static std::uint8_t resolveValue(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2, 
                                  bool first, VMContext& ctx) {
    switch (flag) {
        case 0:  // RR
            return first ? ctx.getRegister(static_cast<Reg>(op1))
                         : ctx.getRegister(static_cast<Reg>(op2));
        case 1:  // RV
            return first ? ctx.getRegister(static_cast<Reg>(op1))
                         : op2;
        case 2:  // VR
            return first ? op1
                         : ctx.getRegister(static_cast<Reg>(op2));
        case 3:  // VV
            return first ? op1 : op2;
        default:
            return 0;
    }
}

// dest 레지스터 번호를 반환 (flag에 따라 op1이 레지스터인지 확인)
// flag 0 (RR) 또는 1 (RV)만 허용 (op1이 레지스터인 경우만)
// 레지스터 범위 검증: R0(1), R1(2), R2(3), PC(4), SP(5), BP(6), ZF(7), CF(8), OF(9) → 1~9만 유효
static Reg resolveDestRegister(std::uint8_t flag, std::uint8_t op1, const char* instrName) {
    if (flag == 0 || flag == 1) {  // RR or RV → op1은 레지스터
        // 레지스터 인덱스 범위 검증 (1~9)
        if (op1 < 1 || op1 > 9) {
            throw std::runtime_error(std::string(instrName) + ": invalid register index (must be 1-9)");
        }
        return static_cast<Reg>(op1);
    }
    // VR 또는 VV인 경우 dest가 레지스터가 아니므로 에러
    throw std::runtime_error(std::string(instrName) + ": invalid dest register (dest cannot be immediate value)");
}

// ===== MOV =====

MovInstruction::MovInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2)
    : flag_(flag), op1_(op1), op2_(op2) {}

void MovInstruction::execute(VMContext& ctx) {
    // dest <- src
    std::uint8_t src = resolveValue(flag_, op1_, op2_, false, ctx);
    Reg destReg = resolveDestRegister(flag_, op1_, "MOV");
    ctx.setRegister(destReg, src);
}

// ===== ADD =====

AddInstruction::AddInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2)
    : flag_(flag), op1_(op1), op2_(op2) {}

void AddInstruction::execute(VMContext& ctx) {
    // dest <- dest + src
    Reg destReg = resolveDestRegister(flag_, op1_, "ADD");
    std::uint8_t dest = ctx.getRegister(destReg);
    std::uint8_t src = resolveValue(flag_, op1_, op2_, false, ctx);
    
    std::uint16_t result = static_cast<std::uint16_t>(dest) + static_cast<std::uint16_t>(src);
    std::uint8_t dest_before = dest;
    std::uint8_t stored = static_cast<std::uint8_t>(result);
    
    ctx.setRegister(destReg, stored);
    
    // 플래그 설정
    // ZF: 저장되는 8bit 결과값이 0인가를 기준으로 계산
    ctx.setFlagZF(stored == 0);
    ctx.setFlagCF(result > 255);
    // OF: signed overflow 체크 (int8_t 범위를 벗어나는지)
    std::int8_t signed_dest = static_cast<std::int8_t>(dest_before);
    std::int8_t signed_src = static_cast<std::int8_t>(src);
    std::int16_t signed_result = static_cast<std::int16_t>(signed_dest) + static_cast<std::int16_t>(signed_src);
    ctx.setFlagOF(signed_result < -128 || signed_result > 127);
}

// ===== SUB =====

SubInstruction::SubInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2)
    : flag_(flag), op1_(op1), op2_(op2) {}

void SubInstruction::execute(VMContext& ctx) {
    // dest <- dest - src
    Reg destReg = resolveDestRegister(flag_, op1_, "SUB");
    std::uint8_t dest = ctx.getRegister(destReg);
    std::uint8_t src = resolveValue(flag_, op1_, op2_, false, ctx);
    
    std::int16_t result = static_cast<std::int16_t>(dest) - static_cast<std::int16_t>(src);
    std::uint8_t dest_before = dest;
    std::uint8_t stored = static_cast<std::uint8_t>(result);
    
    ctx.setRegister(destReg, stored);
    
    // 플래그 설정
    // ZF: 저장되는 8bit 결과값이 0인가를 기준으로 계산
    ctx.setFlagZF(stored == 0);
    ctx.setFlagCF(dest < src);  // borrow 발생
    // OF: signed overflow 체크
    std::int8_t signed_dest = static_cast<std::int8_t>(dest_before);
    std::int8_t signed_src = static_cast<std::int8_t>(src);
    std::int16_t signed_result = static_cast<std::int16_t>(signed_dest) - static_cast<std::int16_t>(signed_src);
    ctx.setFlagOF(signed_result < -128 || signed_result > 127);
}

// ===== MUL =====

MulInstruction::MulInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2)
    : flag_(flag), op1_(op1), op2_(op2) {}

void MulInstruction::execute(VMContext& ctx) {
    // dest <- dest * src
    Reg destReg = resolveDestRegister(flag_, op1_, "MUL");
    std::uint8_t dest = ctx.getRegister(destReg);
    std::uint8_t src = resolveValue(flag_, op1_, op2_, false, ctx);
    
    std::uint16_t result = static_cast<std::uint16_t>(dest) * static_cast<std::uint16_t>(src);
    std::uint8_t dest_before = dest;
    std::uint8_t stored = static_cast<std::uint8_t>(result);
    
    ctx.setRegister(destReg, stored);
    
    // 플래그 설정
    // ZF: 저장되는 8bit 결과값이 0인가를 기준으로 계산
    ctx.setFlagZF(stored == 0);
    ctx.setFlagCF(result > 255);
    // OF: signed overflow 체크
    std::int8_t signed_dest = static_cast<std::int8_t>(dest_before);
    std::int8_t signed_src = static_cast<std::int8_t>(src);
    std::int32_t signed_result = static_cast<std::int32_t>(signed_dest) * static_cast<std::int32_t>(signed_src);
    ctx.setFlagOF(signed_result < -128 || signed_result > 127);
}

// ===== CMP =====
// (dest - src) 결과에 따라 ZF/CF/OF 설정, 나머지 클리어 정책 문서화

CmpInstruction::CmpInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2)
    : flag_(flag), op1_(op1), op2_(op2) {}

void CmpInstruction::execute(VMContext& ctx) {
    // dest - src 계산 (레지스터는 변경하지 않음)
    std::uint8_t dest = resolveValue(flag_, op1_, op2_, true, ctx);
    std::uint8_t src = resolveValue(flag_, op1_, op2_, false, ctx);
    
    std::int16_t result = static_cast<std::int16_t>(dest) - static_cast<std::int16_t>(src);
    std::uint8_t stored = static_cast<std::uint8_t>(result);
    
    // 플래그 설정
    // ZF: 저장되는 8bit 결과값이 0인가를 기준으로 계산 (ADD/SUB와 동일한 원칙)
    ctx.setFlagZF(stored == 0);
    ctx.setFlagCF(dest < src);  // borrow 발생
    // OF: signed overflow 체크
    std::int8_t signed_dest = static_cast<std::int8_t>(dest);
    std::int8_t signed_src = static_cast<std::int8_t>(src);
    std::int16_t signed_result = static_cast<std::int16_t>(signed_dest) - static_cast<std::int16_t>(signed_src);
    ctx.setFlagOF(signed_result < -128 || signed_result > 127);
}

// ===== PUSH =====

PushInstruction::PushInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2)
    : flag_(flag), op1_(op1), op2_(op2) {}

void PushInstruction::execute(VMContext& ctx) {
    // 스택에 값 푸시
    // PUSH는 op1만 사용 (op2는 무시됨)
    // PUSH [REG] 또는 PUSH [VALUE] 형태로 op1만 의미 있음
    std::uint8_t value;
    switch (flag_) {
        case 0:  // RR → op1=reg
        case 1:  // RV → op1=reg
            value = ctx.getRegister(static_cast<Reg>(op1_));
            break;
        case 2:  // VR → op1=value
        case 3:  // VV → op1=value
            value = op1_;
            break;
        default:
            value = 0;
            break;
    }
    ctx.push(value);
}

// ===== POP =====

PopInstruction::PopInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2)
    : flag_(flag), op1_(op1), op2_(op2) {}

void PopInstruction::execute(VMContext& ctx) {
    // 스택에서 값 팝하여 레지스터에 저장
    // POP은 op1이 항상 레지스터여야 함 (flag 0 또는 1만 허용)
    if (flag_ != 0 && flag_ != 1) {
        throw std::runtime_error("POP: operand must be a register");
    }
    // 레지스터 인덱스 범위 검증 (1~9)
    if (op1_ < 1 || op1_ > 9) {
        throw std::runtime_error("POP: invalid register index (must be 1-9)");
    }
    std::uint8_t value = ctx.pop();
    Reg destReg = static_cast<Reg>(op1_);
    ctx.setRegister(destReg, value);
}

// ===== JMP =====

JmpInstruction::JmpInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2)
    : flag_(flag), op1_(op1), op2_(op2) {}

void JmpInstruction::execute(VMContext& ctx) {
    // 무조건 점프
    std::uint8_t target = resolveValue(flag_, op1_, op2_, false, ctx);
    ctx.jump(target);
}

// ===== BE (Branch if Equal) =====

BeInstruction::BeInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2)
    : flag_(flag), op1_(op1), op2_(op2) {}

void BeInstruction::execute(VMContext& ctx) {
    // ZF가 true일 때 점프
    if (ctx.getFlagZF()) {
        std::uint8_t target = resolveValue(flag_, op1_, op2_, false, ctx);
        ctx.jump(target);
    }
}

// ===== BNE (Branch if Not Equal) =====

BneInstruction::BneInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2)
    : flag_(flag), op1_(op1), op2_(op2) {}

void BneInstruction::execute(VMContext& ctx) {
    // ZF가 false일 때 점프
    if (!ctx.getFlagZF()) {
        std::uint8_t target = resolveValue(flag_, op1_, op2_, false, ctx);
        ctx.jump(target);
    }
}

// ===== PRINT =====

PrintInstruction::PrintInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2)
    : flag_(flag), op1_(op1), op2_(op2) {}

void PrintInstruction::execute(VMContext& ctx) {
    // 레지스터 또는 즉값을 콘솔에 출력
    std::uint8_t value = resolveValue(flag_, op1_, op2_, false, ctx);
    // endl 대신 '\n' 사용 (불필요한 flush 방지로 성능 향상)
    std::cout << static_cast<int>(value) << '\n';
}
