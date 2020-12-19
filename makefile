COMPILER=gcc
FILES=arbolesADT.c dataManagementADT.c
PARAMETERS=-fsanitize=address -g -Wall -pedantic -std=c99
DEBUG_COMPILER=-g -DDEBUG=1

all:
	gcc arbolesADTBUE.c -o arbolesADTBUE $(FILES) $(PARAMETERS)
	gcc arbolesADTVAN.c -o arbolesADTVAN $(FILES) $(PARAMETERS)

BUE:
	gcc arbolesADTBUE.c -o arbolesADTBUE $(FILES) $(PARAMETERS)

VAN:
	gcc arbolesADTVAN.c -o arbolesADTVAN $(FILES) $(PARAMETERS)

clean:
	rm -f arbolesADTBUE arbolesADTVAN
