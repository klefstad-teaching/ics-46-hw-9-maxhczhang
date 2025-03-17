#include "dijkstras.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << "<input_file>\n";
        return 1;
    }

    Graph G;
    file_to_graph(argv[1], G);

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    for (int i = 0; i < G.numVertices; i++)
    {
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }

    return 0;
}
