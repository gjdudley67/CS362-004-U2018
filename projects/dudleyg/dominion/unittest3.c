/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * getCostUnitTest: getCostUnitTest.c dominion.o rngs.o
 *      gcc -o getCostUnitTest -g  getCostUnitTest.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"




int myAssert(int Value1 , int Value2, const char* testDescription)
{
	if (Value1 == Value2)
	{
		printf("%s test succeeded!\n", testDescription);
	}
	else
	{
		printf("%s test failed!\n", testDescription);
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
	
    printf ("TESTING getCost:\n");
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
				memcpy(&testG, &G, sizeof(struct gameState)); //Make a test copy of the new game.
				myAssert(getCost(curse) , 0, "Curse cost verified in getCost"); //Verify all costs
				myAssert(getCost(estate) , 2, "Estate cost verified in getCost");
				myAssert(getCost(duchy) , 5, "duchy cost verified in getCost");
				myAssert(getCost(province) , 8, "province cost verified in getCost");
				myAssert(getCost(copper) , 0, "copper cost verified in getCost");
				myAssert(getCost(silver) , 3, "silver cost verified in getCost");
				myAssert(getCost(gold) , 6, "gold cost verified in getCost");
				myAssert(getCost(adventurer) , 6, "adventurer cost verified in getCost");
				myAssert(getCost(council_room) , 5, "council_room cost verified in getCost");
				myAssert(getCost(feast) , 4, "feast cost verified in getCost");
				myAssert(getCost(gardens) , 4, "gardens cost verified in getCost");
				myAssert(getCost(mine) , 5, "mine cost verified in getCost");
				myAssert(getCost(remodel) , 4, "remodel cost verified in getCost");
				myAssert(getCost(smithy) , 4, "smithy cost verified in getCost");
				myAssert(getCost(village) , 3, "village cost verified in getCost");
				myAssert(getCost(baron) , 4, "baron cost verified in getCost");
				myAssert(getCost(great_hall) , 3, "great_hall cost verified in getCost");
				myAssert(getCost(minion) , 5, "minion cost verified in getCost");
				myAssert(getCost(steward) , 3, "steward cost verified in getCost");
				myAssert(getCost(tribute) , 5, "tribute cost verified in getCost");
				myAssert(getCost(ambassador) , 3, "ambassador cost verified in getCost");
				myAssert(getCost(cutpurse) , 4, "cutpurse cost verified in getCost");
				myAssert(getCost(embargo) , 2, "embargo cost verified in getCost");
				myAssert(getCost(outpost) , 5, "outpost cost verified in getCost");
				myAssert(getCost(salvager) , 4, "salvager cost verified in getCost");
				myAssert(getCost(sea_hag) , 4, "sea_hag cost verified in getCost");
				myAssert(getCost(treasure_map) , 4, "treasure_map cost verified in getCost");
				myAssert(getCost(5234193282717284817264) , -1, "Very high absurd input verified as bad input in getCost"); //Verify bad input
				myAssert(getCost(-50000000) , -1, "Very low absurd input verified as bad input in getCost");
									
    return 0;
}
