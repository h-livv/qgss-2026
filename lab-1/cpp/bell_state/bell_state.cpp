// Create the Bell state (|00> + |11>) / sqrt(2)

#include "compat/quantumcircuit.hpp"
#include "compat/statevector.hpp"

using namespace Qiskit::compat;

int main() {
    QuantumCircuit circ(2, 0);

    circ.h(0);       // Put qubit 0 in superposition
    circ.cx(0, 1);   // Entangle qubit 1 with qubit 0
    circ.draw();

    auto sv = Statevector::from_instruction(circ);
    std::cout << "Bell state: " << sv << std::endl;

    return 0;
}
