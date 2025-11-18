#pragma once

#include <cstdint>

// [Owner: B] 파일명: Instructions.h
// [Role] 모든 구체 명령어 "선언"을 한 파일에 모음
// [Interfaces] 각 Instruction 클래스의 execute 선언
// [Notes] 옵션 B 사용: 모든 구체 명령어를 Instructions.h/.cpp 한 쌍에 모음

// 전방 선언
class VMContext;
class Instruction;

// Instruction 기본 인터페이스 (Command 패턴)
class Instruction {
public:
    virtual ~Instruction() = default;
    virtual void execute(VMContext& ctx) = 0;
};

// ===== MOV =====
class MovInstruction : public Instruction {
public:
    MovInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2);
    void execute(VMContext& ctx) override;

private:
    std::uint8_t flag_;
    std::uint8_t op1_;
    std::uint8_t op2_;
};

// ===== ADD =====
class AddInstruction : public Instruction {
public:
    AddInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2);
    void execute(VMContext& ctx) override;

private:
    std::uint8_t flag_;
    std::uint8_t op1_;
    std::uint8_t op2_;
};

// ===== SUB =====
class SubInstruction : public Instruction {
public:
    SubInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2);
    void execute(VMContext& ctx) override;

private:
    std::uint8_t flag_;
    std::uint8_t op1_;
    std::uint8_t op2_;
};

// ===== MUL =====
class MulInstruction : public Instruction {
public:
    MulInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2);
    void execute(VMContext& ctx) override;

private:
    std::uint8_t flag_;
    std::uint8_t op1_;
    std::uint8_t op2_;
};

// ===== CMP =====
// 결과에 따라 ZF/CF/OF 설정
class CmpInstruction : public Instruction {
public:
    CmpInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2);
    void execute(VMContext& ctx) override;

private:
    std::uint8_t flag_;
    std::uint8_t op1_;
    std::uint8_t op2_;
};

// ===== PUSH =====
class PushInstruction : public Instruction {
public:
    PushInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2);
    void execute(VMContext& ctx) override;

private:
    std::uint8_t flag_;
    std::uint8_t op1_;
    std::uint8_t op2_;
};

// ===== POP =====
class PopInstruction : public Instruction {
public:
    PopInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2);
    void execute(VMContext& ctx) override;

private:
    std::uint8_t flag_;
    std::uint8_t op1_;
    std::uint8_t op2_;
};

// ===== JMP =====
class JmpInstruction : public Instruction {
public:
    JmpInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2);
    void execute(VMContext& ctx) override;

private:
    std::uint8_t flag_;
    std::uint8_t op1_;
    std::uint8_t op2_;
};

// ===== BE (Branch if Equal, ZF가 true일 때 점프) =====
class BeInstruction : public Instruction {
public:
    BeInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2);
    void execute(VMContext& ctx) override;

private:
    std::uint8_t flag_;
    std::uint8_t op1_;
    std::uint8_t op2_;
};

// ===== BNE (Branch if Not Equal, ZF가 false일 때 점프) =====
class BneInstruction : public Instruction {
public:
    BneInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2);
    void execute(VMContext& ctx) override;

private:
    std::uint8_t flag_;
    std::uint8_t op1_;
    std::uint8_t op2_;
};

// ===== PRINT =====
class PrintInstruction : public Instruction {
public:
    PrintInstruction(std::uint8_t flag, std::uint8_t op1, std::uint8_t op2);
    void execute(VMContext& ctx) override;

private:
    std::uint8_t flag_;
    std::uint8_t op1_;
    std::uint8_t op2_;
};
