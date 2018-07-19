/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * scoreForUnitTest: scoreForUnitTest.c dominion.o rngs.o
 *      gcc -o scoreForUnitTest -g  scoreForUnitTest.c dominion.o rngs.o $(CFLAGS)
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
	
    printf ("TESTING scoreFor:\n");
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
				memcpy(&testG, &G, sizeof(struct gameState));
				myAssert(scoreFor(0 , &testG) , 3, "Starting score correct as reported from scoreFor" , 0);
				myAssert(scoreFor(1 , &testG) , 3, "Starting score correct as reported from scoreFor" , 1);
				
				testG.discard[0][ testG.discardCount[0] ] = estate;
				testG.discardCount[0]++; 
				myAssert(scoreFor(0 , &testG) , 4, "Score correct after inserting estate into discard" , 0);
				testG.discard[0][ testG.discardCount[0] ] = curse;
				testG.discardCount[0]++;
				myAssert(scoreFor(0 , &testG) , 3, "Score correct after inserting curse into discard" , 0);
				testG.discard[0][ testG.discardCount[0] ] = great_hall;
				testG.discardCount[0]++;
				myAssert(scoreFor(0 , &testG) , 4, "Score correct after inserting great_hall into discard" , 0);
				testG.discard[0][ testG.discardCount[0] ] = gardens;
				testG.discardCount[0]++;
				printf("fullDeckCount returns %d\n", fullDeckCount(0, 0, &testG));
				printf("Total Cards for player 0: %d\n",testG.deckCount[0] + testG.handCount[0] + testG.discardCount[0] + testG.playedCardCount );
				printf("scoreFor reports %d after adding gardens", scoreFor(0 , &testG));
				myAssert(scoreFor(0 , &testG) , 5, "Score correct after inserting gardens into discard" , 0);
				int a;
				for (a = 4; a < 10; a++)
				{
					testG.discard[0][ testG.discardCount[0] ] = copper; //Insert 6 coppers into discard to raise Garden value
					testG.discardCount[0]++;
				}
				printf("Total Cards for player 0: %d\n",testG.deckCount[0] + testG.handCount[0] + testG.discardCount[0] + testG.playedCardCount );
				printf("scoreFor reports %d after adding more junk cards", scoreFor(0 , &testG));
				myAssert(scoreFor(0 , &testG) , 6, "Score correct after inserting more cards into discard" , 0);
				memcpy(&testG, &G, sizeof(struct gameState)); //Overwrite the game to start over.
				int x = 0;
				int v = 0;
				for(x = 0; x < 5 ; x++)
				{
					testG.hand[0][x] = estate;
				}			
				for(v = 0; v < 5 ; v++)
				{
					testG.deck[0][v] = estate;
				}
				myAssert(scoreFor(0, &testG), 10, "Score correct for all cards estates", 0);
				
				int g = 0;
				for(g = 0; g < 5 ; g++)
				{
					testG.hand[0][g] = duchy;
				}
				int l = 0;
				for(l = 0; l < 5 ; l++)
				{
					testG.deck[0][l] = duchy;
				}
				myAssert(scoreFor(0, &testG), 30, "Score correct for all cards duchys", 0);
				
				int q = 0;
				for(q = 0; q < 5 ; q++)
				{
					testG.hand[0][q] = province;
				}
				int o = 0;
				for(o = 0; o < 5 ; o++)
				{
					testG.deck[0][o] = province;
				}
				myAssert(scoreFor(0, &testG), 60, "Score correct for all cards provinces", 0);
    return 0;
}