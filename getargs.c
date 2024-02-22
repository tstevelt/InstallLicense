/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"InstallLicense.h"

static void Usage ()
{
	printf ( "\nInstall open source licensing in all .c and .h files in directory tree.\n" );
	printf ( "Original files are renamed with .bak extension.  Existing .bak files (if any)\n" );
	printf ( "are silently over-written. Due caution is recommended.\n\n" );
	printf ( "USAGE: InstallLicense directory license year name email [options]\n" );
	printf ( " license - PD, MIT or AGPL\n" );
	printf ( " year    - copyright year[s]. use single quotes if necessary\n" );
	printf ( " name    - copyright holder[s]. use single quotes if necessary\n" );
	printf ( "Options\n" );
	printf ( " -p xxx  - program name and description, used by some licenses\n" );
	printf ( " -d      - debug\n" );
	printf ( "\n" );
	exit ( 1 );
}

void getargs ( int argc, char *argv[] )
{
	struct	stat	sb;
	if ( argc < 6 )
	{
		Usage ();
	}

	Directory       = argv[1];
	License         = argv[2];
	CopyrightYear   = argv[3];
	CopyrightHolder = argv[4];
	CopyrightEmail  = argv[5];
	ProgramNameAndDescription = NULL;

	for ( int xa = 6; xa < argc; xa++ )
	{
		if ( xa + 1 < argc && strcmp ( argv[xa], "-p" ) == 0 )
		{
			xa++;
			ProgramNameAndDescription = argv[xa];
		}
		else if ( strcmp ( argv[xa], "-d" ) == 0 )
		{
			Debug = 1;
		}
		else
		{
			Usage ();
		}
	}

	if ( lstat ( argv[1], &sb ) == -1 )
	{
		perror ( "lstat" );
		exit ( 1 );
	}

	switch (sb.st_mode & S_IFMT) 
	{
		case S_IFDIR:
			break;

		case S_IFLNK:
			printf ( "%s is symbolic link. Use a real directory\n", Directory );
			exit ( 1 );

		case S_IFBLK:
		case S_IFCHR:
		case S_IFIFO:
		case S_IFREG:
		case S_IFSOCK:
		default:
			printf ( "%s is not a directory\n", Directory );
			exit ( 1 );
	}

	if ( strcmp ( License, "PD" ) == 0 )
	{
		LicenseType = LICENSE_PD;
	}
	else if ( strcmp ( License, "MIT" ) == 0 )
	{
		LicenseType = LICENSE_MIT;
	}
	else if ( strcmp ( License, "AGPL" ) == 0 )
	{
		LicenseType = LICENSE_AGPL;
	}
	else
	{
		printf ( "Unknown license\n" );
		exit ( 1 );
	}
}
