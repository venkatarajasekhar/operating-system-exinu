#include <prodcons.h>
#include <stdlib.h>

void producer(int count)
{
    //Code to produce values less than equal to count, 
    //produced value should get assigned to global variable 'n'.
    //print produced value e.g. produced : 8
/*    srand(time(NULL));
    while(true)
    {
	n = rand() % count;
	printf("produced: %d", n);
    }
*/
    int i;
    for (i = 0; i < count; i++)
    {
	wait(consumed);
	n = i;
	printf("produced: %d\n", n);
	signal(produced);
    }
}
