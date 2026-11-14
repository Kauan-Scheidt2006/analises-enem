#pragma once

#include "MemoriaProcesso.h"

class MonitorMemoriaProcesso {
public:
    virtual ~MonitorMemoriaProcesso() = default;

    virtual MemoriaProcesso consultar() const = 0;
};
