#include "dijkstras.h"
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    previous.assign(numVertices, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
    minHeap.push({source, 0});
    distances[source] = 0;

    while (!minHeap.empty())
    {
        int u = minHeap.top().second;
        minHeap.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& edge : G[u])
        {
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && distances[u] != INF && distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    vector<int> path;
    for (int v = destination; v != -1; v = previous[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total_cost)
{
    for (size_t i = 0; i < path.size(); i++)
    {
        cout << path[i];
        if (i < path.size()) cout << " ";
    }
    cout << "\nTotal cost is " << total_cost << "\n";
}