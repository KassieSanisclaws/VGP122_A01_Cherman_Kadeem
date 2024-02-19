// VGP122_A01_Cherman_Kadeem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// [3] Call the function of expected value of player_Stands when player is standing.

#include <iostream>
using namespace std;

//Declartion of functions:
double player_Hit(int player_TotalPoints, int pace, int cards, int cardDeck[]);
double player_Stands(int player_Total, int player_PaceTimer, int player_Cards, int cardDeck[]);
double max_OfTwoNum(double x, double y);
double player_DoubleHit(int player_Total, int pace, int cardDeck[]);
double player_Splits(int player_Total, int pace, int cardDeck[]);
void dealer(int old_total, int old_aceCount, int cards, double probability, int cardDeck[], double dealer_Probability[]);


int numOfSuits = 6;
int faceUp_Card;

int main()
{
    int ch = 0, i = 0, j = 0, cardDeck[11]{}, pc1, pc2;
    //Represents the number of aces in deck.
    double dealer_Probability[7]{}, ev_Stand = 0.0, ev_Hit = 0.0, ev_Double = 0.0, ev_Split = 0.0;
    for (i = 1; i <= 9; i++)
        cardDeck[i] = 4 * numOfSuits;
        cardDeck[10] = 16 * numOfSuits;
        cardDeck[0] = 52 * numOfSuits;

          cerr << "1. Dealer probability chances\n";
          cerr << "2. Player Hand\n";
          cerr << "3. Whole gamee\n";
          cin >> ch;

          if (ch == 1)
          {
              for (i = 0; i <= 10; i++) {
                  cout << "Face Up Card = " << i << "\n";
                  cardDeck[i]--;
                  cardDeck[0]--;
                  dealer(i, (i == 1 ? 1 : 0), 1, 1.0, cardDeck, dealer_Probability);

                  for (j = 0; j <= 6; j++)
                      cerr << j << "\t" << dealer_Probability[j] << "\n";
                  //Adds back cards after down passing cards dealer fashion:
                  cardDeck[i]++;
                  cardDeck[0]++;
              }
          }
          else if (ch == 2) {
              cerr << "Player Card 1:";
              cin >> pc1;
              cerr << "Player Card 2: ";
              cin >> pc2;
              cerr << "Dealers up card: ";
              cin >> faceUp_Card;
              cardDeck[pc1]--;
              cardDeck[pc2]--;
              cardDeck[faceUp_Card]--;
              cardDeck[0] -= 3;
              ev_Stand = player_Stands(pc1 + pc2, (pc1 == 1 ? 1 : 0) + (pc2 == 1 ? 1 : 0), 2, cardDeck);
              //Shows the user what happens when they hit:
              ev_Hit = player_Hit(pc1 + pc2, (pc1 == 1 ? 1 : 0) + (pc2 == 1 ? 1 : 0), 2, cardDeck);
              //Call to player douybling hit:
              ev_Double = player_DoubleHit(pc1 + pc2, (pc1 == 1 ? 1 : 0) + (pc2 == 1 ? 1 : 0), cardDeck);
             //Player must have a pair to split:
              if (pc1 == pc2) {
                  ev_Split = player_Splits(pc1, (pc1 == 1 ? 1 : 0), cardDeck);
              }
              else {
                  ev_Split = -1.0;
              }
              cerr << "EV stand =\t" << ev_Stand << "\n";
              cerr << "EV hit =\t" << ev_Hit << "\n";
              cerr << "EV Double =\t" << ev_Double << "\n";
              cerr << "EV split = \t" << ev_Split << "\n";
          }
          //Analyze the whole game:
          else if (ch == 3) {
              double prob = 1.0;
              double total_Prob = 0.0;
              double total_Value = 0.0;

              for (pc1 = 1; pc1 <= 10; pc1++) {
                  prob *= (double)cardDeck[pc1] / (double)cardDeck[0];
                  cardDeck[pc1]--;
                  cardDeck[0]--;

                  for (pc2 = pc1; pc2 <= 10; pc2++) {
                      prob *= (pc1 == pc2 ? 1 : 2) * (double)cardDeck[pc2] / (double)cardDeck[0];
                      cardDeck[pc2]--;
                      cardDeck[0]--;

                      for (faceUp_Card = 1; faceUp_Card <= 10; faceUp_Card++) {
                          prob *= (double)cardDeck[faceUp_Card] / (double)cardDeck[0];
                          total_Prob += prob;
                          cardDeck[faceUp_Card]--;
                          cardDeck[0]--;
                          ev_Stand = player_Stands(pc1 + pc2, (pc1 == 1 ? 1 : 0) + (pc2 == 1 ? 1 : 0), 2, cardDeck);
                          //Shows the user what happens when they hit:
                          ev_Hit = player_Hit(pc1 + pc2, (pc1 == 1 ? 1 : 0) + (pc2 == 1 ? 1 : 0), 2, cardDeck);
                          //Call to player douybling hit:
                          ev_Double = player_DoubleHit(pc1 + pc2, (pc1 == 1 ? 1 : 0) + (pc2 == 1 ? 1 : 0), cardDeck);
                          //Player must have a pair to split:
                          if (pc1 == pc2) {
                              ev_Split = player_Splits(pc1, (pc1 == 1 ? 1 : 0), cardDeck);
                          }
                          else {
                            ev_Split = -1.0;
                            printf("%i, %i, %i,%f, %f, %f, %f\n", pc1, pc2, faceUp_Card, ev_Stand, ev_Hit, ev_Double, ev_Split);

                          }
                          cardDeck[0]++;
                          cardDeck[faceUp_Card]++;
                          prob /= (double)cardDeck[faceUp_Card] / (double)cardDeck[0];
                     }
                          cardDeck[0]++;
                          cardDeck[pc2]++;
                          prob /= (pc1 == pc2 ? 1 : 2) * (double)cardDeck[pc2] / (double)cardDeck[0];
                  }
                          cardDeck[0]++;
                          cardDeck[pc1]++;
                          prob /= (double)cardDeck[pc1] / (double)cardDeck[0];
              }
          }
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

//Player function 
static double player_Stands(int player_Total, int player_PaceTimer, int player_Cards, int cardDeck[])
{
   double player_Stands = 0.0, dealers_Probability[7]{};
   //Test-Case when player has a Black Jack:
     if ((player_Total == 11) && (player_PaceTimer == 1) && (player_Cards == 2)) {
        //Test-Case player has winning Black Jack cards!:6
         if ((faceUp_Card > 1) && (faceUp_Card < 10)) {
             return 1.5;
         }
         else {
        //Call Dealer function 
             dealer(faceUp_Card, (faceUp_Card == 1 ? 1 : 0), 1, 1.0, cardDeck, dealers_Probability);
             return 1.5 * (dealers_Probability[0] + dealers_Probability[1] + dealers_Probability[2] + dealers_Probability[3] + dealers_Probability[4] + dealers_Probability[6]);
         }
      }
      //Test-Case Player ghets a Bust in Balck Jack:
       else if (player_Total > 21) {
         return -1.0;
      }
      //Test-Case player has a soft hand which then player gets 10points added to their total:
       else {
         if ((player_Total <= 11) && (player_PaceTimer > 0)) {
             player_Total += 10;
       //Call Dealer function on player hand card count:
             dealer(faceUp_Card, (faceUp_Card == 1 ? 1 : 0), 1, 1.0, cardDeck, dealers_Probability);
             player_Stands = dealers_Probability[6];
         //Probability of dealer Black Jack:
             player_Stands -= dealers_Probability[5]; 
           for (int i = 0; i <= 4; i++) {
               if (player_Total > i + 17) {
                   player_Stands + dealers_Probability[i];
               }
                else if (player_Total < i + 17) {
                   player_Stands -= dealers_Probability[i];
                }
             }
         }
      }
     //Return expected value of player_Stands:
     return player_Stands;
}

//Player Function for when player hits Calculated thexpected value for player:
static double player_Hit(int player_TotalPoints, int pace, int cards, int cardDeck[])
 {
      //Numbers of cards to determine if player has Black Jack
       int next_Card;
       double prob = 0.0, ev_Stand, ev_Hit, ev_Hit_Again;
       ev_Hit = 0.0;

     for (next_Card = 1; next_Card <= 10; next_Card++) {
       //Player probability of getting any given rank card:
         prob = (double)cardDeck[next_Card] / (double)cardDeck[0];
         cardDeck[next_Card]--;
         cardDeck[0]--;
        //Stand of hit decision:
         ev_Stand = player_Stands(player_TotalPoints + next_Card, pace + (next_Card == 1 ? 1 : 0), cards + 1, cardDeck);
        //Player Hits again calling the player Hit function recussively to calculate:
         if (player_TotalPoints + next_Card < 17) {
          ev_Hit_Again = player_Hit(player_TotalPoints + next_Card, pace + (next_Card == 1 ? 1 : 0), cards + 1, cardDeck);
         }
         else {
        //Makes the player stand if player has 17 and or more:
           ev_Hit_Again = -1;
           ev_Hit += prob * max_OfTwoNum(ev_Stand, ev_Hit_Again);
           cardDeck[next_Card]++;
           cardDeck[0]++;
         }
     }
     return ev_Hit;
 }
//Function for when player double downs on bet:
static double player_DoubleHit(int player_Total, int pace, int cardDeck[]) 
{
    int next_Card; 
    double prob, ev_Double;
    ev_Double = 0.0;
    
    if (player_Total > 11) {
        ev_Double = -1;
    }
    else {
    //Loop through what the next card is:
      for (next_Card = 1; next_Card <= 10; next_Card++) {
        //Player probability of getting any given rank card:
        prob = (double)cardDeck[next_Card] / (double)cardDeck[0];
        cardDeck[next_Card]--;
        cardDeck[0]--;
        //Stand of hit decision doubls cant take any more cards:
        ev_Double += prob * player_Stands(player_Total + next_Card, pace + (next_Card == 1 ? 1 : 0),3, cardDeck);
            cardDeck[next_Card]++;
            cardDeck[0]++;
      }
    }
    //Player is betting twice as mouch:
    return 2 * ev_Double;
}

//Test-Case what happens after player splits:
static double player_Splits(int player_Total, int pace, int cardDeck[]) 
{
    int next_Card;
    double prob, ev_Split, ev_Stand, ev_Hit;
    ev_Split = 0.0;

  for (next_Card = 1; next_Card <= 10; next_Card++) 
    {
    //STEPS:
    //First find the probability of the card and remove from deck.
    //Player has choice to stand or hit.
      prob = (double)cardDeck[next_Card] / (double)cardDeck[0];
      cardDeck[next_Card]--;
      cardDeck[0]--;
    //Expect value of standing is what ever i get from treat ace and a 10 as 21.
      ev_Stand = player_Stands(player_Total + next_Card, pace + (next_Card == 1 ? 1 : 0), 3, cardDeck);
    //Send 2 cards for the hit function.
      if (player_Total == 1) {
          ev_Hit = -1.0;
      }
      else {
      ev_Hit = player_Stands(player_Total + next_Card, pace + (next_Card == 1 ? 1 : 0), 2, cardDeck);
      ev_Split += prob * max_OfTwoNum(ev_Stand, ev_Hit);
      cardDeck[next_Card]++;
      cardDeck[0]++;
      }
    }
  //After running through all player possiblities of 10 possible cards because player is doubling bet multiple by 2.
   return 2 * ev_Split;
 }

//Created Function that returns the greate of the 2 values:
static double max_OfTwoNum(double x, double y)
 {
    if (x > y) {
        return x;
    }
    else {
        return y;
    }
 }

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

//Dealer function for card distribution from dealer deck and probability of dealer wins ratio of chance to hit on the ace through int itterations:
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
