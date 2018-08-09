/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * numHandCardsUnitTest: numHandCardsUnitTest.c dominion.o rngs.o
 *      gcc -o numHandCardsUnitTest -g  numHandCardsUnitTest.c dominion.o rngs.o $(CFLAGS)
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
	
    printf ("TESTING numHandCards:\n");
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
				memcpy(&testG, &G, sizeof(struct gameState)); //Make a test copy of the new game.
				
				myAssert(numHandCards(&testG) , 5, "Starting hand count reported correct by numHandCards" , 0);
				testG.hand[0][ testG.handCount[0] ] = village;
				testG.handCount[0]++; 
				myAssert(numHandCards(&testG) , 6, "Hand count reported correct by numHandCards after adding village to the hand" , 0);
				testG.hand[0][testG.handCount[0]] = testG.deck[0][testG.deckCount[0] - 1];//Add card to hand
				testG.deckCount[0]--;
				testG.handCount[0]++;//Increment hand count
				myAssert(numHandCards(&testG) , 7, "Hand count reported correct by numHandCards after adding a new card to the hand from the deck" , 0);
				testG.discard[0][ testG.discardCount[0] ] = estate;
				testG.discardCount[0]++; 
				myAssert(numHandCards(&testG) , 7, "Hand count reported correct by numHandCards after adding a new card to the discard pile" , 0);
				testG.hand[0][ testG.handCount[0] ] = curse;
				testG.handCount[0]++; 
				myAssert(numHandCards(&testG) , 8, "Hand count reported correct by numHandCards after adding curse to the hand" , 0);
				
				for (i = 0; i < testG.handCount[0]; i++){ //Discard all cards
					testG.discard[0][testG.discardCount[0]++] = testG.hand[0][i];//Discard
					testG.hand[0][i] = -1;//Set card to -1
				}
					testG.handCount[0] = 0;//Reset hand count
					myAssert(numHandCards(&testG) , 0, "Hand count reported correct by numHandCards after discarding all cards from hand" , 0);
					
				testG.deck[0][ testG.deckCount[0] ] = estate;
				testG.deckCount[0]++;
				myAssert(numHandCards(&testG) , 0, "Hand count reported correct by numHandCards after adding 1 card to the deck" , 0);			
    return 0;
}
