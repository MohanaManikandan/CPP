#include <gtest/gtest.h>
#include "../src/GameOfLife.h"

TEST(TestInitializeLiveMatrix, ZeroLiveCells)
{
    GameOfLife oGameObject;

    oGameObject.InitializeLiveMatrix(std::vector<std::pair<int, int>>());

    const auto& vecLiveMatrix = oGameObject.GetLiveMatrix();

    ASSERT_EQ(vecLiveMatrix.size(), 0);
}

TEST(TestInitializeLiveMatrix, OneLiveCell)
{
    GameOfLife oGameObject;

    oGameObject.InitializeLiveMatrix(std::vector<std::pair<int, int>>{std::make_pair(1,1)});

    const auto& vecLiveMatrix = oGameObject.GetLiveMatrix();

    ASSERT_EQ(vecLiveMatrix.size(), 2);
    ASSERT_EQ(vecLiveMatrix, std::vector<std::vector<bool>>({{false, false},{false, true}}));
}

TEST(TestInitializeLiveMatrix, MultipleLiveCells)
{
    GameOfLife oGameObject;

    oGameObject.InitializeLiveMatrix(std::vector<std::pair<int, int>>{std::make_pair(1,1), std::make_pair(0,0), std::make_pair(2,2)});

    const auto& vecLiveMatrix = oGameObject.GetLiveMatrix();

    ASSERT_EQ(vecLiveMatrix.size(), 3);
    ASSERT_EQ(vecLiveMatrix, std::vector<std::vector<bool>>({{true, false, false}, {false, true, false}, {false, false, true}}));
}

TEST(TestRunTick, ZeroCellsAlive)
{
    GameOfLife oGameObject;

    oGameObject.InitializeLiveMatrix(std::vector<std::pair<int, int>>());

    oGameObject.RunTick();

    const auto& vecLiveMatrix = oGameObject.GetLiveMatrix();

    ASSERT_EQ(vecLiveMatrix.size(), 0);
}

TEST(TestRunTick, OneLiveCell)
{
    GameOfLife oGameObject;

    oGameObject.InitializeLiveMatrix(std::vector<std::pair<int, int>>{std::make_pair(1,1)});

    oGameObject.RunTick();

    const auto& vecLiveMatrix = oGameObject.GetLiveMatrix();

    ASSERT_EQ(vecLiveMatrix.size(), 2);
    ASSERT_EQ(vecLiveMatrix, std::vector<std::vector<bool>>({{false, false},{false, false}}));
}

class TestRunTickBlockPattern : public ::testing::Test
{
    public:
    GameOfLife m_oGameObject;
    protected:
    void SetUp() override
    {
        m_oGameObject.InitializeLiveMatrix(std::vector<std::pair<int, int>>{std::make_pair(0,1), std::make_pair(1,1), std::make_pair(0, 2), std::make_pair(1,2)});
    }
};

TEST_F(TestRunTickBlockPattern, OneTick)
{
    m_oGameObject.RunTick();

    const auto& vecLiveMatrix = m_oGameObject.GetLiveMatrix();

    ASSERT_EQ(vecLiveMatrix.size(), 3);
    ASSERT_EQ(vecLiveMatrix, std::vector<std::vector<bool>>({{false, true, true},{false, true, true}, {false, false, false}}));
}

TEST_F(TestRunTickBlockPattern, TwoTicks)
{
    m_oGameObject.RunTick();
    m_oGameObject.RunTick();

    const auto& vecLiveMatrix = m_oGameObject.GetLiveMatrix();

    ASSERT_EQ(vecLiveMatrix.size(), 3);
    ASSERT_EQ(vecLiveMatrix, std::vector<std::vector<bool>>({{false, true, true},{false, true, true}, {false, false, false}}));
}

TEST_F(TestRunTickBlockPattern, ThreeTicks)
{
    m_oGameObject.RunTick();
    m_oGameObject.RunTick();
    m_oGameObject.RunTick();

    const auto& vecLiveMatrix = m_oGameObject.GetLiveMatrix();

    ASSERT_EQ(vecLiveMatrix.size(), 3);
    ASSERT_EQ(vecLiveMatrix, std::vector<std::vector<bool>>({{false, true, true},{false, true, true}, {false, false, false}}));
}

class TestRunTickBoatPattern : public ::testing::Test
{
    public:
    GameOfLife m_oGameObject;
    protected:
    void SetUp() override
    {
        m_oGameObject.InitializeLiveMatrix(std::vector<std::pair<int, int>>{std::make_pair(0,1), 
                                                                            std::make_pair(1,0),
                                                                            std::make_pair(2,1), 
                                                                            std::make_pair(0,2),
                                                                            std::make_pair(1,2)});
    }
};

TEST_F(TestRunTickBoatPattern, OneTick)
{
    m_oGameObject.RunTick();

    const auto& vecLiveMatrix = m_oGameObject.GetLiveMatrix();

    ASSERT_EQ(vecLiveMatrix.size(), 3);
    ASSERT_EQ(vecLiveMatrix, std::vector<std::vector<bool>>({{false, true, true},{true, false, true}, {false, true, false}}));
}

