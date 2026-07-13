// Exercise 7: 64-qubit GHZ using BFS on the heavy-hex topology

#include <queue>
#include <map>
#include "compat/quantumcircuit.hpp"
#include <fstream>
#include "compat/target.hpp"
#include "compat/transpile.hpp"

using namespace Qiskit::compat;

int main() {
    auto adj = torino_adjacency(64);
    int n = 64;
    int center = 25;  // Try changing this!

    // Show degree-3 junctions
    std::cout << "Degree-3 junctions in qubits 0-63:" << std::endl;
    for (int q = 0; q < n; q++) {
        if (adj[q].size() >= 3) {
            std::cout << "  Qubit " << q << ": neighbors {";
            for (size_t i = 0; i < adj[q].size(); i++) {
                if (i > 0) std::cout << ", ";
                std::cout << adj[q][i];
            }
            std::cout << "}" << std::endl;
        }
    }

    // Step 1: Build a spanning tree via BFS from center
    std::map<int, int> parent;
    std::map<int, int> bfs_depth;
    parent[center] = -1;
    bfs_depth[center] = 0;
    std::queue<int> queue;
    queue.push(center);

    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();
        for (int nb : adj[node]) {
            if (parent.find(nb) == parent.end()) {
                parent[nb] = node;
                bfs_depth[nb] = bfs_depth[node] + 1;
                queue.push(nb);
            }
        }
    }

    int max_d = 0;
    for (auto& kv : bfs_depth)
        max_d = std::max(max_d, kv.second);

    std::cout << "\nBFS from qubit " << center
              << ": reached " << parent.size() << " qubits" << std::endl;
    std::cout << "Max BFS depth: " << max_d << std::endl;

    // Step 2: Build GHZ circuit layer by layer along the BFS tree
    QuantumCircuit circ(n, 0);
    circ.h(center);

    for (int d = 1; d <= max_d; d++) {
        for (int q = 0; q < n; q++) {
            if (bfs_depth.count(q) && bfs_depth[q] == d) {
                // TODO: ADD YOUR CODE HERE: add CX from parent[q] to q
                circ.cx(parent[q], q);
            }
        }
    }

    std::cout << "\nYour GHZ abstract depth: " << circ.depth() << std::endl;

    // Transpile and compare with naive chain
    // Emit OpenQASM 3 for grading via the Python qc_grader client.
    std::ofstream qasm_out("../ghz_64_exercise/circuit.qasm");
    qasm_out << circ.to_qasm3();
    qasm_out.close();

    auto circ_meas = circ.measure_all();

    auto target = make_torino_target();
    auto pm = generate_preset_pass_manager(1, target);
    auto isa_qc = pm.run(circ_meas);

    auto ops = isa_qc.count_ops();
    std::cout << "Your GHZ transpiled depth: " << isa_qc.depth() << std::endl;
    std::cout << "Your GHZ CZ gates: " << (ops.count("cz") ? ops["cz"] : 0) << std::endl;

    // Naive chain for comparison
    QuantumCircuit naive(n, 0);
    naive.h(0);
    for (int q = 0; q < n - 1; q++)
        naive.cx(q, q + 1);
    auto naive_meas = naive.measure_all();

    auto isa_naive = pm.run(naive_meas);
    auto ops_naive = isa_naive.count_ops();
    std::cout << "\nNaive chain transpiled depth: " << isa_naive.depth() << std::endl;
    std::cout << "Naive chain CZ gates: " << (ops_naive.count("cz") ? ops_naive["cz"] : 0) << std::endl;

    return 0;
}
