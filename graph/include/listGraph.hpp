#pragma once

#include "iGraph.hpp"

class ListGraph : public IGraph {
public:
    ListGraph(size_t num_vertices);
    virtual ~ListGraph() = default;
    ListGraph(const IGraph& l_graph);

    void AddEdge(size_t from, size_t to) override;
    size_t VerticesCount() const override;

    std::vector<size_t> GetNextVertices(size_t vertex) const override;
    std::vector<size_t> GetPrevVertices(size_t vertex) const override;

private:
    std::vector<std::vector<size_t>> _vertices;
};
