#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H
#include <vector>
struct FloydWarshallResult
{
    std::vector<std::vector<long long>> distance;
    bool negativeCycle;
};
FloydWarshallResult floydWarshall(const std::vector<std::vector<long long>>& matrix);

#endif