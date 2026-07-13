// Circuit depth examples

#include "compat/quantumcircuit.hpp"
#include "compat/statevector.hpp"

using namespace Qiskit::compat;

int main() {
    // Example 1: Two independent X gates -> depth 1 (parallel)
    QuantumCircuit qc1(2, 0);
    qc1.x(0);
    qc1.x(1);
    std::cout << "Two independent X gates -- depth: "
              << qc1.depth() << std::endl;
    qc1.draw();

    // Example 2: Two CX gates sharing qubit 0 -> depth 2 (sequential)
    QuantumCircuit qc2(3, 0);
    qc2.cx(0, 1);
    qc2.cx(0, 2);
    std::cout << "\nCX(0,1) then CX(0,2) -- depth: "
              << qc2.depth() << std::endl;
    qc2.draw();

    // Example 3: Two CX gates on disjoint qubits -> depth 1 (parallel)
    QuantumCircuit qc3(4, 0);
    qc3.cx(0, 1);
    qc3.cx(2, 3);
    std::cout << "\nCX(0,1) and CX(2,3) in parallel -- depth: "
              << qc3.depth() << std::endl;
    qc3.draw();

    return 0;
}
