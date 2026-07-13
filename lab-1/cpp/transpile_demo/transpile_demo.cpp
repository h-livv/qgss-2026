// Transpile a simple 5-qubit chain GHZ circuit

#include "compat/quantumcircuit.hpp"
#include "compat/statevector.hpp"
#include "compat/target.hpp"
#include "compat/transpile.hpp"

using namespace Qiskit::compat;

QuantumCircuit ghz_chain(int n) {
    QuantumCircuit circ(n, 0);
    circ.h(0);
    for (int i = 0; i < n - 1; i++)
        circ.cx(i, i + 1);
    return circ;
}

int main() {
    auto target = make_torino_target();
    auto qc = ghz_chain(5);

    std::cout << "Original circuit:" << std::endl;
    qc.draw();

    auto qc_meas = qc.measure_all();

    auto pm = generate_preset_pass_manager(1, target);
    auto isa_qc = pm.run(qc_meas);

    std::cout << "\nTranspiled circuit:" << std::endl;
    isa_qc.draw(false);

    auto ops_before = qc.count_ops();
    auto ops_after = isa_qc.count_ops();

    std::cout << "\nBefore: depth " << qc.depth() << ", gates {";
    for (auto& kv : ops_before)
        std::cout << " " << kv.first << ":" << kv.second;
    std::cout << " }" << std::endl;

    std::cout << "After:  depth " << isa_qc.depth() << ", gates {";
    for (auto& kv : ops_after)
        std::cout << " " << kv.first << ":" << kv.second;
    std::cout << " }" << std::endl;

    return 0;
}
