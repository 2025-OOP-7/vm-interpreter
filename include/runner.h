#pragma once

// [Owner: D] 파일명: runner.h
// [Role] VM 실행 루프 관리
// [Notes] fetch → parse → create → execute → PC++ 흐름 제어

#include "VMContext.h"

class Runner {
public:
    static void run(VMContext& ctx);
};

