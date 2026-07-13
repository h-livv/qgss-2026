// Build a circuit that applies an X gate to a single qubit

#include "compat/quantumcircuit.hpp"
#include "compat/statevector.hpp"

using namespace Qiskit::compat;

int main() {
    QuantumCircuit circ(1, 0);

    circ.x(0);
    circ.draw();

    auto sv = Statevector::from_instruction(circ);
    std::cout << "X|0> = " << sv << std::endl;

    return 0;
}
