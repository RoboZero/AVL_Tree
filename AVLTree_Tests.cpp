//
// Created by tirio on 2/13/2022.
//


#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "AVLTree.h"
#include <random>

bool isInorder(vector<string>& ids){
    for(int i = 0; i < ids.size() - 1; i++)
    {
        if(stoi(ids[i]) >= stoi(ids[i + 1]))
        {
            return false;
            break;
        }
    }

    return true;
}

TEST_CASE( "AVL Insert - Static", "[flag]")
{
    AVLTree tree;

    //Act
    tree.insert("Brandon", "45679999");
    tree.insert("Brian", "35459999");
    tree.insert("Briana", "87879999");
    tree.insert("Bella", "95469999");

    //Assert
    vector<string> inorderNames;
    tree.getNamesInorder(inorderNames);

    vector<string> levelorderNames;
    tree.getNamesLevelorder(levelorderNames);

    vector<string> inorderExpectedNames = {"Brian", "Brandon", "Briana", "Bella"};
    vector<string> levelorderExpectedNames = {"Brandon", "Brian", "Briana", "Bella"};

    REQUIRE(inorderNames == inorderExpectedNames);
    REQUIRE(levelorderNames == levelorderExpectedNames);
}

TEST_CASE( "AVL Insert - Random", "[flag]")
{
    AVLTree tree;
    //srand(1);

    //Act
    for(int i = 0; i < 10; i++)
    {
        int randomInput = rand() % 100;

        tree.insert("Default Name", std::to_string(randomInput));
    }

    //Assert
    vector<string> inorderIds;
    tree.getIdsInorder(inorderIds);

    bool inorder = isInorder(inorderIds);
    REQUIRE(inorder);
}

TEST_CASE( "AVL Insert - Left Rotation", "[flag]")
{
    AVLTree tree;

    //Act
    tree.insert("Brandon", "45679999");
    tree.insert("Brian", "35459999");
    tree.insert("Briana", "77879999");
    tree.insert("Bella", "85469999");
    tree.insert("Bronston", "95469999");

    //Assert
    vector<string> idsInorder;
    tree.getIdsInorder(idsInorder);

    vector<string> idsLevelorder;
    tree.getIdsLevelorder(idsLevelorder);

    vector<string> expectedInorder = {"35459999", "45679999", "77879999", "85469999", "95469999"};
    vector<string> expectedLevelorder = {"45679999", "35459999", "85469999", "77879999", "95469999"};

    REQUIRE(idsInorder == expectedInorder);
    REQUIRE(idsLevelorder == expectedLevelorder);
}

TEST_CASE( "AVL Insert - Simple Left Rotation w/ New Root ", "[flag]")
{
    AVLTree tree;

    //Act
    tree.insert("Brandon", "55679999");
    tree.insert("Brian", "65459999");
    tree.insert("Briana", "77879999");
    //No hanging node/node to shift down.

    //Assert
    vector<string> idsInorder;
    tree.getIdsInorder(idsInorder);

    vector<string> idsLevelorder;
    tree.getIdsLevelorder(idsLevelorder);

    vector<string> expectedInorder = {"55679999", "65459999", "77879999"};
    vector<string> expectedLevelorder = {"65459999", "55679999", "77879999"};

    REQUIRE(idsInorder == expectedInorder);
    REQUIRE(idsLevelorder == expectedLevelorder);
}

TEST_CASE( "AVL Insert - Complex Left Rotation w/ New Root", "[flag]")
{
    AVLTree tree;

    //Act
    tree.insert("Brandon", "55679999");
    tree.insert("Brian", "75459999");
    tree.insert("Briana", "87879999");
    //Node being shifted down
    tree.insert("Bruno", "63339999");

    //Assert
    vector<string> idsInorder;
    tree.getIdsInorder(idsInorder);

    vector<string> idsLevelorder;
    tree.getIdsLevelorder(idsLevelorder);

    vector<string> expectedInorder = {"55679999", "63339999", "75459999", "87879999"};
    vector<string> expectedLevelorder = {"75459999", "55679999", "87879999", "63339999"};

    REQUIRE(idsInorder == expectedInorder);
    REQUIRE(idsLevelorder == expectedLevelorder);
}

