// Exercise 5: Efficient 5-qubit GHZ on a line
// Build a depth-4 GHZ starting from the middle qubit

#include "compat/quantumcircuit.hpp"
#include <fstream>
#include "compat/statevector.hpp"
#include "compat/target.hpp"
#include "compat/transpile.hpp"

using namespace Qiskit::compat;

int main() {
    QuantumCircuit circ(5, 0);

    // TODO: ADD YOUR CODE HERE: build a depth-4 GHZ starting from the middle
    int mid = 5/2;
    circ.h(mid);

    for (int step = 1; step < 5; step++) {
        int left = mid - step;
        int right = mid + step;
        if (left >= 0)
            circ.cx(left + 1, left);
        if (right < 5)
            circ.cx(right - 1, right);
        if (left <= 0 && right >= 4)
            break;
    }

    circ.draw();

    auto d = circ.depth();
    std::cout << "Abstract depth: " << d << std::endl;

    if (d == 4) {
        std::cout << "Correct! Depth 4 achieved." << std::endl;
    } else {
        std::cout << "Expected depth 4, got " << d << ". Try again!" << std::endl;
    }

    // Transpile for the line subgraph 0-1-2-3-4
    // Emit OpenQASM 3 for grading via the Python qc_grader client.
    std::ofstream qasm_out("../ghz_line_exercise/circuit.qasm");
    qasm_out << circ.to_qasm3();
    qasm_out.close();

    auto circ_meas = circ.measure_all();

    auto target = make_torino_target();
    auto pm = generate_preset_pass_manager(1, target);
    auto isa_qc = pm.run(circ_meas);

    std::cout << "Transpiled depth: " << isa_qc.depth() << std::endl;
    auto ops = isa_qc.count_ops();
    std::cout << "CZ gates: " << (ops.count("cz") ? ops["cz"] : 0) << std::endl;

    return 0;
}
