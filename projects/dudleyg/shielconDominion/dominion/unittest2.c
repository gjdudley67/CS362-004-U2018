/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * fullDeckCountUnitTest: fullDeckCountUnitTest.c dominion.o rngs.o
 *      gcc -o fullDeckCountUnitTest -g  fullDeckCountUnitTest.c dominion.o rngs.o $(CFLAGS)
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
    struct gameState G , testG;
	
    printf ("TESTING fullDeckCount:\n");
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
				memcpy(&testG, &G, sizeof(struct gameState)); //Make a test copy of the new game.
				myAssert(fullDeckCount(0 , copper, &testG) , 7, "Starting copper amount correct as reported from fullDeckCount" , 0);
				myAssert(fullDeckCount(0 , estate, &testG) , 3, "Starting estate correct as reported from fullDeckCount" , 0);
				myAssert(fullDeckCount(1 , copper, &testG) , 7, "Starting copper amount correct as reported from fullDeckCount" , 1);
				myAssert(fullDeckCount(1 , estate, &testG) , 3, "Starting estate correct as reported from fullDeckCount" , 1);
				
				testG.discard[0][ testG.discardCount[0] ] = estate;
				testG.discardCount[0]++; 
				myAssert(fullDeckCount(0 , estate, &testG) , 4, "Estate count correct as reported from fullDeckCount after inserting estate into discard" , 0);
				testG.discard[0][ testG.discardCount[0] ] = curse;
				testG.discardCount[0]++;
				myAssert(fullDeckCount(0 , estate, &testG) , 4, "Estate count correct as reported from fullDeckCount after inserting curse into discard" , 0);
				myAssert(fullDeckCount(1 , estate, &testG) , 3, "Estate count correct as reported from fullDeckCount after inserting estate into discard of player 0" , 1);
				testG.discard[0][ testG.discardCount[0] ] = curse;
				testG.discardCount[0]++;
				myAssert(fullDeckCount(0 , curse, &testG) , 2, "Curse count correct as reported from fullDeckCount after inserting 2 curses into discard" , 0);
				
				testG.hand[0][testG.handCount[0]] = testG.deck[0][testG.deckCount[0] - 1];//Add card to hand
				testG.deckCount[0]--;
				testG.handCount[0]++;//Increment hand count
				myAssert(fullDeckCount(0 , estate, &testG) , 4, "Estate count correct as reported from fullDeckCount after drawing a new card" , 0);
				myAssert(fullDeckCount(0 , copper, &testG) , 7, "Copper amount correct as reported from fullDeckCount after drawing a new card" , 0);
				
				testG.deck[0][ testG.deckCount[0] ] = estate;
				testG.deckCount[0]++; 
				myAssert(fullDeckCount(0 , estate, &testG) , 5, "Estate count correct as reported from fullDeckCount after gaining a new estate in the deck" , 0);
				
				testG.deck[0][ testG.deckCount[0] ] = curse;
				testG.deckCount[0]++; 
				myAssert(fullDeckCount(0 , estate, &testG) , 5, "Estate count correct as reported from fullDeckCount after gaining a new curse in the deck" , 0);
		
				testG.hand[0][ testG.handCount[0] ] = curse;
				testG.handCount[0]++; 
				myAssert(fullDeckCount(0 , estate, &testG) , 5, "Estate count correct as reported from fullDeckCount after gaining a new curse in the hand" , 0);
				myAssert(fullDeckCount(0 , curse, &testG) , 4, "Curse count correct as reported from fullDeckCount after inserting 1 curse into the deck, and 1 curse into the hand" , 0);
				
				testG.hand[0][ testG.handCount[0] ] = village;
				testG.handCount[0]++; 
				myAssert(fullDeckCount(0 , village, &testG) , 1, "Village count correct as reported from fullDeckCount after gaining a new village in the hand" , 0);
				playCard(testG.handCount[0] - 1, 0, 0, 0, &testG);
				myAssert(fullDeckCount(0 , village, &testG) , 1, "Village count correct as reported from fullDeckCount after playing village from the hand" , 0); //About 99% positive this will fail, no playedcard checking.
				
    return 0;
}
