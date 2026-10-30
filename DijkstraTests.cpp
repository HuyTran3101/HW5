#include "Graph.h"
#include "BetterPriorityQueue.h"
#include "Dijkstra.h"

#include <iostream>
#include <cassert>
#include <climits>
#include <stdexcept>

using namespace std;

int DijkstraTest() {
    cout << "Testing Dijkstra Algorithm..." << endl;

    // Original instructor test
    Graph* g = new Graph();

    g->AddNode(1);
    g->AddNode(2);
    g->AddNode(3);

    g->AddEdge(1, 2, 7);
    g->AddEdge(2, 1, 7);
    g->AddEdge(1, 3, 9);
    g->AddEdge(3, 1, 9);

    cout << "---Graph---" << endl;
    cout << "\tnodes: " << g->NodesToString() << endl;
    cout << "\tedges: " << g->EdgesToString() << endl;
    cout << "---Graph---" << endl << endl;

    nodekey_t start = 1;
    nodekey_t end = 3;

    cout << "start: " << start
         << "  goal: " << end << endl;

    int ans = dijkstra(start, end, g);

    cout << "Output from Dijkstra("
         << start << ", " << end
         << ") => " << ans << endl;

    assert(ans == 9);

    delete g;

    cout << "DONE with basic testing of Dijkstra algorithm"
         << endl;

    return ans;
}

// Six-node example from the assignment PDF
void SixNodeShortestPathTest() {
    cout << "Testing six-node graph..." << endl;

    Graph g;

    for (nodekey_t i = 1; i <= 6; i++) {
        g.AddNode(i);
    }

    // Add both directions because this example is undirected
    g.AddEdge(1, 2, 7);
    g.AddEdge(2, 1, 7);

    g.AddEdge(1, 3, 9);
    g.AddEdge(3, 1, 9);

    g.AddEdge(1, 6, 14);
    g.AddEdge(6, 1, 14);

    g.AddEdge(2, 3, 10);
    g.AddEdge(3, 2, 10);

    g.AddEdge(2, 4, 15);
    g.AddEdge(4, 2, 15);

    g.AddEdge(3, 4, 11);
    g.AddEdge(4, 3, 11);

    g.AddEdge(3, 6, 2);
    g.AddEdge(6, 3, 2);

    g.AddEdge(4, 5, 6);
    g.AddEdge(5, 4, 6);

    g.AddEdge(5, 6, 9);
    g.AddEdge(6, 5, 9);

    // Shortest: 1 -> 3 -> 6 -> 5
    // Cost: 9 + 2 + 9 = 20
    assert(dijkstra(1, 5, &g) == 20);

    // Shortest: 1 -> 3 -> 6
    assert(dijkstra(1, 6, &g) == 11);

    // Reverse path
    assert(dijkstra(5, 1, &g) == 20);

    // Starting and ending at the same node
    assert(dijkstra(4, 4, &g) == 0);

    cout << "PASSED!" << endl;
}

// Extra test cases
void AdditionalDijkstraTests() {
    cout << "Testing unreachable, directed, and zero-weight paths..."
         << endl;

    Graph g;

    g.AddNode(1);
    g.AddNode(2);
    g.AddNode(3);
    g.AddNode(4);

    // Node 4 has no connections
    g.AddEdge(1, 2, 10);
    g.AddEdge(1, 3, 1);
    g.AddEdge(3, 2, 2);
    g.AddEdge(2, 3, 0);
    g.AddEdge(3, 3, 0);

    // Indirect path is cheaper
    // 1 -> 3 -> 2 costs 1 + 2 = 3
    assert(dijkstra(1, 2, &g) == 3);

    // Zero-weight edge
    assert(dijkstra(2, 3, &g) == 0);

    // No directed path from 3 back to 1
    assert(dijkstra(3, 1, &g) == INT_MAX);

    // Node 4 is disconnected
    assert(dijkstra(1, 4, &g) == INT_MAX);

    // Same starting and ending node
    assert(dijkstra(4, 4, &g) == 0);

    // Invalid destination
    bool threw = false;

    try {
        dijkstra(1, 99, &g);
    }
    catch (const invalid_argument&) {
        threw = true;
    }

    assert(threw);

    // Null graph pointer
    threw = false;

    try {
        dijkstra(1, 2, nullptr);
    }
    catch (const invalid_argument&) {
        threw = true;
    }

    assert(threw);

    // Check large distances and integer overflow handling
    Graph large;

    large.AddNode(10);
    large.AddNode(11);
    large.AddNode(12);

    large.AddEdge(10, 11, INT_MAX - 5);
    large.AddEdge(11, 12, 10);

    assert(dijkstra(10, 11, &large) == INT_MAX - 5);
    assert(dijkstra(10, 12, &large) == INT_MAX);

    cout << "PASSED!" << endl;
}

int main() {
    DijkstraTest();
    SixNodeShortestPathTest();
    AdditionalDijkstraTests();

    cout << endl;
    cout << "ALL TESTS PASSED!" << endl;

    return 0;
}