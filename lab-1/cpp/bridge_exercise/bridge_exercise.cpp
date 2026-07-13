// Exercise 4: Build a 3-qubit GHZ using only nearest-neighbor CX gates (bridge identity)

#include "compat/quantumcircuit.hpp"
#include <fstream>
#include "compat/statevector.hpp"

using namespace Qiskit::compat;

int main() {
    QuantumCircuit qc(3, 0);
    qc.h(0);
    qc.cx(0, 1);

    // TODO: ADD YOUR CODE HERE: replace the non-local CX(0, 2) using the bridge identity
    QuantumCircuit qc_bridge(3, 0);
    qc.cx(0, 1);
    qc.cx(1, 2);
    qc.cx(0, 1);
    qc.cx(1, 2);

    qc.draw();

    // Emit OpenQASM 3 for grading via the Python qc_grader client.
    std::ofstream qasm_out("../bridge_exercise/circuit.qasm");
    qasm_out << qc.to_qasm3();
    qasm_out.close();

    auto sv = Statevector::from_instruction(qc);
    std::cout << "Your state: " << sv << std::endl;

    // Check: should be a valid 3-qubit GHZ state with prob 0.5 each for |000> and |111>
    auto data = sv.data();
    double prob_0 = std::norm(data[0]);
    double prob_last = std::norm(data.back());

    if (std::abs(prob_0 - 0.5) < 0.01 && std::abs(prob_last - 0.5) < 0.01) {
        std::cout << "Valid 3-qubit GHZ state!" << std::endl;
    } else {
        std::cout << "Not a valid GHZ state. Check your CX gates." << std::endl;
    }

    auto ops = qc.count_ops();
    std::cout << "CX gate count: " << ops["cx"] << std::endl;

    return 0;
}
