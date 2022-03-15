//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Marek Spirka <xspirk01@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Marek Spirka
 *
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>
#include "gtest/gtest.h"
#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

using namespace std;
const static int MIN = -100;
const static int MAX = 100;

class EmptyTree : public  ::testing::Test{
    protected:
     BinaryTree tree;
};

//vytvorenie stromu a pridanie hodnot dongo
class NonEmptyTree : public ::testing::Test{
protected:
    const static int lenght_tree = 10;
    int values[lenght_tree] = {-20, -10, -8, 5, 10, 18, 27, 45, 60, 90 };
    virtual void SetUp(){
        for(auto value : values)
            tree.InsertNode(value);
    }
    BinaryTree tree;
};

//vytvorenie axiomov a pridanie hodnot do nich
class TreeAxioms: public ::testing::Test{
protected:
    BinaryTree tree;
    virtual void SetUp(){
        int values_axioms[] = {2,4,5,6};

        for (int i = 0; i <= 4 ; ++i) {
            tree.InsertNode(values_axioms[i]);
        }
    }
};

//-----------------------------------------------TESTS EMPTY TREE------------------------------------------------------//

//V teste hladame uzly v prazdnom strome -> ocakavame prazdny strom
TEST_F(EmptyTree, FindNode){
    for(int i = MIN; i <= MAX; i++){
        EXPECT_TRUE(tree.FindNode(i) == NULL);
    }
}

//V teste sa snazime odstranit uzol z prazdneho stromu -> ocakavame chybu
TEST_F(EmptyTree, DeleteNode){
    for(int i = MIN; i <= MAX; i++){
        EXPECT_FALSE(tree.DeleteNode(i));
    }
}
//V teste skusame vkladat do prazdneho stromu nove hodnoty
TEST_F(EmptyTree, InsertNode){
    vector<int> values = {5,10,50,100,500};
    pair<bool, BinaryTree::Node_t *> temp;

    for(auto value : values){
        EXPECT_NO_THROW(temp = tree.InsertNode(value));
        ASSERT_TRUE(temp.first);
        ASSERT_FALSE(temp.second == NULL);
    }
    EXPECT_FALSE(tree.GetRoot() == NULL);
}

//---------------------------------------------TESTS NONEMPTY TREE-----------------------------------------------------//

//Pridanie uzlov do neprazdneho stromu, pridame hodnoty, ktore sa tam uz nachadzaju -> ocakavame chybu
TEST_F(NonEmptyTree, InsertNode){
    pair<bool, BinaryTree::Node_t *> temp;
    int index = 0;
        for(int i = MIN; i <= MAX; i++){
            EXPECT_NO_THROW(temp = tree.InsertNode(i));
            ASSERT_TRUE(temp.second != NULL);

        if(index < lenght_tree){
            if (i != values[index]){
                EXPECT_TRUE(temp.second);
            }
            else{
                EXPECT_FALSE(temp.first);
                index++;
            }
        }
        else{
            EXPECT_TRUE(temp.first);
        }
    }
}

//V teste sa testuje vymazavanie uzlov, ak sa uzol nachadza a da sa zmazat -> true, ak sa uzol nenechadza v strome neda sa vymazat -> false
TEST_F(NonEmptyTree, DeleteNode){
    int random_nonimported_values[] = {-50,-40, 9, 200, 300};
    int imported_values[] = { -20, -10, -8, 5, 10, 18, 27, 45, 60, 90};

    for (auto value : random_nonimported_values){
        EXPECT_FALSE(tree.DeleteNode(value));
    }
    for (auto value : imported_values){
        EXPECT_TRUE(tree.DeleteNode(value));
    }
}
//V teste sa testuje vyhladavanie uzlov, ak sa uzol nachadza -> true, ak nie -> false
TEST_F(NonEmptyTree, FindNode){
    int index = 0;

    for(int i = MIN; i <= MAX; i++){
        //vyhladavame dokym nedojdem na koniec stromu
        if(index < lenght_tree){
            if(i != values[index]){
                ASSERT_FALSE(tree.FindNode(i));
            }
            else{
                ASSERT_TRUE(tree.FindNode(i));
                index++;
            }
        }else
            ASSERT_FALSE(tree.FindNode(i));
        }
    }
