// GHZ starting from the middle, fanning out in both directions

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

QuantumCircuit ghz_half(int n) {
    QuantumCircuit circ(n, 0);
    int mid = n / 2;
    circ.h(mid);

    for (int step = 1; step < n; step++) {
        int left = mid - step;
        int right = mid + step;
        if (left >= 0)
            circ.cx(left + 1, left);
        if (right < n)
            circ.cx(right - 1, right);
        if (left <= 0 && right >= n - 1)
            break;
    }
    return circ;
}

int main() {
    auto qc_half = ghz_half(20);
    qc_half.draw();

    std::cout << "Half-depth GHZ (20 qubits): depth "
              << qc_half.depth() << std::endl;
    auto qc_chain = ghz_chain(20);
    std::cout << "Linear GHZ (20 qubits):     depth "
              << qc_chain.depth() << std::endl;

    return 0;
}
