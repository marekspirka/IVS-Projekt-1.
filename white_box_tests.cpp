//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Marek Spirka <xspirk01@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Marek Spirka
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"
using namespace std;

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//


class Empty_Matrix : public ::testing::Test{
protected:
    Matrix matrix_m;
};

class No_Empty_Matrix : public ::testing::Test{
    //zadefinovanie matic
    protected:
        Matrix m1x1 = Matrix();
        Matrix m2x2 = Matrix(2,2);
        Matrix m3x3 = Matrix(3,3);
        Matrix m3x2 = Matrix(3,2);
        Matrix m4x2 = Matrix(4,2);
        Matrix m5x5 = Matrix(5,5);

    //vytvorenie matic s hodnotami
        virtual void SetUp(){
            m2x2.set(vector<vector<double>>
            {
                    {4,8},
                    {5,2}
            });

            m3x3.set(vector<vector<double>>
            {
                {1,2,6},
                {7,9,2},
                {7,3,5}
            });
            m3x2.set(vector<vector<double>>
        {
                {7,6},
                {9,5},
                {1,6}
        });

            m4x2.set(vector<vector<double>>
        {
                {1,6},
                {7,9},
                {5,2},
                {6,9}
        });
            m5x5.set(vector<vector<double>>
        {
            {7,6,3,2,1},
            {9,5,6,1,2},
            {1,6,7,8,9},
            {2,4,7,4,9},
            {5,6,2,6,1},
        });

}
};

/*--------------------------------------------------Prazdne matice-----------------------------------------------------*/

TEST_F(Empty_Matrix, Create_Matrix){

    /*matice, ktore nie je mozne vytvorit -> minusovy index alebo nulovy index*/
    EXPECT_ANY_THROW(Matrix(-500, 10));
    EXPECT_ANY_THROW(Matrix(-1, 2));
    EXPECT_ANY_THROW(Matrix(0, 0));
    EXPECT_ANY_THROW(Matrix(0, 1));
    EXPECT_ANY_THROW(Matrix(1, 0));

    /*matice, ktore je mozne vytvorit*/
    EXPECT_NO_THROW(Matrix());
    EXPECT_NO_THROW(Matrix(1, 20));
    EXPECT_NO_THROW(Matrix(10, 90));
    EXPECT_NO_THROW(Matrix(1, 1));
    EXPECT_NO_THROW(Matrix(4, 4));
}

TEST_F(Empty_Matrix, First_Set_Value){
    //testy, kde ocakvame chybu
    EXPECT_FALSE(matrix_m.set(2,3,4));
    EXPECT_FALSE(matrix_m.set(-5,2,4));
    EXPECT_FALSE(matrix_m.set(-5,-5,-5));
    EXPECT_FALSE(matrix_m.set(2,-2,5));

    //testy, kde neocakvame chybu
    EXPECT_TRUE(matrix_m.set(0,0,2));
    EXPECT_EQ(matrix_m.get(0,0),2);
}

TEST_F(Empty_Matrix, Second_Set_Value){
    //testy, kde ocakvame chybu
    EXPECT_FALSE(matrix_m.set(vector<vector< double > >(5, vector<double>(2,3))));
    EXPECT_FALSE(matrix_m.set(vector<vector< double > >(2, vector<double>(5,5))));
    EXPECT_FALSE(matrix_m.set(vector<vector< double > >{{}}));
    EXPECT_FALSE(matrix_m.set(vector<vector< double > >{{200,-200,9,65.25}}));
    //testy, kde neocakvame chybu
    EXPECT_TRUE(matrix_m.set(vector<vector< double > >(1, vector<double>(1, 10))));
    EXPECT_TRUE(matrix_m.set(vector<vector< double > >(1, vector<double>(1, 5))));
}

TEST_F(Empty_Matrix, Get_Value){
    //neocakavame chybu vratenu programom
    EXPECT_NO_THROW(matrix_m.get(0,0));
    //ocakavame chybu vratenu programom
    EXPECT_ANY_THROW(matrix_m.get(9,0));
    EXPECT_ANY_THROW(matrix_m.get(0,-2));
    EXPECT_ANY_THROW(matrix_m.get(-10,0));

    EXPECT_EQ(matrix_m.get(0,0), 0);
}

TEST_F(Empty_Matrix, Compare_Matrix){
    Matrix matica{1,1};
    matica.set(0,0,10);

    //Porovnavame prazdnu maticu s vytvorenou maticou
    EXPECT_ANY_THROW(matrix_m == (Matrix(1,5)));
    EXPECT_ANY_THROW(matrix_m == (Matrix(0,0)));

    //Ocakavame chyvu, matice sa nemozu rovnat
    EXPECT_FALSE(matrix_m == (matica));
}

