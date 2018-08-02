/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * VillageTest: VillageTest.c dominion.o rngs.o
 *      gcc -o VillageTest -g  VillageTest.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <math.h>


void printstate(struct gameState Old , struct gameState New, int player)
{
        printf("For original game state: deckcount = %d , handcount = %d, discardcount = %d, playedcount = %d, numbuys = %d, numactions = %d\n", Old.deckCount[player], Old.handCount[player], Old.discardCount[player], Old.playedCardCount, Old.numBuys, Old.numActions);
        printf("For new game state after card effect: deckcount = %d , handcount = %d, discardcount = %d, playedcount = %d, numbuys = %d, numactions = %d\n", New.deckCount[player], New.handCount[player], New.discardCount[player], New.playedCardCount, New.numBuys, New.numActions);
}




int myAssert(int Value1 , int Value2, const char* testDescription , int player, struct gameState Before, struct gameState After, int* TotalTestCounter, int* SuccessTestCounter, int* FailTestCounter)
{
	if (Value1 == Value2)
	{
		*SuccessTestCounter = *SuccessTestCounter + 1;
		//printf("%s test succeeded! For player %d \n", testDescription, player);
	}
	else
	{
		printf("%s test failed! For player %d \n", testDescription, player);
		printstate(Before, After, player);
		*FailTestCounter = *FailTestCounter + 1;
	}
	*TotalTestCounter = *TotalTestCounter + 1;
}


int main() {
	srand(time(NULL));
    int Ttestcount = 0;
    int Stestcount = 0;
    int Ftestcount = 0;

    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
	int LoopCounter;
    int p, r, handCount;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G , testG;;
	
    printf ("TESTING Village:\n");
for(LoopCounter = 0 ; LoopCounter < 3000 ; LoopCounter++)
{	
    for (p = 0; p < numPlayer; p++)
    {
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
				G.whoseTurn = p;
				//Initial random card counts
				G.deckCount[p] = (rand() % MAX_DECK/2);
				G.discardCount[p] = (rand() % MAX_DECK/2);
				G.handCount[p] = (rand() % MAX_HAND/2) + 1;	
				G.numActions = (rand() % 100);
		
				memcpy(&testG, &G, sizeof(struct gameState));
				
				
			    cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
				
				myAssert(testG.deckCount[p] + testG.handCount[p] + testG.discardCount[p] + testG.playedCardCount , G.deckCount[p] + G.handCount[p] + G.discardCount[p] + G.playedCardCount , "No New Cards Test", p, G, testG, &Ttestcount, &Stestcount, &Ftestcount);
					
				if(G.deckCount[p] + G.discardCount[p] >= 1)
				{
                myAssert(testG.handCount[p] , G.handCount[p] * 1, "Hand Count", p, G, testG, &Ttestcount, &Stestcount, &Ftestcount); // check if the number of cards in our hand increased by 1. Net gain is zero though.
				}
				
				myAssert(testG.numActions, G.numActions + 2, "NumActionsTest", p, G, testG, &Ttestcount, &Stestcount, &Ftestcount); //Make sure that the number of actions increased by 2
				myAssert(testG.numBuys, 1, "NumBuysTest", p, G, testG, &Ttestcount, &Stestcount, &Ftestcount); //Make sure that a Buy was not consumed.
				
				myAssert(testG.supplyCount[estate], 8 , "Estate supply count verified correct", p, G, testG, &Ttestcount, &Stestcount, &Ftestcount);
				myAssert(testG.supplyCount[duchy], 8 , "duchy supply count verified correct", p, G, testG, &Ttestcount, &Stestcount, &Ftestcount);
				myAssert(testG.supplyCount[province], 8 , "province supply count verified correct", p, G, testG, &Ttestcount, &Stestcount, &Ftestcount);
				myAssert(testG.supplyCount[copper], 46 , "copper supply count verified correct", p, G, testG, &Ttestcount, &Stestcount, &Ftestcount);  //Important to verify that we didn't take these from supply...
				myAssert(testG.supplyCount[silver], 40 , "silver supply count verified correct", p, G, testG, &Ttestcount, &Stestcount, &Ftestcount);
				myAssert(testG.supplyCount[gold], 30 , "gold supply count verified correct", p, G, testG, &Ttestcount, &Stestcount, &Ftestcount);
				
				
				if (numPlayer == 2)
				{
					if(p == 0)
					{
						myAssert(testG.handCount[1] , G.handCount[1], "Other Players Didn't Gain Cards in their hand", p+1, G, testG, &Ttestcount, &Stestcount, &Ftestcount); //Make sure the other player didn't somehow gain cards in their hand.
						myAssert(testG.deckCount[1] + testG.handCount[1] + testG.discardCount[1] , G.deckCount[1] + G.handCount[1] + G.discardCount[1], "Other Players didn't gain cards in their deck", p+1, G, testG, &Ttestcount, &Stestcount, &Ftestcount); //This test ensures that no new cards were somehow magically created by the adventurer card for the other player.
						myAssert(testG.discardCount[1], G.discardCount[1], "Other Players Discard Pile did not increase", p+1, G, testG, &Ttestcount, &Stestcount, &Ftestcount); //Ensure that the other player's discard pile did not increase in size for any reason.
					}
					if(p == 1)
					{
						myAssert(testG.handCount[0] , G.handCount[0], "Other Players didn't gain cards in their hand", p-1, G, testG, &Ttestcount, &Stestcount, &Ftestcount); //Make sure the other player didn't somehow gain cards in their hand.
						myAssert(testG.deckCount[0] + testG.handCount[0] + testG.discardCount[0], G.deckCount[0] + G.handCount[0] + G.discardCount[0], "Other Players didn't gain cards in their deck", p-1, G, testG, &Ttestcount, &Stestcount, &Ftestcount); //This test ensures that no new cards were somehow magically created by the adventurer card for the other player.
						myAssert(testG.discardCount[0], G.discardCount[0], "Other Players Discard Pile did not increase", p-1, G, testG, &Ttestcount, &Stestcount, &Ftestcount); //Ensure that the other player's discard pile did not increase in size for any reason.
					}
				}
				
    }
   testG.playedCardCount = 0; //Reset played card count
}
printf("Total Tests Ran: %d  , Total Successful Tests: %d , Total Failed Tests: %d\n", Ttestcount, Stestcount, Ftestcount);
    return 0;
}
