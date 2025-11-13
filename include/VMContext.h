#pragma once

// [Owner: C] 파일명: VMContext.h
// [Role] VM 상태 관리(레지스터, 스택, 코드 메모리, PC/플래그 API)
// [Interfaces] 레지스터 get/set, 스택 push/pop, 코드 로딩, 플래그 관리
// [Notes] 선언 예시는 주석으로만 남기고, 실제 구현은 VMContext.cpp TODO로

// [담당: C] VM 상태 관리(레지스터, 스택, 코드 메모리, PC/플래그 API)
// [구성 가이드]
// - 레지스터 get/set (Reg 기반)
// - 스택 push/pop (SP 규칙 주석으로 문서화)
// - 코드 로딩(loadCode), 다음 명령 가져오기(fetchNext)
// - 플래그(ZF/CF/OF) set/clear API
//
// [주의] 선언 예시는 주석으로만 남기고, 실제 구현은 VMContext.cpp TODO로.

