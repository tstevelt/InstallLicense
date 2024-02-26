/*----------------------------------------------------------------------------
	Program : InstallLicense.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Feb 2024
	Synopsis: Install license in source code tree.  Rewrite .c and .h files
	Return  : 

	Todo    : test everything for symbolic link.

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		02/24/2024	Added .sh, .js, .css and .sql files
	tms		02/26/2024	Added .py

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#define		MAIN
#include	"InstallLicense.h"

int main ( int argc, char *argv[] )
{
	DIR		*topdir;

	getargs ( argc, argv );

	MainLicense ( Directory );

	if (( topdir = opendir ( Directory )) == NULL )
	{
		perror("opendir");
	}

	ProcessDirectory ( Directory, topdir );

	printf ( "%d files\n", FileCount );

	return ( 0 );
}
