#include "setGraph.hpp"

SetGraph::SetGraph(size_t l_verticesNum)
    : _vertices(l_verticesNum) {}

SetGraph::SetGraph(const IGraph& l_graph)
    : _vertices(l_graph.VerticesCount()) {

    for (size_t i = 0; i < l_graph.VerticesCount(); ++i) {
        const auto nextVertices = l_graph.GetNextVertices(i);
        for (const size_t& vert : nextVertices) {
            AddEdge(i, vert);
        }
    }
}

void SetGraph::AddEdge(size_t l_from, size_t l_to) {
    _vertices[l_from].emplace(l_to);
}

size_t SetGraph::VerticesCount() const {
    return _vertices.size();
}

std::vector<size_t> SetGraph::GetNextVertices(size_t l_vertex) const {
    return {_vertices[l_vertex].begin(), _vertices[l_vertex].end()};
}

std::vector<size_t> SetGraph::GetPrevVertices(size_t l_vertex) const {
    std::vector<size_t> preVertices;
    for (size_t i = 0; i < VerticesCount(); ++i) {
        const auto& nextVertices = _vertices[i];
        for (const auto& vert : nextVertices) {
            if (vert == l_vertex) {
                preVertices.push_back(i);
            }
        }
    }
    return preVertices;
}
