#include <iostream>
#include <vector>
#include <queue>
#include <climits>

namespace listGraph {
class ListGraph {
public:
    ListGraph(size_t num_vertices);
    ~ListGraph() = default;

    void AddEdge(size_t from, size_t to);
    size_t VerticesCount() const;

    std::vector<size_t> GetNextVertices(size_t vertex) const;

private:
    std::vector<std::vector<size_t>> _vertices;
};

ListGraph::ListGraph(size_t l_verticesNum)
    : _vertices(l_verticesNum) {}

void ListGraph::AddEdge(size_t l_from, size_t l_to) {
    _vertices[l_from].emplace_back(l_to);
    _vertices[l_to].emplace_back(l_from);
}

size_t ListGraph::VerticesCount() const {
    return _vertices.size();
}

std::vector<size_t> ListGraph::GetNextVertices(size_t l_vertex) const {
    return _vertices[l_vertex];
}
}  // listGraph

size_t shortPathNum(const listGraph::ListGraph& l_graph, size_t l_from, size_t l_to) {
    std::vector<int> distance(l_graph.VerticesCount(), INT_MAX);
    distance[l_from] = 0;

    std::vector<size_t> pathCount(l_graph.VerticesCount(), 0);
    pathCount[l_from] = 1;

    std::queue<size_t> queue;
    queue.push(l_from);

    while(!queue.empty()) {
        size_t curr = queue.front();
        queue.pop();
        std::vector<size_t> nextVert = l_graph.GetNextVertices(curr);
        for (auto next : nextVert) {
            if (distance[next] == INT_MAX) {
                distance[next] = distance[curr] + 1;
                pathCount[next] = pathCount[curr];
                queue.push(next);
            } else if (distance[next] == distance[curr] + 1) {
                pathCount[next] += pathCount[curr];
            }
        }
    }
    return pathCount[l_to];
}

int main() {
    size_t verticesNum = 0;
    std::cin >> verticesNum;
    listGraph::ListGraph graph(verticesNum);

    size_t edgesNum = 0;
    std::cin >> edgesNum;

    size_t from = 0;
    size_t to = 0;
    for (size_t i = 0; i < edgesNum; ++i){
        std::cin >> from >> to;
        graph.AddEdge(from, to);
    }
    std::cin >> from >> to;
    std::cout << shortPathNum(graph, from, to);
    return 0;
}
