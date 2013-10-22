//
//  main.c
//  worldtime
//
//  Created by John Macdonald on 10/17/13.
//  Copyright (c) 2013 John Macdonald. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <time.h>

// Globals
typedef struct
{
	const char *name;
	int offset;
} tz_t;

static const tz_t table[] =
{
	{ "washington" , -5 },
	{ "philadelphia", -5 },
	{ "newyork", -5 },
	{ "chicago", -6 },
	{ "denver", -7 },
	{ "sanfrancisco", -8 },
	{ "london", 0 },
	{ "paris", 1 },
	{ "helsinki", 2 },
	{ "beijing", 8 },
	{ NULL, 0 }
};

int main(int argc, const char * argv[])
{

    time_t		now=0, newtime=0;
    struct tm	*ts;
	const tz_t	*p;
	char		input[30];
    char		buf[80];
	char		city[80] = "Localtime";
	char		found=0;
	long		offset=0;
	int			dst=0;
	int			i=0;
	
	/* Get the current time. */
    now = time(NULL);
	ts = localtime(&now);
	
	if (argc > 1)
	{
		/* convert input to all lower case */
		strcpy (input, argv[1]);
		for (i=0; i<=strlen(input); i++)
		{
			if (input[i]>=65 && input[i]<=90)
				input[i] = input[i] + 32;
		}
		
		for (p=table; p->name!=NULL; p++)
		{
			if (strcmp (p->name, input) == 0)
			{
				found = 1;
				if (ts->tm_isdst == 1)
					dst = 1;
				offset = (p->offset + dst) * 3600;
				newtime = now + offset;
				ts = gmtime(&newtime);
				strcpy (city, argv[1]);
				break;
			}
		}
		if (found == 0)
		{
			printf ("Error: City not found in db\n");
		}
	}
	
    /* Format and print the time, "ddd yyyy-mm-dd hh:mm:ss zzz" */
    printf ("%s: ", city);
	strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S\n", ts);
    puts(buf);
	
    return 0;
}

