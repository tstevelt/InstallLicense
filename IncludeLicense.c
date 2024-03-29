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

	switch ( FileType )
	{
		case FILE_TYPE_C:
			fprintf ( ofp, "/*---------------------------------------------------------------------------\n" );
			break;
	}

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

		switch ( FileType )
		{
			case FILE_TYPE_JS:
				fprintf ( ofp, "// " );
				break;
			case FILE_TYPE_CSS:
				TrimRight ( xbuffer );
				if ( strlen ( xbuffer ) == 0 )
				{
					continue;
				}
				fprintf ( ofp, "/* " );
				break;
			case FILE_TYPE_SH:
			case FILE_TYPE_PY:
				fprintf ( ofp, "# " );
				break;
			case FILE_TYPE_SQL:
				fprintf ( ofp, "-- " );
				break;
		}

		fprintf ( ofp, "%s", xbuffer );

		switch ( FileType )
		{
			case FILE_TYPE_CSS:
				fprintf ( ofp, " */\n" );
				break;
			case FILE_TYPE_C:
			case FILE_TYPE_JS:
			case FILE_TYPE_SH:
			case FILE_TYPE_PY:
			case FILE_TYPE_SQL:
				break;
		}

	}

	switch ( FileType )
	{
		case FILE_TYPE_C:
			fprintf ( ofp, "---------------------------------------------------------------------------*/\n" );
			break;
	}

	fclose ( ifp );
}
