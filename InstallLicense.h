/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<dirent.h>
#include	<errno.h>

#include	"shslib.h"

#ifdef MAIN
#define		TYPE	/* */
#else
#define		TYPE	extern
#endif

TYPE	int		Debug;
TYPE	char	*Directory;
TYPE	char	*License;
TYPE	char	*CopyrightYear;
TYPE	char	*CopyrightHolder;
TYPE	char	*CopyrightEmail;
TYPE	char	*ProgramNameAndDescription;
TYPE	int		FileCount;

TYPE	int		LicenseType;
#define		LICENSE_PD		1
#define		LICENSE_MIT		2
#define		LICENSE_AGPL	3

TYPE	char	ifn[1024], sfn[1024], dfn[1024], nfn[1024];

#define		FILE_TYPE_C		1
#define		FILE_TYPE_JS	2
#define		FILE_TYPE_CSS	3
#define		FILE_TYPE_SH	4
#define		FILE_TYPE_SQL	5

TYPE	int	FileType;

/*----------------------------
:.,$d
:r ! mkproto -p *.c
----------------------------*/

/* getargs.c */
void getargs ( int argc , char *argv []);

/* IncludeLicense.c */
void IncludeLicense ( FILE *ofp );

/* InstallLicense.c */
int main ( int argc , char *argv []);

/* MainLicense.c */
void MainLicense ( char *Directory );

/* ProcessDirectory.c */
void ProcessDirectory ( char *Name , DIR *dir );

/* ProcessFile.c */
void ProcessFile ( char *FileName );
