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
	{ "NewYork", -5 },
	{ "Chicago", -6 },
	{ "Denver", -7 },
	{ "SanFrancisco", -8 },
	{ "London", 0 },
	{ "Paris", 1 },
	{ "Helsinki", 2 },
	{ "Beijing", 8 },
	{ NULL, 0 }
};

int main(int argc, const char * argv[])
{

    time_t		now=0, newtime=0;
    struct tm	*ts;
	tz_t		*p;
    char		buf[80];
	char		found=0;
	long		offset=0;
	char		city[80] = "Localtime";
	int			dst=0;
	
	/* Get the current time. */
    now = time(NULL);
	ts = localtime(&now);
	
	if (argc > 1)
	{
		for (p=table; p->name!=NULL; p++)
		{
			if (strcmp (p->name, argv[1]) == 0)
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
	
	/* modify the time according to timezone offset */
	

    /* Format and print the time, "ddd yyyy-mm-dd hh:mm:ss zzz" */
    printf ("%s: ", city);
	strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S\n", ts);
    puts(buf);
	
    return 0;
}

