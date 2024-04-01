/*  Identifier = 15C1680EE94C640EC35E1694295A3625C3254CBA

    EECS 281 Lab 4: Connected Components

    For this lab, you will write a program that calculates the
    number of connected components in an undirected graph.

    Your program will receive an input file in the following format:
    1) The first line of input contains the number of vertices V and number
       of edges E in the graph.
    2) The next E lines list out the connections between vertices in the
       graph in the format of "u v", which indicates the existence of an edge
       between u and v.

    For example, the following input file would be read as follows:
    4 2  (the graph has 4 vertices numbered from 0-3, and two edges exist in
          the graph)
    0 1  (the first of these edges connects vertex 0 with vertex 1)
    0 2  (the second of these edges connects vertex 0 with vertex 2)

    In this case, vertices {0, 1, 2} form a connected component, and vertex
    {3} forms a connected component (since 3 is not connected to anything).
    Thus, your program should print out 2.

    You will be using union-find to complete this lab. The following starter
    code has been provided. Feel free to modify this code in your
    implementation. Good luck!
*/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <numeric>

class Graph
{
    uint32_t V;
    uint32_t E;
    vector<uint32_t> parent;
    vector<uint32_t> rank;

public:
    Graph(uint32_t v, uint32_t e) : V{v}, E{e}, parent(v), rank(v, 0)
    {
        std::iota (std::begin(parent), std::end(parent), 0); 
    }

    uint32_t find_set(uint32_t v)
    {
        if (v != parent[v])
        {
            parent[v] = find_set(parent[v]); // Path compression
        }
        return parent[v];
    }

    void union_set(uint32_t a, uint32_t b)
    {
        uint32_t rootA = find_set(a);
        uint32_t rootB = find_set(b);
        if (rootA != rootB)
        {
            if (rank[rootA] > rank[rootB])
            {
                parent[rootB] = rootA;
            }
            else
            {
                parent[rootA] = rootB;
                if (rank[rootA] == rank[rootB])
                {
                    rank[rootB]++;
                }
            }
        }
    }

    uint32_t count_components()
    {
        uint32_t count = 0;
        for (uint32_t i = 0; i < V; ++i)
        {
            if (parent[i] == i)
            {
                count++;
            }
        }
        return count;
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    uint32_t vertex_count, edge_count, u, v;

    cin >> vertex_count >> edge_count;

    Graph g(vertex_count, edge_count);

    for (uint32_t i = 0; i < edge_count; ++i)
    {
        cin >> u >> v;
        g.union_set(u, v);
    }

    cout << g.count_components() << endl;
    return 0;
}