TEST_CASE( "AVL Insert - Simple Right Rotation w/ New Root", "[flag]")
{
    AVLTree tree;

    //Act
    tree.insert("Brandon", "55679999");
    tree.insert("Brian", "35459999");
    tree.insert("Briana", "17879999");

    //Assert
    vector<string> idsInorder;
    tree.getIdsInorder(idsInorder);

    vector<string> idsLevelorder;
    tree.getIdsLevelorder(idsLevelorder);

    vector<string> expectedInorder = {"17879999", "35459999", "55679999"};
    vector<string> expectedLevelorder = {"35459999", "17879999", "55679999"};

    REQUIRE(idsInorder == expectedInorder);
    REQUIRE(idsLevelorder == expectedLevelorder);
}

TEST_CASE( "AVL Insert - Complex Right Rotation w/ New Root", "[flag]")
{
    AVLTree tree;

    //Act
    tree.insert("Brandon", "55679999");
    tree.insert("Brian", "35459999");
    tree.insert("Briana", "17879999");
    //Node being shifted down
    tree.insert("Bruno", "43339999");

    //Assert
    vector<string> idsInorder;
    tree.getIdsInorder(idsInorder);

    vector<string> idsLevelorder;
    tree.getIdsLevelorder(idsLevelorder);

    vector<string> expectedInorder = {"17879999", "35459999", "43339999", "55679999"};
    vector<string> expectedLevelorder = {"35459999", "17879999", "55679999", "43339999"};

    REQUIRE(idsInorder == expectedInorder);
    REQUIRE(idsLevelorder == expectedLevelorder);
}

TEST_CASE( "AVL Insert - Chain Left Rotations", "[flag]")
{
    AVLTree tree;

    tree.insert("Default", "45679999");
    tree.insert("Default", "65459999");
    tree.insert("Default", "57879999");
    tree.insert("Default", "73339999");
    tree.insert("Default", "83339999");
    tree.insert("Default", "93339999");

    //Assert
    vector<string> idsInorder;
    tree.getIdsInorder(idsInorder);

    vector<string> idsLevelorder;
    tree.getIdsLevelorder(idsLevelorder);

    vector<string> expectedInorder = {"45679999", "57879999", "65459999", "73339999", "83339999", "93339999"};
    vector<string> expectedLevelorder = {"73339999", "57879999", "83339999", "45679999", "65459999", "93339999"};

    REQUIRE(idsInorder == expectedInorder);
    REQUIRE(idsLevelorder == expectedLevelorder);
}

TEST_CASE( "AVL Insert - Chain Right Rotations", "[flag]")
{
    AVLTree tree;

    tree.insert("Default", "95679999");
    tree.insert("Default", "85459999");
    tree.insert("Default", "67879999");
    tree.insert("Default", "73339999");
    tree.insert("Default", "33339999");
    tree.insert("Default", "13339999");

    //Assert
    vector<string> idsInorder;
    tree.getIdsInorder(idsInorder);

    vector<string> idsLevelorder;
    tree.getIdsLevelorder(idsLevelorder);

    vector<string> expectedInorder = {"13339999", "33339999", "67879999", "73339999", "85459999", "95679999"};
    vector<string> expectedLevelorder = {"67879999", "33339999", "85459999", "13339999", "73339999", "95679999"};

    REQUIRE(idsInorder == expectedInorder);
    REQUIRE(idsLevelorder == expectedLevelorder);
}

TEST_CASE( "AVL Insert - Simple Left Right Rotation w/ New Root", "[flag]")
{
    AVLTree tree;

    //Act
    tree.insert("Brandon", "55679999");
    tree.insert("Brian", "35459999");
    //Node being shifted down
    tree.insert("Bruno", "43339999");

    //Assert
    vector<string> idsInorder;
    tree.getIdsInorder(idsInorder);

    vector<string> idsLevelorder;
    tree.getIdsLevelorder(idsLevelorder);

    vector<string> expectedInorder = {"35459999", "43339999", "55679999"};
    vector<string> expectedLevelorder = {"43339999", "35459999", "55679999"};

    REQUIRE(idsInorder == expectedInorder);
    REQUIRE(idsLevelorder == expectedLevelorder);
}

