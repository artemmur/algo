#include <memory>

#include <gtest/gtest.h>

#include "arcGraph.hpp"
#include "listGraph.hpp"
#include "matrixGraph.hpp"
#include "setGraph.hpp"

bool test(const IGraph& l_graph) {
    if (l_graph.VerticesCount() != 5) {
        return false;
    }

    {
        std::vector<size_t> nextVert = l_graph.GetNextVertices(0);
        if (nextVert.size() != 1 || nextVert[0] != 2) {
            return false;
        }

        std::vector<size_t> preVert = l_graph.GetPrevVertices(0);
        if (preVert.size() != 1 || preVert[0] != 1) {
            return false;
        }
    }

    {
        std::vector<size_t> nextVert = l_graph.GetNextVertices(1);
        if (nextVert.size() != 1 || nextVert[0] != 0) {
            return false;
        }

        std::vector<size_t> preVert = l_graph.GetPrevVertices(1);
        if (preVert.size() != 0) {
            return false;
        }
    }

    {
        std::vector<size_t> nextVert = l_graph.GetNextVertices(2);
        if (nextVert.size() != 1 || nextVert[0] != 3) {
            return false;
        }

        std::vector<size_t> preVert = l_graph.GetPrevVertices(2);
        std::sort(preVert.begin(), preVert.end());
        if (preVert.size() != 2 || preVert[0] != 0 || preVert[1] != 4) {
            return false;
        }
    }

    {
        std::vector<size_t> nextVert = l_graph.GetNextVertices(3);
        if (nextVert.size() != 1 || nextVert[0] != 4) {
            return false;
        }

        std::vector<size_t> preVert = l_graph.GetPrevVertices(3);
        std::sort(preVert.begin(), preVert.end());
        if (preVert.size() != 2 || preVert[0] != 2 || preVert[1] != 4) {
            return false;
        }
    }

    {
        std::vector<size_t> nextVert = l_graph.GetNextVertices(4);
        std::sort(nextVert.begin(), nextVert.end());
        if (nextVert.size() != 2 || nextVert[0] != 2 || nextVert[1] != 3) {
            return false;
        }

        std::vector<size_t> preVert = l_graph.GetPrevVertices(4);
        if (preVert.size() != 1 || preVert[0] != 3) {
            return false;
        }
    }

    return true;
}

TEST(graph, all) {
    std::unique_ptr<IGraph> graph = std::make_unique<ListGraph>(5);
    graph->AddEdge(1, 0);
    graph->AddEdge(0, 2);
    graph->AddEdge(2, 3);
    graph->AddEdge(3, 4);
    graph->AddEdge(4, 3);
    graph->AddEdge(4, 2);

    EXPECT_EQ(test(*graph), true);

    {
        std::unique_ptr<IGraph> matrix = std::make_unique<MatrixGraph>(*graph);
        EXPECT_EQ(test(*matrix), true);
    }

    {
        std::unique_ptr<IGraph> set = std::make_unique<SetGraph>(*graph);
        EXPECT_EQ(test(*set), true);
    }

    {
        std::unique_ptr<IGraph> arc = std::make_unique<ArcGraph>(*graph);
        EXPECT_EQ(test(*arc), true);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
