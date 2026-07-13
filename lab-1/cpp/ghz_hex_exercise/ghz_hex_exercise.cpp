// Exercise 6: 7-qubit GHZ on a heavy-hex T-shaped subgraph
//
// Subgraph adjacency (abstract qubit numbering):
// 0(q23) -- 1(q24) -- 2(q25) -- 3(q26) -- 4(q27)
//                      |
//                    5(q35)
//                      |
//                    6(q44)

#include "compat/quantumcircuit.hpp"
#include <fstream>
#include "compat/statevector.hpp"
#include "compat/target.hpp"
#include "compat/transpile.hpp"

using namespace Qiskit::compat;

int main() {
    QuantumCircuit circ(7, 0);

    // TODO: ADD YOUR CODE HERE: build GHZ starting from the best qubit (the junction)
    circ.h(2);
    circ.cx(2, 1);
    circ.cx(2, 3);
    circ.cx(2, 5);
    circ.cx(1,0);
    circ.cx(3,4);
    circ.cx(5,6);


    circ.draw();

    auto d = circ.depth();
    std::cout << "Abstract depth: " << d << std::endl;

    // Verify it is a valid 7-qubit GHZ state
    // Emit OpenQASM 3 for grading via the Python qc_grader client.
    std::ofstream qasm_out("../ghz_hex_exercise/circuit.qasm");
    qasm_out << circ.to_qasm3();
    qasm_out.close();

    auto sv = Statevector::from_instruction(circ);
    auto data = sv.data();
    double prob_0 = std::norm(data[0]);
    double prob_last = std::norm(data.back());

    if (std::abs(prob_0 - 0.5) < 0.01 && std::abs(prob_last - 0.5) < 0.01) {
        std::cout << "Valid 7-qubit GHZ state!" << std::endl;
    } else {
        std::cout << "Not a valid GHZ state. Check your circuit." << std::endl;
    }

    // Transpile with the physical layout
    auto circ_meas = circ.measure_all();

    auto target = make_torino_target();
    auto pm = generate_preset_pass_manager(1, target);
    auto isa_qc = pm.run(circ_meas);

    std::cout << "Transpiled depth: " << isa_qc.depth() << std::endl;
    auto ops = isa_qc.count_ops();
    std::cout << "CZ gates: " << (ops.count("cz") ? ops["cz"] : 0) << std::endl;

    return 0;
}
