CFLAGS = -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

MyUnitTest1: MyUnitTest1.c dominion.o rngs.o
	gcc -o MyUnitTest1 -g  MyUnitTest1.c dominion.o rngs.o $(CFLAGS)

testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
	gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)

AdventurerTest: cardtest1.c dominion.o rngs.o
	gcc -o AdventurerTest -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

SmithyTest: cardtest2.c dominion.o rngs.o
	gcc -o SmithyTest -g cardtest2.c dominion.o rngs.o $(CFLAGS)

VillageTest: cardtest3.c dominion.o rngs.o
	gcc -o VillageTest -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

CouncilRoomTest: cardtest4.c dominion.o rngs.o
	gcc -o CouncilRoomTest -g cardtest4.c dominion.o rngs.o $(CFLAGS)

scoreForUnitTest: unittest1.c dominion.o rngs.o
	gcc -o scoreForUnitTest -g unittest1.c dominion.o rngs.o $(CFLAGS)

fullDeckCountUnitTest: unittest2.c dominion.o rngs.o
	gcc -o fullDeckCountUnitTest -g unittest2.c dominion.o rngs.o $(CFLAGS)

getCostUnitTest: unittest3.c dominion.o rngs.o
	gcc -o getCostUnitTest -g unittest3.c dominion.o rngs.o $(CFLAGS)

numHandCardsUnitTest: unittest4.c dominion.o rngs.o
	gcc -o numHandCardsUnitTest -g unittest4.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	touch randomtestadventurer.out
	randomtestadventurer >> randomtestadventurer.out
	gcov dominion.c -b >> randomtestadventurer.out

randomtestsmithy: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestsmithy -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	touch randomtestcard1.out
	randomtestsmithy >> randomtestcard1.out
	gcov dominion.c -b >> randomtestcard1.out

randomtestvillage: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestvillage -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	touch randomtestcard2.out
	randomtestvillage >> randomtestcard2.out
	gcov dominion.c -b >> randomtestcard2.out

randomtestresults: randomtestadventurer randomtestsmithy randomtestvillage
	touch randomtestresults.out
	randomtestadventurer >> randomtestresults.out
	randomtestsmithy >> randomtestresults.out
	randomtestvillage >> randomtestresults.out
	gcov dominion.c -b >> randomtestresults.out

unittestresults: numHandCardsUnitTest getCostUnitTest fullDeckCountUnitTest scoreForUnitTest CouncilRoomTest VillageTest SmithyTest AdventurerTest dominion.o rngs.o
	touch unittestresults.out
	numHandCardsUnitTest >> unittestresults.out
	getCostUnitTest >> unittestresults.out
	fullDeckCountUnitTest >> unittestresults.out
	scoreForUnitTest >> unittestresults.out
	CouncilRoomTest >> unittestresults.out
	VillageTest >> unittestresults.out
	SmithyTest >> unittestresults.out
	AdventurerTest >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out


clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe MyUnitTest1 testUpdateCoins AdventurerTest SmithyTest VillageTest CouncilRoomTest scoreForUnitTest fullDeckCountUnitTest getCostUnitTest numHandCardsUnitTest randomtestadventurer randomtestsmithy randomtestvillage
