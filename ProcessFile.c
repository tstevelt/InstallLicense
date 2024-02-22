/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"InstallLicense.h"

void ProcessFile ( char *FileName )
{
	int		xl, xi, xf;
	FILE	*sfp, *dfp;
	char	xbuffer[10240];
	char	bfn[1024];

	xl = strlen ( FileName );

	if ( strncmp ( &FileName[xl-2], ".c", 2 ) == 0 || strncmp ( &FileName[xl-2], ".h", 2 ) == 0 )
	{
		printf ( "Processing: %s\n", FileName );
		FileCount++;
	}
	else
	{
		return;
	}

	sprintf ( bfn, "%s.bak", FileName );
	rename ( FileName, bfn );

	if (( sfp = fopen ( bfn, "r" )) == NULL )
	{
		fprintf ( stderr, "Cannot open %s for reading, error %s\n", bfn, strerror(errno) );
		return;
	}

	if (( dfp = fopen ( FileName, "w" )) == NULL )
	{
		fprintf ( stderr, "Cannot create %s for output, error %s\n", FileName, strerror(errno) );
		return;
	}

	if ( fgets ( xbuffer, sizeof(xbuffer), sfp ) == NULL )
	{
		fprintf ( stderr, "Cannot read first line of %s\n", FileName );
		fclose ( sfp );
		return;
	}

	rewind ( sfp );
	if ( strncmp ( xbuffer, "/*", 2 ) == 0 )
	{
		if ( Debug )
		{
			printf ( "  skipping inital comment\n" );
		}

		xf = 0;
		while ( xf == 0 && fgets ( xbuffer, sizeof(xbuffer), sfp ) != NULL )
		{
			xl = strlen ( xbuffer );
			fprintf ( dfp, "%s", xbuffer );
			for ( xi = 0; xi < xl; xi++ )
			{
				if ( strncmp ( &xbuffer[xi], "*/", 2 ) == 0 )
				{
					xf = 1;
					break;
				}
			}
		}
	}

	IncludeLicense ( dfp );

	while ( fgets ( xbuffer, sizeof(xbuffer), sfp ) != NULL )
	{
		fprintf ( dfp, "%s", xbuffer );
	}
	
	fclose ( sfp );
	fclose ( dfp );
}
