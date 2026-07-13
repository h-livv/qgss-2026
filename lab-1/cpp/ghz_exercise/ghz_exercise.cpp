// Exercise 3: Build a depth-5 GHZ state for 16 qubits

#include "compat/quantumcircuit.hpp"
#include <fstream>
#include "compat/statevector.hpp"
#include <vector>
#include <algorithm>

using namespace Qiskit::compat;

int main() {
    QuantumCircuit circ(16, 0);

    // Layer 0: Hadamard -- 1 qubit in superposition
    circ.h(0);
    std::vector<int> entangled = {0};

    // Layer 1: 1 CX gate -> 2 entangled qubits
    // TODO: ADD YOUR CODE HERE
    for (int i = 0; i < 1; i++){
            circ.cx(entangled[i], i+1);
            entangled.push_back(i+1);
    }

    // Layer 2: 2 CX gates -> 4 entangled qubits
    // TODO: ADD YOUR CODE HERE
    for (int i = 0; i < 2; i++){
            circ.cx(entangled[i], i+2);
            entangled.push_back(i+2);
    }

    // Layer 3: 4 CX gates -> 8 entangled qubits
    // TODO: ADD YOUR CODE HERE
    for (int i = 0; i < 4; i++){
            circ.cx(entangled[i], i+4);
            entangled.push_back(i+4);
    }

    // Layer 4: 8 CX gates -> 16 entangled qubits
    // TODO: ADD YOUR CODE HERE
    for (int i = 0; i < 8; i++){
            circ.cx(entangled[i], i+8);
            entangled.push_back(i+8);
    }

    circ.draw();

    auto d = circ.depth();
    std::cout << "Depth: " << d << std::endl;

    // Verify: check that it is a valid GHZ state
    // Emit OpenQASM 3 for grading via the Python qc_grader client.
    std::ofstream qasm_out("../ghz_exercise/circuit.qasm");
    qasm_out << circ.to_qasm3();
    qasm_out.close();

    auto sv = Statevector::from_instruction(circ);
    auto data = sv.data();
    double prob_0 = std::norm(data[0]);
    double prob_last = std::norm(data.back());

    if (d == 5 && std::abs(prob_0 - 0.5) < 0.01 && std::abs(prob_last - 0.5) < 0.01) {
        std::cout << "Valid 16-qubit GHZ state with depth 5!" << std::endl;
    } else {
        std::cout << "Not quite right. Check your CX gates." << std::endl;
    }

    return 0;
}
