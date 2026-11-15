#pragma once

#include "../MonitorMemoriaProcesso.h"

class MonitorMemoriaWindows final : public MonitorMemoriaProcesso {
public:
    MemoriaProcesso consultar() const override;
};
