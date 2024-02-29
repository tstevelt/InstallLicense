/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"InstallLicense.h"

static void CheckFile ( char *Base )
{
	sprintf ( sfn, "%s/%s_LICENSE", LICENSE_DIRECTORY, Base );
	if ( access ( sfn, R_OK ) != 0 )
	{
		fprintf ( stderr, "Cannot find main license %s\n", sfn );
		exit ( 1 );
	}

	sprintf ( ifn, "%s/%s_INCLUDE", LICENSE_DIRECTORY, Base );
	if ( access ( ifn, R_OK ) != 0 )
	{
		fprintf ( stderr, "Cannot find include license %s\n", ifn );
		exit ( 1 );
	}
}


void MainLicense ( char *Directory )
{
	FILE	*sfp, *dfp;
	char	xbuffer[1024];
	char	*cp;

	/*----------------------------------------------------------
		first make sure we have both main and include
	----------------------------------------------------------*/
	switch ( LicenseType )
	{
		case LICENSE_PD:
			CheckFile ( "PD" );
			break;

		case LICENSE_MIT:
			CheckFile ( "MIT" );
			break;

		case LICENSE_AGPL:
			CheckFile ( "AGPL" );
			break;
	}

	sprintf ( dfn, "%s/LICENSE", Directory );
	if ( access ( dfn, F_OK ) == 0 )
	{
		printf ( "%s exists, renaming\n", dfn );
		sprintf ( nfn, "%s/LICENSE.old", Directory );
		rename ( dfn, nfn );
	}

	sfp = fopen ( sfn, "r" );
	dfp = fopen ( dfn, "w" );

	while ( fgets ( xbuffer, sizeof(xbuffer), sfp ) != NULL )
	{
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

		fprintf ( dfp, "%s", xbuffer );
	}

	fclose ( sfp );
	fclose ( dfp );
}
