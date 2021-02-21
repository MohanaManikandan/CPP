#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <utility> 

// Using C++14

#include "GameOfLife.h"

// Parameterized Contructor
// Input : Living Cell Coordinates as a vector of pairs
GameOfLife::GameOfLife(const std::vector<std::pair<int, int>>& vecLiveCells)
{
    InitializeLiveMatrix(vecLiveCells);
}

// Initializes the Live Matrix
// Input : Living Cell Coordinates as a vector of pairs
void GameOfLife::InitializeLiveMatrix(const std::vector<std::pair<int, int>>& vecLiveCells)
{
    if(vecLiveCells.size() == 0)
    {
        return;
    }

    for(const auto &x: vecLiveCells)
    {
        m_nMatrixSize = std::max({m_nMatrixSize, x.first, x.second});
    }

    m_nMatrixSize += 1;

    for(size_t nIndex = 0; nIndex < m_nMatrixSize; ++nIndex)
    {
        m_VecLiveMatrix.push_back(std::vector<bool>(m_nMatrixSize, false));
    }

    for(const auto &x : vecLiveCells)
    {
        m_VecLiveMatrix[x.first][x.second] = true;
    }
}

// Runs One Run Of The Game With All The Rules
void GameOfLife::RunTick()
{
    std::vector<std::vector<bool>> vecNextRoundLiveMatrix;

    for(int nIndex = 0; nIndex < m_nMatrixSize; ++nIndex)
    {
        vecNextRoundLiveMatrix.push_back(std::vector<bool>(m_nMatrixSize, false));
    }

    short nNeighbourCount = 0;
    for(size_t nRowIndex = 0; nRowIndex < m_nMatrixSize; ++nRowIndex)
    {
        for(size_t nColumnIndex = 0; nColumnIndex < m_nMatrixSize; ++nColumnIndex)
        {
            nNeighbourCount = 0;
            for(size_t nAdjacentIndex = 0; nAdjacentIndex < 8; ++nAdjacentIndex)
            {
                int xCoordinate = nRowIndex + m_stDirections[nAdjacentIndex].dx;
                int yCoordinate = nColumnIndex + m_stDirections[nAdjacentIndex].dy;

                if((xCoordinate >= 0 && xCoordinate < m_nMatrixSize) && (yCoordinate >= 0 && yCoordinate <= m_nMatrixSize))
                {
                    nNeighbourCount += m_VecLiveMatrix[xCoordinate][yCoordinate] ? 1 : 0;
                }
            }
            
            if(m_VecLiveMatrix[nRowIndex][nColumnIndex])
            {
                if(nNeighbourCount == 2 || nNeighbourCount == 3)
                {
                    vecNextRoundLiveMatrix[nRowIndex][nColumnIndex] = true;
                }
            }
            else
            {
                if(nNeighbourCount == 3)
                {
                    vecNextRoundLiveMatrix[nRowIndex][nColumnIndex] = true;
                }
            }
        }
    }

    m_VecLiveMatrix = vecNextRoundLiveMatrix;
}

// Utility Function To Print The Live Cell Coordinates In (X, Y) Format
void GameOfLife::PrintLiveCells()
{
    for(size_t nRowIndex = 0; nRowIndex < m_VecLiveMatrix.size(); ++nRowIndex)
    {
        for(size_t nColumnIndex = 0; nColumnIndex < m_VecLiveMatrix.size(); ++nColumnIndex)
        {
            if(m_VecLiveMatrix[nRowIndex][nColumnIndex] == true)
            {
                std::cout << nRowIndex << ", " << nColumnIndex << "\n";
            }
        }
    }
}
