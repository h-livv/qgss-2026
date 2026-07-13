// Create |00> - |11> by adding a Z gate

#include "compat/quantumcircuit.hpp"
#include "compat/statevector.hpp"

using namespace Qiskit::compat;

int main() {
    QuantumCircuit circ(2, 0);

    circ.h(0);
    circ.cx(0, 1);
    circ.z(0);         // Try changing to circ.z(1) -- same result!
    circ.draw();

    auto sv = Statevector::from_instruction(circ);
    std::cout << "|00> - |11>: " << sv << std::endl;

    return 0;
}
