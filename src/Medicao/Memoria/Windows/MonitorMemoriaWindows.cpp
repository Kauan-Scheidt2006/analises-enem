#include "MonitorMemoriaWindows.h"

#include <windows.h>
#include <psapi.h>

#include <string>

MemoriaProcesso MonitorMemoriaWindows::consultar() const {
    MemoriaProcesso memoria;

    PROCESS_MEMORY_COUNTERS_EX contadores{};

    contadores.cb = sizeof(contadores);

    const BOOL sucesso = GetProcessMemoryInfo(
        GetCurrentProcess(),
        reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&contadores),
        sizeof(contadores)
    );

    if (!sucesso) {
        memoria.diagnosticos.emplace_back(
            "Falha ao consultar a memoria do processo no Windows. "
            "Codigo do erro: " + std::to_string(GetLastError())
        );

        return memoria;
    }

    memoria.workingSetBytes =
        static_cast<std::uint64_t>(contadores.WorkingSetSize);

    memoria.privateUsageBytes =
        static_cast<std::uint64_t>(contadores.PrivateUsage);

    memoria.peakWorkingSetBytes =
        static_cast<std::uint64_t>(contadores.PeakWorkingSetSize);

    memoria.peakPrivateUsageBytes =
        static_cast<std::uint64_t>(contadores.PeakPagefileUsage);

    memoria.definicaoMemoriaPrivada =
        DefinicaoMemoriaPrivada::MemoriaComprometida;

    return memoria;
}
