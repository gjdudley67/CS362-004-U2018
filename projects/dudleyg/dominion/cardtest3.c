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

int myAssert(int Value1 , int Value2, const char* testDescription , int player)
{
	if (Value1 == Value2)
	{
		printf("%s test succeeded! For player %d \n", testDescription, player);
	}
	else
	{
		printf("%s test failed! For player %d \n", testDescription, player);
	}
}


int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G , testG;;
	
    printf ("TESTING Village:\n");
    for (p = 0; p < numPlayer; p++)
    {
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
				memcpy(&testG, &G, sizeof(struct gameState));
				testG.whoseTurn = p;
				testG.playedCardCount = 0;
			    cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
				//After initializeGame, there should be 10 total cards.
                myAssert(testG.handCount[p] , G.handCount[p] * 1, "Hand Count", p); // check if the number of cards in our hand increased by 1. Net gain is zero though.
				printf("Actual Total Card Count %d , expected card count %d\n", testG.deckCount[p] + testG.handCount[p] + testG.discardCount[p] + testG.playedCardCount, G.deckCount[p] + G.handCount[p] + G.discardCount[p] + G.playedCardCount);
				myAssert(testG.deckCount[p] + testG.handCount[p] + testG.discardCount[p] + testG.playedCardCount , 10, "No New Cards Test", p); //This test ensures that no new cards were somehow magically created by the village card.
				myAssert(testG.numActions, 3, "NumActionsTest", p); //Make sure that the number of actions increased by 2
				myAssert(testG.numBuys, 1, "NumBuysTest", p); //Make sure that a Buy was not consumed.
				myAssert(testG.supplyCount[estate], 8 , "Estate supply count verified correct", p);
				myAssert(testG.supplyCount[duchy], 8 , "duchy supply count verified correct", p);
				myAssert(testG.supplyCount[province], 8 , "province supply count verified correct", p);
				myAssert(testG.supplyCount[copper], 46 , "copper supply count verified correct", p);  //Important to verify that we didn't take these from supply...
				myAssert(testG.supplyCount[silver], 40 , "silver supply count verified correct", p);
				myAssert(testG.supplyCount[gold], 30 , "gold supply count verified correct", p);
				if(p == 0)
				{
					myAssert(testG.handCount[1] , 0, "Other Players Didn't Gain Cards in their hand", p+1); //Make sure the other player didn't somehow gain cards in their hand.
					myAssert(testG.deckCount[1] + testG.handCount[1] + testG.discardCount[1], 10, "Other Players didn't gain cards in their deck", p+1); //This test ensures that no new cards were somehow magically created by the adventurer card for the other player.
					myAssert(testG.discardCount[1], 0, "Other Players Discard Pile did not increase", p+1); //Ensure that the other player's discard pile did not increase in size for any reason.
				}
				if(p == 1)
				{
					myAssert(testG.handCount[0] , 5, "Other Players didn't gain cards in their hand", p-1); //Make sure the other player didn't somehow gain cards in their hand.
					myAssert(testG.deckCount[0] + testG.handCount[0] + testG.discardCount[0], 10, "Other Players didn't gain cards in their deck", p-1); //This test ensures that no new cards were somehow magically created by the adventurer card for the other player.
					myAssert(testG.discardCount[0], 0, "Other Players Discard Pile did not increase", p-1); //Ensure that the other player's discard pile did not increase in size for any reason.
				}
    }
    return 0;
}