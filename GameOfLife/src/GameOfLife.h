#pragma once

// Using C++14
#include <initializer_list>
#include <vector>

class GameOfLife
{
    std::vector<std::vector<bool>> m_VecLiveMatrix;

    int m_nMatrixSize = 0;

public:
    GameOfLife() = default;
    
    GameOfLife(const std::vector<std::pair<int, int>>& vecLiveCells);
   
    void InitializeLiveMatrix(const std::vector<std::pair<int, int>>& vecLiveCells);

    void RunTick();

    void PrintLiveCells();

    const auto& GetLiveMatrix()
    {
        return m_VecLiveMatrix;
    }

private:
    // We will use this for finding Neighbours of the current cell
    typedef struct {
        int dx;
        int dy;
    } Directions;
    
    std::vector<Directions> m_stDirections{{-1,-1,},{-1,0,},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
};
