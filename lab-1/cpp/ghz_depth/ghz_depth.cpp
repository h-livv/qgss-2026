// Compare depth of fan-out vs chain GHZ constructions

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
    for (int n : {5, 10, 20}) {
        auto fan = ghz_fan(n);
        auto chain = ghz_chain(n);
        std::cout << "n=" << n
                  << ":  fan depth = " << fan.depth()
                  << ",  chain depth = " << chain.depth()
                  << std::endl;
    }

    return 0;
}
