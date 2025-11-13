// [Owner: D] 파일명: main.cpp
// [Role] 실행 진입점
// [Interfaces] 파일 경로 인자, VMContext, InstructionParser, InstructionFactory
// [Notes] 의사코드 가이드만 작성

// [담당: D] 실행 진입점
// TODO: 의사코드 가이드만 작성
// 1) 파일 경로 인자 검사
// 2) 파일에서 32bit 단위로 읽어 프로그램 벡터에 적재
// 3) VMContext에 loadCode
// 4) 루프: fetchNext -> InstructionParser::parse -> InstructionFactory::create
// 5) cmd->execute(ctx) 호출
// 6) 분기/점프 시 PC 처리 유의, PRINT는 콘솔 출력
// 7) 리소스 해제

