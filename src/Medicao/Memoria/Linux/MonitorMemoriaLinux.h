#pragma once

#include "../MonitorMemoriaProcesso.h"

class MonitorMemoriaLinux final : public MonitorMemoriaProcesso {
public:
    MemoriaProcesso consultar() const override;
};
