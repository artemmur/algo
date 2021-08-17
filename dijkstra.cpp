#include <iostream>
#include <vector>
#include <set>
#include <climits>

namespace listGraph {
class ListGraph {
public:
    ListGraph(size_t l_verticesNum);
    ~ListGraph() = default;

    void AddEdge(size_t l_from, size_t l_to, size_t l_weight);
    size_t VerticesCount() const;

    std::vector<std::pair<size_t, size_t>> GetNextVertices(size_t l_vertex) const;

private:
    std::vector<std::vector<std::pair<size_t, size_t>>> _vertices;
};

ListGraph::ListGraph(size_t l_verticesNum)
    : _vertices(l_verticesNum) {}

void ListGraph::AddEdge(size_t l_from, size_t l_to, size_t l_weight) {
    _vertices[l_from].emplace_back(l_to, l_weight);
    _vertices[l_to].emplace_back(l_from, l_weight);
}

size_t ListGraph::VerticesCount() const {
    return _vertices.size();
}

std::vector<std::pair<size_t, size_t>> ListGraph::GetNextVertices(size_t l_vertex) const {
    return _vertices[l_vertex];
}
}  // listGraph

int getShortPath(const listGraph::ListGraph& l_graph, size_t l_from, size_t l_to) {
    std::vector<int> distance(l_graph.VerticesCount(), INT_MAX);
    distance[l_from] = 0;
    
    std::set<std::pair<int, size_t>> queue;
    queue.emplace(distance[l_from], l_from);

    while(!queue.empty()) {
        size_t curr = (queue.begin())->second;
        queue.erase(queue.begin());
        std::vector<std::pair<size_t, size_t>> nextVert = l_graph.GetNextVertices(curr);
        for (const auto& nextPair : nextVert) {
            size_t next = nextPair.first;
            size_t weight = nextPair.second;
            if (distance[next] > static_cast<int>(distance[curr] + weight)) {
                if (distance[next] != INT_MAX) {
                    queue.erase(std::make_pair(distance[next], next));
                }
                distance[next] = distance[curr] + weight;
                queue.emplace(distance[next], next);
            }
        }
    }
    return distance[l_to];
}

int main() {
    size_t verticesNum = 0;
    std::cin >> verticesNum;
    listGraph::ListGraph graph(verticesNum);

    size_t edgesNum = 0;
    std::cin >> edgesNum;

    size_t from = 0;
    size_t to = 0;
    for (size_t i = 0; i < edgesNum; ++i) {
        size_t weight = 0;
        std::cin >> from >> to >> weight;
        graph.AddEdge(from, to, weight);
    }
    std::cin >> from >> to;
    std::cout << getShortPath(graph, from, to);
    return 0;
}