TEST_F(TestRunTickBoatPattern, TwoTicks)
{
    m_oGameObject.RunTick();
    m_oGameObject.RunTick();

    const auto& vecLiveMatrix = m_oGameObject.GetLiveMatrix();

    ASSERT_EQ(vecLiveMatrix.size(), 3);
    ASSERT_EQ(vecLiveMatrix, std::vector<std::vector<bool>>({{false, true, true},{true, false, true}, {false, true, false}}));
}

TEST_F(TestRunTickBoatPattern, ThreeTicks)
{
    m_oGameObject.RunTick();
    m_oGameObject.RunTick();
    m_oGameObject.RunTick();

    const auto& vecLiveMatrix = m_oGameObject.GetLiveMatrix();

    ASSERT_EQ(vecLiveMatrix.size(), 3);
    ASSERT_EQ(vecLiveMatrix, std::vector<std::vector<bool>>({{false, true, true},{true, false, true}, {false, true, false}}));
}

class TestRunTickBlinkerPattern : public ::testing::Test
{
    public:
    GameOfLife m_oGameObject;
    protected:
    void SetUp() override
    {
        m_oGameObject.InitializeLiveMatrix(std::vector<std::pair<int, int>>{std::make_pair(1,1), 
                                                                            std::make_pair(1,0),
                                                                            std::make_pair(1,2)});
    }
};

TEST_F(TestRunTickBlinkerPattern, OneTick)
{
    m_oGameObject.RunTick();

    const auto& vecLiveMatrix = m_oGameObject.GetLiveMatrix();

    ASSERT_EQ(vecLiveMatrix.size(), 3);
    ASSERT_EQ(vecLiveMatrix, std::vector<std::vector<bool>>({{false, true, false},{false, true, false}, {false, true, false}}));
}

TEST_F(TestRunTickBlinkerPattern, TwoTicks)
{
    m_oGameObject.RunTick();
    m_oGameObject.RunTick();

    const auto& vecLiveMatrix = m_oGameObject.GetLiveMatrix();

    ASSERT_EQ(vecLiveMatrix.size(), 3);
    ASSERT_EQ(vecLiveMatrix, std::vector<std::vector<bool>>({{false, false, false},{true, true, true}, {false, false, false}}));
}

TEST_F(TestRunTickBlinkerPattern, ThreeTicks)
{
    m_oGameObject.RunTick();
    m_oGameObject.RunTick();
    m_oGameObject.RunTick();

    const auto& vecLiveMatrix = m_oGameObject.GetLiveMatrix();

    ASSERT_EQ(vecLiveMatrix.size(), 3);
    ASSERT_EQ(vecLiveMatrix, std::vector<std::vector<bool>>({{false, true, false},{false, true, false}, {false, true, false}}));
}

class TestRunTickToadPattern : public ::testing::Test
{
    public:
    GameOfLife m_oGameObject;
    protected:
    void SetUp() override
    {
        m_oGameObject.InitializeLiveMatrix(std::vector<std::pair<int, int>>{std::make_pair(1,1), 
                                                                            std::make_pair(1,2),
                                                                            std::make_pair(1,3),
                                                                            std::make_pair(2,2),
                                                                            std::make_pair(2,3),
                                                                            std::make_pair(2,4)});
    }
};

TEST_F(TestRunTickToadPattern, OneTick)
{
    m_oGameObject.RunTick();

    const auto& vecLiveMatrix = m_oGameObject.GetLiveMatrix();

    ASSERT_EQ(vecLiveMatrix.size(), 5);
    ASSERT_EQ(vecLiveMatrix, std::vector<std::vector<bool>>({{false, false, true,  false, false},
                                                             {false, true,  false, false, true }, 
                                                             {false, true,  false, false, true },
                                                             {false, false, false, true,  false},
                                                             {false, false, false, false, false}}));
}

TEST_F(TestRunTickToadPattern, TwoTicks)
{
    m_oGameObject.RunTick();
    m_oGameObject.RunTick();

    const auto& vecLiveMatrix = m_oGameObject.GetLiveMatrix();

    ASSERT_EQ(vecLiveMatrix.size(), 5);
    ASSERT_EQ(vecLiveMatrix, std::vector<std::vector<bool>>({{false, false, false, false, false},
                                                             {false, true,  true,  true,  false}, 
                                                             {false, false, true,  true,  true },
                                                             {false, false, false, false,  false},
                                                             {false, false, false, false, false}}));
}

TEST_F(TestRunTickToadPattern, ThreeTicks)
{
    m_oGameObject.RunTick();
    m_oGameObject.RunTick();
    m_oGameObject.RunTick();

    const auto& vecLiveMatrix = m_oGameObject.GetLiveMatrix();

    ASSERT_EQ(vecLiveMatrix.size(), 5);
    ASSERT_EQ(vecLiveMatrix, std::vector<std::vector<bool>>({{false, false, true,  false, false},
                                                             {false, true,  false, false, true }, 
                                                             {false, true,  false, false, true },
                                                             {false, false, false, true,  false},
                                                             {false, false, false, false, false}}));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
