#include "floyd_warshall.h"

#include <algorithm>
#include <limits>

FloydWarshallResult floydWarshall(
    const std::vector<std::vector<long long>>& matrix)
{
    const long long INF = std::numeric_limits<long long>::max() / 4;

    int vertices = static_cast<int>(matrix.size());

    std::vector<std::vector<long long>> distance = matrix;

    for (int k = 0; k < vertices; k++)
    {
        for (int i = 0; i < vertices; i++)
        {
            if (distance[i][k] == INF)
                continue;

            for (int j = 0; j < vertices; j++)
            {
                if (distance[k][j] == INF)
                    continue;

                long long newDistance =
                    distance[i][k] + distance[k][j];

                if (newDistance < distance[i][j])
                {
                    distance[i][j] = newDistance;
                }
            }
        }
    }

    bool negativeCycle = false;

    for (int i = 0; i < vertices; i++)
    {
        if (distance[i][i] < 0)
        {
            negativeCycle = true;
            break;
        }
    }

    return {distance, negativeCycle};
}