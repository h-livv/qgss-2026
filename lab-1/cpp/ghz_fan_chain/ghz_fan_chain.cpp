// Two ways to build an N-qubit GHZ state

#include "compat/quantumcircuit.hpp"
#include "compat/statevector.hpp"

using namespace Qiskit::compat;

QuantumCircuit ghz_fan(int n) {
    QuantumCircuit circ(n, 0);
    circ.h(0);
    for (int i = 1; i < n; i++)
        circ.cx(0, i);
    return circ;
}

QuantumCircuit ghz_chain(int n) {
    QuantumCircuit circ(n, 0);
    circ.h(0);
    for (int i = 0; i < n - 1; i++)
        circ.cx(i, i + 1);
    return circ;
}

int main() {
    std::cout << "Fan-out (5 qubits):" << std::endl;
    auto fan = ghz_fan(5);
    fan.draw();

    std::cout << "\nChain (5 qubits):" << std::endl;
    auto chain = ghz_chain(5);
    chain.draw();

    return 0;
}
