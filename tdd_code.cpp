//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Marek Spirka <xspirk01@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Marek Spirka
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find/GetHead ...
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "singly linked list", ktera bude splnovat dodane testy
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    m_pHead == NULL;
}

PriorityQueue::~PriorityQueue()
{
    Element_t* actual = m_pHead;
    while (actual != NULL){
        Element_t* next = actual->pNext;
        delete actual;
        actual = next;
    }
    m_pHead = NULL;
}

void PriorityQueue::Insert(int value)
{
    //pridanie a alokovanie pamate pre novy prvok
    Element_t *ac_element = m_pHead;
    //alokovanie pamate pre novy prvok v liste
    Element_t *add_element = (Element_t*) malloc(sizeof (Element_t));

    //osetrenie kodu pri nepodarenom alokovani pamate
    if(add_element == nullptr){
        fprintf(stderr, "Error with allocation memory");
        return;
    }
    //do noveho prvku ulozime hodnotu, ktoru mi priradime cez premennu value
    add_element->value = value;
    add_element->pNext = NULL;


    //ak je list prazdny vlozime na zaciatok novy prvok
    if(m_pHead == nullptr){
        m_pHead = add_element;
        return;
    }

    //pridanie noveho prvku na zaciatok listu
   else if(value > ac_element->value){
        m_pHead = add_element;
        add_element->pNext = ac_element;
       return;
    }

    while (true){
        //pridanie noveho prvku na koniec listu
        if ((ac_element->pNext == NULL) && (value < ac_element->value)){
            ac_element->pNext = add_element;
            break;
        }
        //pridanie noveho prvku do listu
       else if (value > ac_element->pNext->value){
           add_element->pNext = ac_element->pNext;
           ac_element->pNext = add_element;
           break;
    }
        ac_element = ac_element->pNext;
    }
}

bool PriorityQueue::Remove(int value)
{
    //ak by bol list prazdny
    if (m_pHead == NULL){
        return false;
    }

    Element_t* ac_element = m_pHead;
    Element_t* las_element;

    //ak sa prvok nachadza na zaciatku listu
    if(m_pHead->value == value){
        m_pHead = m_pHead->pNext;
        delete(ac_element);
        return true;
    }
    //prehladavame list dokym nenajdeme hodnotu, ktoru chceme vymazat
    while (ac_element->value != value){
        if(ac_element->pNext == nullptr){
            return false;
        }
        las_element = ac_element;
        ac_element = ac_element->pNext;
    }

    las_element->pNext = ac_element->pNext;
    delete(ac_element);
    return true;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    //ak by bol list prazdny
    if (m_pHead == NULL){
        return NULL;
    }

    Element_t *ac_element = m_pHead;
    //prezerame cyklom list dokym nenajdeme hladanu hodnotu, ak najdeme hodnotu vratime prvok listu s danou hodnotou
    while (ac_element->value != value){
        if(ac_element->pNext == nullptr){
            return nullptr;
        }
        ac_element = ac_element->pNext;
    }
    return ac_element;

}

size_t PriorityQueue::Length()
{
    //osetrenie pri prazdnom liste
    if (m_pHead == nullptr){
        return 0;
    }

    Element_t *ac_element = m_pHead;
	int lenght = 1;

    //prechadzame cely list az kym nenarazime na koniec
    while (ac_element->pNext != NULL){
        lenght++;
        ac_element = ac_element->pNext;
    }
    //z funkcii vraciame dlzku listo -> pocet prvkov v liste
    return lenght;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
