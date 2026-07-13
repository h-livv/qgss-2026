// FakeTorino-equivalent backend information

#include "compat/quantumcircuit.hpp"
#include "compat/statevector.hpp"
#include "compat/target.hpp"
#include "compat/transpile.hpp"

using namespace Qiskit::compat;

int main() {
    auto target = make_torino_target();

    std::cout << "Backend: FakeTorino (Heron processor)" << std::endl;
    std::cout << "Qubits: " << target.num_qubits() << std::endl;

    auto gates = torino_basis_gates();
    std::cout << "Native gates:";
    for (auto& g : gates) std::cout << " " << g;
    std::cout << std::endl;

    return 0;
}
