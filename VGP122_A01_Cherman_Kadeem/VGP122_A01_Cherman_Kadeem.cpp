// VGP122_A01_Cherman_Kadeem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

void dealer(int old_total, int old_aceCount, int cards, double probability, int cardDeck[], double dealer_Probability[]);

int numOfSuits = 6;

int main()
{
    int i = 0, cardDeck[11]{};
    //Represents the number of aces in deck.
    double dealer_Probability[7]{};
    for (i = 1; i <= 9; i++)
        cardDeck[i] = 4 * numOfSuits;
        cardDeck[10] = 16 * numOfSuits;
        cardDeck[0] = 52 * numOfSuits;
        dealer(5, 0, 1, 1.0, cardDeck, dealer_Probability);
        for (i = 0; i < 6; i++) cerr << i << "\t" << dealer_Probability[i] << "\n";


    /*std::cout << "Hello World!\n";*/
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

/*
  Dealer Probability 
  0 = 17
  1 = 18
  2 = 19
  3 = 20
  4 = 21
  5 = blackJack
  6 = bust you loose.
*/

static void dealer(int old_total, int old_aceCount, int cards, double probability,int cardDeck[], double dealer_Probability[])
{
    int i, next_Card, new_Total = 0, new_AceAdded = 0;
    if (cards == 1) {
        for (i = 0; i <= 6; i++)
            dealer_Probability[i] = 0.0;
    }
    for (next_Card = 1; next_Card <= 10; next_Card++) {
        probability *= (double)cardDeck[next_Card] / (double)cardDeck[0];
        cardDeck[next_Card]--;
        cardDeck[0]--;
        new_Total = old_total + next_Card;
        new_AceAdded = old_aceCount + (next_Card == 1 ? 1 : 0);
        if (new_Total == 11 && new_AceAdded == 1) // Dealer has BlackJack
            dealer_Probability[5] += probability;
        else if (new_Total > 21)
            dealer_Probability[6] += probability;
        else if (new_Total >= 17)
            dealer_Probability[new_Total - 17] += probability;

        //Condition if dealer has a soft 17:
        /*else if ((new_Total >= 7) && (new_Total <= 11) && (new_AceAdded > 0)) dealer_Probability[new_Total - 7] += probability;*/
        else if (new_Total >= 7 && new_Total <= 11 && new_AceAdded > 0) {
            int index = new_Total - 7;
            dealer_Probability[index] += probability;
        }

        //Dealer hgas 7 or leass points: 
        else
            dealer(new_Total, new_AceAdded, cards + 1, probability, cardDeck, dealer_Probability);

        cardDeck[0]++;
        cardDeck[next_Card]++;
        probability /= (double)cardDeck[next_Card] / (double)cardDeck[0];
    }
}
