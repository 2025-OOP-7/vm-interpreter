// [Owner: D] 파일명: InstructionFactory.cpp
// [Role] opcode → Instruction 생성 매핑 TODO 가이드
// [Interfaces] Instruction* create(uint8_t opcode, uint8_t flag, uint8_t op1, uint8_t op2)
// [Notes] switch(opcode) 매핑, flag 해석, nullptr/예외 처리 정책

// [담당: D] opcode -> Instruction 생성 매핑 TODO 가이드
// - switch(opcode) { case MOV: ... case ADD: ... }
// - flag 해석(RR/RV/R/V) -> 생성자 선택 규칙 주석
// - nullptr/예외 처리 정책
// - 새 명령 추가 시 여기를 업데이트

