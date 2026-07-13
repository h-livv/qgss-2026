// Visualize heavy-hex connectivity for qubits 0-45
// (range extended to 0-45 so Exercise 6's T-junction at q25 -- whose third
//  neighbor q35 lies beyond the first two rows -- shows as degree-3)

#include "compat/quantumcircuit.hpp"
#include "compat/target.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using namespace Qiskit::compat;

int main() {
    int n = 46;
    auto adj = torino_adjacency(n);

    std::cout << "FakeTorino: Qubits 0-45 (heavy-hex topology)" << std::endl;
    std::cout << std::endl;

    // Show connectivity and identify degree-3 junctions
    std::vector<int> junctions;
    for (int q = 0; q < n; q++) {
        if (!adj[q].empty()) {
            std::cout << "  Qubit " << q << " -> {";
            for (size_t i = 0; i < adj[q].size(); i++) {
                if (i > 0) std::cout << ", ";
                std::cout << adj[q][i];
            }
            std::cout << "}";
            if (adj[q].size() >= 3) {
                std::cout << "  ** degree-3 junction **";
                junctions.push_back(q);
            }
            std::cout << std::endl;
        }
    }

    std::cout << "\nDegree-3 junctions (qubits 0-45):";
    for (int q : junctions) std::cout << " " << q;
    std::cout << std::endl;

    // Write graph data as JSON for the Python visualization cell
    nlohmann::json graph;
    graph["nodes"] = nlohmann::json::array();
    graph["edges"] = nlohmann::json::array();
    graph["junctions"] = junctions;

    for (int q = 0; q < n; q++)
        if (!adj[q].empty())
            graph["nodes"].push_back(q);

    for (int q = 0; q < n; q++)
        for (int nb : adj[q])
            if (q < nb)
                graph["edges"].push_back({q, nb});

    std::ofstream out("../topology_viz/graph.json");
    out << graph.dump() << std::endl;

    return 0;
}
