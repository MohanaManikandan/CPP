#include "GameOfLife.cpp"

// Using c++14
// Parses comma separated input from the user and fills the pairs into a vector
bool InputParser(std::vector<std::pair<int, int>> &vecLiveCells)
{
    std::string input_str;
    while(true)
    {
        int nCoordinateX = 0;
        int nCoordinateY = 0;
        std::getline(std::cin, input_str);
        if(input_str.empty())
        {
            break;
        }
        try
        {
            std::stringstream ss(input_str);

            if(ss >> nCoordinateX)
            {
                if(ss.peek() == ',')
                    ss.ignore();
                else
                    return false;

                ss >> nCoordinateY;
            }
        }
        catch(...)
        {
            return false;
        }
        vecLiveCells.push_back(std::make_pair(nCoordinateX, nCoordinateY));
        input_str.clear();
    }
    return true;
}

int main()
{
    std::vector<std::pair<int, int>> vecLiveCellsInput;

    if(InputParser(vecLiveCellsInput) == false)
    {
        std::cout << "Wrong Input Format...\nInput Format : X, Y in multiple lines\n";
    }

    GameOfLife aGameObject(vecLiveCellsInput);
    aGameObject.RunTick();
    aGameObject.PrintLiveCells();

    return 0;
}
