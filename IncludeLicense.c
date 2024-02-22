/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"InstallLicense.h"

void IncludeLicense ( FILE *ofp )
{
	FILE	*ifp;
	char	xbuffer[1024];
	char	*cp;

	ifp = fopen ( ifn, "r" );

	while ( fgets ( xbuffer, sizeof(xbuffer), ifp ) != NULL )
	{
		if ( strstr ( xbuffer, "PROGRAM_NAME_AND_DESCRIPTION" ) != NULL )
		{
			cp = shsSearchAndReplace ( xbuffer, "PROGRAM_NAME_AND_DESCRIPTION", ProgramNameAndDescription );
			sprintf ( xbuffer, "%s", cp );
		}

		if ( strstr ( xbuffer, "COPYRIGHT_YEAR" ) != NULL )
		{
			cp = shsSearchAndReplace ( xbuffer, "COPYRIGHT_YEAR", CopyrightYear );
			sprintf ( xbuffer, "%s", cp );
		}

		if ( strstr ( xbuffer, "COPYRIGHT_HOLDER" ) != NULL )
		{
			cp = shsSearchAndReplace ( xbuffer, "COPYRIGHT_HOLDER", CopyrightHolder );
			sprintf ( xbuffer, "%s", cp );
		}

		if ( strstr ( xbuffer, "COPYRIGHT_EMAIL" ) != NULL )
		{
			cp = shsSearchAndReplace ( xbuffer, "COPYRIGHT_EMAIL", CopyrightEmail );
			sprintf ( xbuffer, "%s", cp );
		}

		fprintf ( ofp, "%s", xbuffer );
	}

	fclose ( ifp );
}
