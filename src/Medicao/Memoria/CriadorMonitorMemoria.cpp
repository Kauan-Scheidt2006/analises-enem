#include "CriadorMonitorMemoria.h"

#if defined(_WIN32)

#include "Windows/MonitorMemoriaWindows.h"

#elif defined(__linux__)

#include "Linux/MonitorMemoriaLinux.h"

#else

#error "Sistema operacional nao suportado para monitoramento de memoria."

#endif

std::unique_ptr<MonitorMemoriaProcesso>
criarMonitorMemoriaProcesso() {

#if defined(_WIN32)

    return std::make_unique<MonitorMemoriaWindows>();

#elif defined(__linux__)

    return std::make_unique<MonitorMemoriaLinux>();

#endif
}