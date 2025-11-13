// [Owner: C] 파일명: VMContext.cpp
// [Role] VMContext 구현 TODO 가이드
// [Interfaces] 레지스터, 스택, 코드 메모리, 플래그 관리 API
// [Notes] 함수 바디는 비워두고 "어떤 로직이 들어갈지"를 상세 주석으로

// [담당: C] VMContext 구현 TODO 가이드
// - 레지스터 맵 초기화: R0,R1,R2,PC,SP,BP,ZF,CF,OF (8bit)
// - 스택 컨테이너(예: vector<uint8_t>)와 SP 규약 주석
// - loadCode(vector<uint32_t>) 보관
// - fetchNext(): PC 기준 다음 명령 반환(PC 증가 규칙 문서화)
// - setFlag/clearFlag 도우미
//
// [주의] 함수 바디는 비워두고 "어떤 로직이 들어갈지"를 상세 주석으로.

