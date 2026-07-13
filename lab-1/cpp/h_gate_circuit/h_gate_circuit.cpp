// Build a circuit that applies an H gate to a single qubit

#include "compat/quantumcircuit.hpp"
#include "compat/statevector.hpp"

using namespace Qiskit::compat;

int main() {
    QuantumCircuit circ(1, 0);

    circ.h(0);
    circ.draw();

    auto sv = Statevector::from_instruction(circ);
    std::cout << "H|0> = " << sv << std::endl;

    return 0;
}
