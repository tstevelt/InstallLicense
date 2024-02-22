/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"InstallLicense.h"

void ProcessDirectory ( char *Name, DIR *dir )
{
	struct dirent	*de;
	DIR				*child;
	char			FullName[1024];

	while (( de = readdir ( dir )) != NULL )
	{
		sprintf ( FullName, "%s/%s", Name, de->d_name );

		if ( de->d_type == DT_DIR )
		{
			if ( strcmp ( de->d_name, "." ) == 0 )
			{
				continue;
			}
			else if ( strcmp ( de->d_name, ".." ) == 0 )
			{
				continue;
			}

			if ( Debug )
			{
				printf ( "Directory: %s\n", FullName );
			}
			if (( child = opendir ( FullName )) == NULL )
			{
				perror("opendir");
			}
			ProcessDirectory ( FullName, child );
		}
		else
		{
			if ( Debug )
			{
				printf ( "File: %s\n", FullName );
			}
			ProcessFile ( FullName );
		}
	}

	closedir ( dir );
}
