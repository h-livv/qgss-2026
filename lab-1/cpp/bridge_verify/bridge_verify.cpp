// Verify the bridge identity: CX(0, 2) == CX(0,1) CX(1,2) CX(0,1) CX(1,2)

#include "compat/quantumcircuit.hpp"
#include "compat/statevector.hpp"

using namespace Qiskit::compat;

int main() {
    // Direct: one long-distance CX (with H on qubit 0 so the entangling action is visible)
    QuantumCircuit qc_direct(3, 0);
    qc_direct.h(0);
    qc_direct.cx(0, 2);

    // Bridge: four nearest-neighbor CX gates
    QuantumCircuit qc_bridge(3, 0);
    qc_bridge.h(0);
    qc_bridge.cx(0, 1);
    qc_bridge.cx(1, 2);
    qc_bridge.cx(0, 1);
    qc_bridge.cx(1, 2);

    auto sv_direct = Statevector::from_instruction(qc_direct);
    auto sv_bridge = Statevector::from_instruction(qc_bridge);

    std::cout << "Direct CX(0, 2): " << sv_direct << std::endl;
    std::cout << "Bridge form:    " << sv_bridge << std::endl;

    return 0;
}
