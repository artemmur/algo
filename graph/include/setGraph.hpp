#pragma once

#include <set>

#include "iGraph.hpp"

class SetGraph : public IGraph {
public:
    SetGraph(size_t l_verticesNum);
    virtual ~SetGraph() = default;
    SetGraph(const IGraph& l_graph);

    void AddEdge(size_t l_from, size_t l_to) override;
    size_t VerticesCount() const override;

    std::vector<size_t> GetNextVertices(size_t l_vertex) const override;
    std::vector<size_t> GetPrevVertices(size_t l_vertex) const override;

private:
    std::vector<std::set<size_t>> _vertices;
};