TEST_CASE( "AVL Insert - Simple Right Left Rotation w/ New Root", "[flag]")
{
    AVLTree tree;

    //Act
    tree.insert("Brandon", "55679999");
    tree.insert("Brian", "75459999");
    //Node being shifted down
    tree.insert("Bruno", "63339999");

    //Assert
    vector<string> idsInorder;
    tree.getIdsInorder(idsInorder);

    vector<string> idsLevelorder;
    tree.getIdsLevelorder(idsLevelorder);

    vector<string> expectedInorder = {"55679999", "63339999", "75459999"};
    vector<string> expectedLevelorder = {"63339999", "55679999", "75459999"};

    REQUIRE(idsInorder == expectedInorder);
    REQUIRE(idsLevelorder == expectedLevelorder);
}

TEST_CASE("AVL Insert - Large tree", "[flag]")
{
    AVLTree tree;

    //Act
    tree.insert("Brian", "45679999");
    tree.insert("Brian", "35459999");
    tree.insert("Briana", "77879999");
    tree.insert("Bella", "85469999");
    tree.insert("Bronston", "95469999");
    tree.insert("Alpha", "95329999");
    tree.insert("Charlie", "32329999");
    tree.insert("Brian", "36323199");
    tree.insert("Brian", "09332319");

    //Assert
    vector<string> idsInorder;
    tree.getIdsInorder(idsInorder);

    vector<string> idsLevelorder;
    tree.getIdsLevelorder(idsLevelorder);

    vector<string> expectedInorder = {"09332319", "32329999", "35459999", "36323199", "45679999", "77879999", "85469999", "95329999", "95469999"};
    vector<string> expectedLevelorder = {"85469999", "35459999", "95469999", "32329999", "45679999", "95329999", "09332319", "36323199", "77879999"};

    REQUIRE(idsInorder == expectedInorder);
    REQUIRE(idsLevelorder == expectedLevelorder);
}

TEST_CASE("AVL GetName / SearchId - Get from large tree", "[flag]")
{
    AVLTree tree;

    //Act
    tree.insert("Brandon", "45679999");
    tree.insert("Brian", "35459999");
    tree.insert("Briana", "77879999");
    tree.insert("Bella", "85469999");
    tree.insert("Bronston", "95469999");
    tree.insert("Alpha", "95329999");
    tree.insert("Charlie", "32329999");
    tree.insert("Tango", "3632319");
    tree.insert("Frita", "09332319");

    //Get name uses same system as searchId
    string name1 = tree.getName("95329999");
    string name2 = tree.getName("32329999");
    string name3 = tree.getName("00000000");
    string name4 = tree.getName("45679999");

    //Assert
    REQUIRE(name1 == "Alpha");
    REQUIRE(name2 == "Charlie");
    REQUIRE(name3 == "");
    REQUIRE(name4 == "Brandon");
}

TEST_CASE("AVL GetIds / SearchName - Get from large tree", "[flag]")
{
    AVLTree tree;

    //Act
    tree.insert("Brian", "45679999");
    tree.insert("Brian", "35459999");
    tree.insert("Briana", "77879999");
    tree.insert("Bella", "85469999");
    tree.insert("Bronston", "95469999");
    tree.insert("Alpha", "95329999");
    tree.insert("Charlie", "32329999");
    tree.insert("Brian", "36323199");
    tree.insert("Brian", "09332319");

    //Get name uses same system as searchId
    vector<string> ids = tree.getIds("Brian");
    vector<string> expected = {"35459999", "09332319", "45679999", "36323199"};

    //Assert
    REQUIRE(ids == expected);
}