TEST_F(Empty_Matrix, Count_Matrix){
    Matrix matica{1,1};
    matica.set(0,0,10);

    EXPECT_ANY_THROW(matrix_m + (Matrix(1,5)));
    EXPECT_ANY_THROW(matrix_m + (Matrix(0,0)));

    //prazdna matica sa nebude rovnat suctom dvoch matic
    EXPECT_FALSE(matrix_m == (matrix_m +(matica)));
    //ocakavame pravdu
    EXPECT_TRUE(matica == (matrix_m +(matica)));
}

TEST_F(Empty_Matrix, Multiply_Matrix){
    //testujeme nasobenie matic
    EXPECT_ANY_THROW(matrix_m * (Matrix(2,1)));
    EXPECT_ANY_THROW(matrix_m * (Matrix(0,0)));

    Matrix multiply1x2_res(1,4);
    multiply1x2_res.set(vector<vector<double>>(1, vector<double>(4,0)));
    Matrix multiply1x2(1,4);
    multiply1x2.set(vector<vector<double>>{
            {1,5,9,2}
    });
    EXPECT_TRUE(multiply1x2_res ==(matrix_m *(multiply1x2)));
}

TEST_F(Empty_Matrix, Multiply_Matrix_By_Number){
    //testujeme, ci sa budu rovnat matice, ak vynasobime prazdnu maticu a porovname ju s prazdnou maticou
    EXPECT_TRUE(matrix_m *(2) == (matrix_m));
    //testujeme, ci po vytvoreni matici, ktora ma hodnotu 10, ci po vynasobeni cislom sa bude rovnat vytvorenej matici
    matrix_m.set(0, 0, 10);
    Matrix mat_result(1, 1);
    mat_result.set(vector<vector< double > > {
        {100}
    });
    EXPECT_TRUE(mat_result ==(matrix_m *(10)));
}

TEST_F(Empty_Matrix, Solve_Equaltion){
    EXPECT_ANY_THROW(matrix_m.solveEquation(vector<double> {2,3,4,5}));
    EXPECT_ANY_THROW(matrix_m.solveEquation({2}));

    Matrix matica{2,1};
    matica.set(vector<vector<double>>{
        {1},
        {4}
    });
    EXPECT_ANY_THROW(matica.solveEquation(vector<double> {1,4}));
}

/*-------------------------------------------------Neprazdne matice----------------------------------------------------*/

TEST_F(No_Empty_Matrix, Firs_Set_Value){
    //Otestovanie nespravnych matic
    EXPECT_FALSE(m2x2.set(0,2,12));
    EXPECT_FALSE(m2x2.set(9,2,12));
    EXPECT_FALSE(m3x3.set(-1,2,7));
    EXPECT_FALSE(m3x3.set(0,3,5));
    EXPECT_FALSE(m3x2.set(1,2,7));
    EXPECT_FALSE(m3x2.set(0,4,1));
    EXPECT_FALSE(m4x2.set(0,4,2));
    EXPECT_FALSE(m5x5.set(0,5,5));

    //Otestovanie spravnych matic
    EXPECT_TRUE(m2x2.set(1,1,3));
    EXPECT_TRUE(m3x3.set(1,2,2));
    EXPECT_TRUE(m3x2.set(0,0,0));
    EXPECT_TRUE(m4x2.set(2,0,2));
    EXPECT_TRUE(m5x5.set(4,4,4));
}

