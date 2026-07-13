// Optional: Build |01> - |10>

#include "compat/quantumcircuit.hpp"
#include "compat/statevector.hpp"

using namespace Qiskit::compat;

int main() {
    QuantumCircuit circ(2, 0);

    // TODO: ADD YOUR CODE HERE
    circ.h(0);
    circ.cx(0, 1);
    circ.x(0);
    circ.z(1);

    circ.draw();

    auto sv = Statevector::from_instruction(circ);
    std::cout << "Your state: " << sv << std::endl;

    return 0;
}