TEST_CASE("AVL Remove - Double children", "[flag]")
{
    AVLTree tree;

    //Act
    tree.insert("Bario", "50109922");
    tree.insert("Brian", "39876126");
    tree.insert("Briana", "80991111");
    tree.insert("Bella", "21908756");
    tree.insert("Bronston", "45632189");
    tree.insert("Alpha", "90000001");
    tree.insert("Charlie", "42011099");

    tree.remove("39876126");

    //Assert
    vector<string> ids;
    tree.getIdsInorder(ids);

    vector<string> idsLevelorder;
    tree.getIdsLevelorder(idsLevelorder);

    vector<string> expectedLevelorder = {"50109922", "42011099", "80991111", "21908756","45632189", "90000001" };

    bool inorder = isInorder(ids);
    REQUIRE(inorder);
    REQUIRE(idsLevelorder == expectedLevelorder);
}


TEST_CASE("AVL Remove - One child", "[flag]")
{
    AVLTree tree;

    //Act
    tree.insert("Bario", "50109922");
    tree.insert("Brian", "39876126");
    tree.insert("Briana", "80991111");
    tree.insert("Bella", "21908756");
    tree.insert("Bronston", "45632189");
    tree.insert("Alpha", "90000001");
    tree.insert("Charlie", "42011099");

    tree.remove("90000001");

    //Assert
    vector<string> ids;
    tree.getIdsInorder(ids);

    vector<string> idsLevelorder;
    tree.getIdsLevelorder(idsLevelorder);

    vector<string> expectedLevelorder = {"50109922", "39876126", "80991111", "21908756","45632189", "42011099"};

    bool inorder = isInorder(ids);
    REQUIRE(inorder);
    REQUIRE(idsLevelorder == expectedLevelorder);
}

TEST_CASE("AVL Level count", "[flag]")
{
    AVLTree tree;

    tree.insert("Bario", "50109922");
    tree.insert("Brian", "39876126");
    tree.insert("Briana", "80991111");
    tree.insert("Bella", "21908756");
    tree.insert("Bronston", "45632189");
    tree.insert("Alpha", "90000001");
    tree.insert("Charlie", "42011099");

    REQUIRE(tree.getLevelCount() == 4);
}

TEST_CASE("AVL Remove Inorder - ", "[flag]")
{
    AVLTree tree;

    //Act
    tree.insert("Bario", "50109922");
    tree.insert("Brian", "39876126");
    tree.insert("Briana", "80991111");
    tree.insert("Bella", "21908756");
    tree.insert("Bronston", "45632189");
    tree.insert("Alpha", "90000001");
    tree.insert("Charlie", "42011099");

    tree.removeInorder(2);

    //Assert
    vector<string> ids;
    tree.getIdsInorder(ids);

    vector<string> idsLevelorder;
    tree.getIdsLevelorder(idsLevelorder);

    vector<string> expectedLevelorder = {"50109922", "39876126", "80991111", "21908756", "42011099", "90000001"};

    bool inorder = isInorder(ids);
    REQUIRE(inorder);
    REQUIRE(idsLevelorder == expectedLevelorder);
}


TEST_CASE( "AVL Trials - Sample Input/Output", "[flag]")
{
    AVLTree tree;

    //Act
    tree.insert("Brandon", "45679999");
    tree.insert("Brian", "35459999");
    tree.insert("Briana", "87879999");
    tree.insert("Bella", "95469999");

    tree.remove("45679999");
    tree.removeInorder(2);

    //Assert
    vector<string> namesInorder;
    tree.getNamesInorder(namesInorder);

    vector<string> inorderExpectedNames = {"Brian", "Briana" };
    REQUIRE(namesInorder == inorderExpectedNames);
}

TEST_CASE( "AVL Trials - Lots of random inserts", "[flag]")
{
    AVLTree tree;
    //srand(1);

    //Act
    for(int i = 0; i < 100000; i++)
    {
    int randomInput = rand() % 10000000;

    tree.insert("Default Name", std::to_string(randomInput));
    }

    //Assert
    vector<string> inorderIds;
    tree.getIdsInorder(inorderIds);

    bool inorder = isInorder(inorderIds);
    REQUIRE(inorder);
}