TEST_F(No_Empty_Matrix, Get_Value){
    //testujeme, ze ak neprekrocime indexy kod nevyhodi chybovu hlasku
    EXPECT_NO_THROW(m2x2.get(1,1));
    EXPECT_NO_THROW(m3x3.get(2,0));
    EXPECT_NO_THROW(m5x5.get(4,1));
    //testujeme ci program zisti, ze sme mimo indexy
    EXPECT_ANY_THROW(m2x2.get(2,4));
    EXPECT_ANY_THROW(m3x3.get(2,4));
    EXPECT_ANY_THROW(m5x5.get(7,4));
    //hladame cislo, ktore sa na danych indexov nachadza
    EXPECT_EQ(m2x2.get(1, 1), 2);
    EXPECT_EQ(m3x3.get(2, 2), 5);
    EXPECT_EQ(m5x5.get(4, 2), 2);
    //hladame cislo, ktore sa na danych indexov nenachadza
    EXPECT_NE(m2x2.get(1, 1), 8);
    EXPECT_NE(m3x3.get(2, 2), 2);
    EXPECT_NE(m5x5.get(4, 2), 0);
}
TEST_F(No_Empty_Matrix, Compare_Matrix ){
    EXPECT_ANY_THROW(m2x2 == m5x5);
    EXPECT_ANY_THROW(m4x2 == m3x3);
    //prikaz sa ma vyhodnotit ako false
    EXPECT_FALSE(m3x3 == Matrix(3,3));
    //porovnavame rovnake matice, co znamena, ze sa musia rovnat
    EXPECT_TRUE(m3x3 == m3x3);
    EXPECT_TRUE(m5x5 == m5x5);

}
TEST_F(No_Empty_Matrix, Count_Matrix ){
    EXPECT_ANY_THROW(m4x2 + m5x5);
    EXPECT_ANY_THROW(m2x2 + m3x3);
    EXPECT_ANY_THROW(m3x3 + m5x5);

    EXPECT_FALSE(m2x2 + m2x2 == m2x2);
    EXPECT_NO_THROW(m3x3 + m3x3);

    //vytvorime si par matic a porovnat ich ci sa rovnaju suctom dvoch matic
    Matrix m1(3,3);
    m1.set(vector<vector< double > > {{5,1,2},{2,5,3},{2,5,6}});
    EXPECT_FALSE(m3x3 + m3x3 == m1);

    m1.set(vector<vector< double > >{{2,4,12},{14,18,4},{14,6,10}});
    EXPECT_TRUE(m3x3 + m3x3 == m1);
}
TEST_F(No_Empty_Matrix, Multiply_Matrix){
    EXPECT_NO_THROW(m3x3 * m3x2);
    EXPECT_NO_THROW(m2x2 * m2x2);
    EXPECT_NO_THROW(m2x2 * m2x2);

    EXPECT_ANY_THROW(m2x2 * m4x2);
    EXPECT_ANY_THROW(m3x3 * m5x5);

    //vytvorime si maticu a porovname ich ci sa rovnaju sucinu dvoch matic
    Matrix m1(3,2);
    m1.set(vector<vector< double > > {{35,52},{132,29},{81,87}});
    EXPECT_FALSE(m3x3 * m3x2 == m1);
    m1.set(vector<vector< double > >{{31,52},{132,99},{81,87}});
    EXPECT_TRUE(m3x3 * m3x2 == m1);
}

TEST_F(No_Empty_Matrix, Multiply_Matrix_By_Number){
    EXPECT_FALSE(m2x2 == m2x2 * 6);
    EXPECT_TRUE(m3x3 + m3x3 == m3x3 * 2);

    //provnavame maticu so sucinom matice s cislom
    Matrix m1(3,3);
    m1.set(vector<vector< double > > {{57,38,40},{84,101,70},{63,56,73}});
    EXPECT_FALSE(m3x3 * 2 == m1);
}

TEST_F(No_Empty_Matrix, Solve_Equaltion){
    EXPECT_ANY_THROW(m3x3.solveEquation(vector<double> {2}));
    EXPECT_ANY_THROW(m4x2.solveEquation(vector<double> {2,3,4}));
    EXPECT_ANY_THROW(m5x5.solveEquation(vector<double> {2,3,4,5}));
    EXPECT_ANY_THROW(Matrix(5,5).solveEquation(vector<double> {2,3,4,5,6}));

    //vytvorime si 2x2 maticu a porovnavame x1,x2 s vytvorenymi vektormi...dopredu sme si tuto sustavu vypocitali
    Matrix m1(2,2);
    m1.set(vector<vector< double > > {{2,-25},{-1,15}});
    vector<double> right_2x2_vector = {21,1};
    vector<double> bad_2x2_vector = {-2,5};

    EXPECT_TRUE(m1.solveEquation(vector<double>{17,-6}) ==  right_2x2_vector );
    EXPECT_FALSE(m1.solveEquation(vector<double>{17,-6}) ==  bad_2x2_vector );
}

TEST_F(No_Empty_Matrix, Transpose_Matrix){
    //porovname ci sa rovna matice jej transponovanej matici -> program by mal vyhodit false
    EXPECT_FALSE(m3x3.transpose() == m3x3);
    EXPECT_FALSE(m5x5.transpose() == m5x5);

    //vytvorime transponovanu maticu k matici, ktoru sme uz vytvorili na zaciatku
    Matrix trans2x2(2,2);
    trans2x2.set(vector<vector< double > > {{4,5},{8,2}});
    EXPECT_TRUE(m2x2.transpose() == trans2x2);
}
TEST_F(No_Empty_Matrix,Inverse_Matrix){
    //testujeme, ci program vie odhalit ak sa neda spravit inverzna matica (matica musi byt stvorcova)
    EXPECT_ANY_THROW(m4x2.inverse());
    EXPECT_ANY_THROW(m5x5.inverse());
    EXPECT_NO_THROW(m3x3.inverse());

    //vytvorime si  maticu a k nej inverznu a porovname ju s dopredu vytvorenou inverznou maticou
    Matrix mat2x2(2,2);
    mat2x2.set(vector<vector< double > > {{-1,-2},{-3,-4}});
    Matrix inverse2x2(2,2);
    inverse2x2.set(vector<vector< double > > {{2,-1},{-1.5,0.5}});
    EXPECT_TRUE(mat2x2.inverse() == inverse2x2);
}

/*** Konec souboru white_box_tests.cpp ***/
