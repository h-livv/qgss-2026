// Exercise 1: Build the |01> + |10> Bell state

#include "compat/quantumcircuit.hpp"
#include <fstream>
#include "compat/statevector.hpp"

using namespace Qiskit::compat;

int main() {
    QuantumCircuit circ(2, 0);

    // TODO: ADD YOUR CODE HERE
    circ.h(0);       // Put qubit 0 in superposition
    circ.cx(0, 1);   // Entangle qubit 1 with qubit 0
    circ.x(1);       // Flip qubit 1

    circ.draw();

    // Emit OpenQASM 3 for grading via the Python qc_grader client.
    std::ofstream qasm_out("../bell_exercise/circuit.qasm");
    qasm_out << circ.to_qasm3();
    qasm_out.close();

    auto sv = Statevector::from_instruction(circ);
    std::cout << "Your state: " << sv << std::endl;

    return 0;
}
