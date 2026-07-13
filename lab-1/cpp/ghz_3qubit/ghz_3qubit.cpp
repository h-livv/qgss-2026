// 3-qubit GHZ state

#include "compat/quantumcircuit.hpp"
#include "compat/statevector.hpp"

using namespace Qiskit::compat;

int main() {
    QuantumCircuit circ(3, 0);

    circ.h(0);
    circ.cx(0, 1);
    circ.cx(1, 2);
    circ.draw();

    auto sv = Statevector::from_instruction(circ);
    std::cout << "3-qubit GHZ: " << sv << std::endl;

    return 0;
}
