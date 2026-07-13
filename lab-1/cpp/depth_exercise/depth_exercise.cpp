// Exercise 2: Predict the circuit depth
// Look at each circuit and predict its depth before reading the output!

#include "compat/quantumcircuit.hpp"
#include "compat/statevector.hpp"

using namespace Qiskit::compat;

int main() {
    // Circuit A
    QuantumCircuit qc_a(4, 0);
    qc_a.h(0);
    qc_a.h(1);
    qc_a.cx(0, 2);
    qc_a.cx(1, 3);
    qc_a.cx(2, 3);
    std::cout << "Circuit A:" << std::endl;
    qc_a.draw();

    // Circuit B
    QuantumCircuit qc_b(3, 0);
    qc_b.h(0);
    qc_b.cx(0, 1);
    qc_b.h(2);
    qc_b.cx(2, 1);
    std::cout << "\nCircuit B:" << std::endl;
    qc_b.draw();

    // Check your predictions!
    std::cout << "\n--- Answers ---" << std::endl;
    std::cout << "Circuit A depth: " << qc_a.depth() << std::endl;
    std::cout << "Circuit B depth: " << qc_b.depth() << std::endl;

    return 0;
}
