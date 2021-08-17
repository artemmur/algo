#include "listGraph.hpp"

ListGraph::ListGraph(size_t l_verticesNum)
    : _vertices(l_verticesNum) {}

ListGraph::ListGraph(const IGraph& l_graph)
    : _vertices(l_graph.VerticesCount()) {

    for (size_t i = 0; i < l_graph.VerticesCount(); ++i) {
        _vertices[i] = l_graph.GetNextVertices(i);
    }
}

void ListGraph::AddEdge(size_t l_from, size_t l_to) {
    _vertices[l_from].emplace_back(l_to);
}

size_t ListGraph::VerticesCount() const {
    return _vertices.size();
}

std::vector<size_t> ListGraph::GetNextVertices(size_t l_vertex) const {
    return _vertices[l_vertex];
}

std::vector<size_t> ListGraph::GetPrevVertices(size_t l_vertex) const {
    std::vector<size_t> preVert;
    for (size_t i = 0; i < VerticesCount(); ++i) {
        for (size_t j = 0; j < _vertices[i].size(); ++j) {
            if (_vertices[i][j] == l_vertex) {
                preVert.push_back(i);
            }
        }
    }
    return preVert;
}
