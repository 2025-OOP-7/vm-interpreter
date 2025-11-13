// [Owner: B] 파일명: Instructions.cpp
// [Role] 모든 구체 명령어 "구현" 가이드만 모음 (함수 바디 X, TODO만)
// [Interfaces] 각 Instruction 클래스의 execute 구현
// [Notes] 공통 규칙: execute(VMContext& ctx)에서 피연산자 타입(flag)에 따라 처리

// [담당: B] 모든 구체 명령어 "구현" 가이드만 모음 (함수 바디 X, TODO만)
// 공통 규칙: execute(VMContext& ctx)에서
// - 피연산자 타입(flag)에 따라 레지스터/즉값 처리
// - 레지스터 읽기/쓰기: VMContext API 사용
// - 분기/점프는 여기서 PC를 직접 설정하고 루프의 자동 증가에 주의
//
// 섹션별 TODO 템플릿만 제공:
// ===== MOV =====
// // TODO: dest <- src (reg or value)
//
// ===== ADD =====
// // TODO: dest <- dest + src; ZF/CF/OF 필요 시 업데이트 정책 주석
//
// ===== SUB =====
// // TODO: ...
//
// ===== MUL =====
// // TODO: ...
//
// ===== CMP =====
// // TODO: (dest - src) 결과에 따라 ZF/CF/OF 설정, 나머지 클리어 정책 문서화
//
// ===== PUSH / POP =====
// // TODO: SP 규약에 맞춘 push/pop
//
// ===== JMP / BE / BNE =====
// // TODO: ZF 조건 점프, PC 설정
//
// ===== PRINT =====
// // TODO: 레지스터 또는 즉값 콘솔 출력

