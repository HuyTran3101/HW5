#include "Graph.h"
#include "BetterPriorityQueue.h"
#include <cassert>
#include <iostream>

using namespace std;

void ContainsTest() {
    cout << "Testing Contains Helper Method..." << endl;

    Graph g = Graph();
    BetterPriorityQueue q;

    g.AddNode(1);
    g.AddNode(2);
    g.AddNode(3);
    g.AddNode(4);
    g.AddNode(5);
    g.AddNode(6);

    set<nodekey_t> nodes = g.GetNodes();

    for (nodekey_t n : nodes) {
        BPQNode cur;
        cur.gnode = n;
        q.push(cur);
    }

    // Test existing node
    BPQNode positive;
    positive.gnode = 2;
    assert(q.Contains(positive) == true);

    // Test missing node
    BPQNode negative;
    assert(q.Contains(negative) == false);

    // Make sure the previous search did not change the queue
    assert(q.Contains(positive) == true);

    cout << "PASSED!" << endl;
}

void UpdateTest() {
    cout << "Testing Update Helper Method..." << endl;

    Graph g = Graph();
    BetterPriorityQueue q;

    g.AddNode(1);
    g.AddNode(2);
    g.AddNode(3);
    g.AddNode(4);
    g.AddNode(5);
    g.AddNode(6);

    set<nodekey_t> nodes = g.GetNodes();

    size_t i = 0;

    for (nodekey_t n : nodes) {
        BPQNode cur;
        cur.pri = i;
        cur.gnode = n;
        q.push(cur);
        i++;
    }

    // Test decreasing the priority of node 6 to zero
    BPQNode positive;
    positive.gnode = 6;
    positive.pri = 0;

    cout << "q before: " << q.ToString() << endl;

    assert(q.Update(positive) == true);

    cout << "q after: " << q.ToString() << endl;

    // Accept valid heap orders specified by the instructor
    string soln1 =
        "[(6, pri: 0), (1, pri: 0), (2, pri: 1), "
        "(3, pri: 2), (4, pri: 3), (5, pri: 4)]";

    string soln2 =
        "[(1, pri: 0), (2, pri: 1), (6, pri: 0), "
        "(4, pri: 3), (5, pri: 4), (3, pri: 2)]";

    string soln3 =
        "[(1, pri: 0), (6, pri: 0), (2, pri: 1), "
        "(3, pri: 2), (4, pri: 3), (5, pri: 4)]";

    // Updating a missing node should return false
    BPQNode negative;
    assert(q.Update(negative) == false);

    cout << "q after test 2: " << q.ToString() << endl;

    assert(q.ToString() == soln1 ||
           q.ToString() == soln2 ||
           q.ToString() == soln3);

    // Larger priorities should be ignored
    BPQNode negative2;
    negative2.gnode = 5;
    negative2.pri = 80;

    assert(q.Update(negative2) == false);

    cout << "q after test 3: " << q.ToString() << endl;

    assert(q.ToString() == soln1 ||
           q.ToString() == soln2 ||
           q.ToString() == soln3);

    cout << "PASSED!" << endl;
}

// Additional tests beyond the instructor's starter
void AdditionalBPQTests() {
    cout << "Testing additional priority queue cases..." << endl;

    BetterPriorityQueue q;

    BPQNode missing;
    missing.gnode = 99;

    // Empty queue
    assert(q.empty());
    assert(q.ToString() == "[]");
    assert(!q.Contains(missing));
    assert(!q.Update(missing));

    // Insert eight nodes with different priorities
    for (int i = 1; i <= 8; i++) {
        BPQNode node;
        node.gnode = i;
        node.pri = i * 10;
        q.push(node);
    }

    // Decrease node 8's priority to 2
    BPQNode target;
    target.gnode = 8;
    target.pri = 2;

    assert(q.Contains(target));
    assert(q.Update(target));

    // Node 8 should now have the smallest priority
    assert(q.top().gnode == 8);
    assert(q.top().pri == 2);

    // Same or larger priorities should be ignored
    assert(!q.Update(target));

    target.pri = 100;
    assert(!q.Update(target));
    assert(q.top().pri == 2);

    // Missing nodes should not change the queue
    string before = q.ToString();

    assert(!q.Update(missing));
    assert(q.ToString() == before);

    assert(
        BetterPriorityQueue::BPQNodeToString(q.top())
        == "(8, pri: 2)"
    );

    // Test that removing nodes produces ascending priorities
    int previous = -1;

    while (!q.empty()) {
        int priority = q.top().pri;

        assert(priority >= previous);

        previous = priority;
        q.pop();
    }

    assert(q.ToString() == "[]");

    cout << "PASSED!" << endl;
}

int main() {
    ContainsTest();
    UpdateTest();
    AdditionalBPQTests();

    cout << "ALL TESTS PASSED!!" << endl;
    return 0;
}