// V teste sa vymaze cely strom a nasledne skontrolujeme ci su v strome nejake hodnoty, ak nie -> true, nasledne skontrolujeme
// ci sa nachadza v strome root, ak nie -> true
TEST_F(NonEmptyTree, DeleteNodeAll){
        for (int i = 0; i < lenght_tree; i++){
            EXPECT_TRUE(tree.DeleteNode(values[i]));
        }
        for (int i = 0; i < lenght_tree ; i++){
            EXPECT_TRUE(tree.FindNode(values[i]) == NULL);
        }
        EXPECT_TRUE(tree.GetRoot() == NULL);
}

TEST_F(NonEmptyTree, Axiom1){
    vector<BinaryTree::Node_t *> outLeafNodes;
    EXPECT_NO_THROW(tree.GetLeafNodes(outLeafNodes));

    //ak je prvok cierny, ocakavame, ze za nim uz nic nepojde
    for (const Node_t *leaf : outLeafNodes){
        EXPECT_EQ(leaf->color, Color_t::BLACK);
        ASSERT_FALSE(leaf->pRight != NULL);
        ASSERT_FALSE(leaf->pLeft != NULL);
    }
}
//V teste kontrolujeme, ze ak je uzol cerveny jeho potomkovia musia byt cierny
TEST_F(NonEmptyTree, Axiom2){

    //vyhladame si v strome najprv vsetky nelistove prvky a potom vsetky prvky v strome
    vector<BinaryTree::Node_t *> NonLeafNodesTree1{};
    vector<BinaryTree::Node_t *> AllNodesTree1{};
    tree.GetNonLeafNodes(NonLeafNodesTree1);
    tree.GetAllNodes(AllNodesTree1);

    //vyhladavame v strome prvky, ktore nie su koncove(listove), ak sme nasli cerveny prvok, vpravo aj v lavo musia byt cierne prvky
    for (auto node : NonLeafNodesTree1){
        if(node->color == RED){
            if(node->pLeft != NULL){
                EXPECT_EQ(node->pLeft->color, BLACK);
            }
            if(node->pRight != NULL){
                EXPECT_EQ(node->pLeft->color, BLACK);
            }
        }
    }
    //to iste skontrolujeme aj pre vsetky prvky v strome, ktore nemusia byt koncove
    for(auto node : AllNodesTree1){
        if(node->color == RED){
            if(node->pLeft != NULL){
                EXPECT_EQ(node->pLeft->color, BLACK);
            }
            if(node->pRight != NULL){
                EXPECT_EQ(node->pLeft->color, BLACK);
            }
        }
    }
}

TEST_F(TreeAxioms, Axiom3){
    vector<BinaryTree::Node_t *> outLeafNodes;
    int black_nodes = 0;

    for(Node_t *leaf : outLeafNodes){
            //ocakavme, ze ak je prvok cierny, za danym prvkom sa uz nic nenachadza ani na jednej strane
            EXPECT_EQ(leaf->color, Color_t::BLACK);
            ASSERT_TRUE(leaf->pRight == NULL);
            ASSERT_TRUE(leaf->pLeft == NULL);

            //kontrolujeme, ze od koncoveho prvku (listoveho) ma byt rovnaky pocet ciernych prvkov
        if (black_nodes != 0){
        //cez cyklus sa dostavame ku kuronu stromu a pocitama cierne prvky
                for(Node_t *temp = leaf; temp != NULL; temp = temp->pParent){
                    if(temp->color == Color_t:: BLACK ){
                        black_nodes++;
                    }
                }
            }
        //kontrolujeme ostatne uzly, ci maju tiez rovnaky pocet ciernych prvkov ku korenu
        else {
            int count_black_nodes = 0;
            //cez cyklus sa dostavame ku kuronu stromu a pocitama cierne prvky
            for(Node_t *temp = leaf; temp != NULL; temp = temp->pParent){
                if(temp->color == Color_t:: BLACK ){
                    count_black_nodes++;
                }
            }
        }
    }
}
/*** Konec souboru black_box_tests.cpp ***/
