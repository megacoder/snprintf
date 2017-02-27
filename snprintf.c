/*
	vim: ts=8 sw=8
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <alloca.h>
#include <string.h>

#include <gcc-compat.h>

static char	msg[] = { "1234" };

static	void
process(
	char * const	title,
	size_t const	len
)
{
	size_t const	t_len = len + 1;
	char * const	text = alloca( t_len );
	size_t		needed;

	memset( text, 0, t_len );
	text[ t_len - 1 ] = 0x01;
	needed = snprintf( text, len, "%s", msg );
	printf(
		"%-12s\t%d=>%d\t%02X:%02X:%02X %s\t%s:%u\n",
		title,
		needed + 1,
		len,
		text[ t_len - 3 ] & 0xFF,	/* Last msg character	*/
		text[ t_len - 2 ] & 0xFF,	/* Should be a NULL	*/
		text[ t_len - 1 ] & 0xFF,	/* Should be the guard	*/
		(needed >= len) ? "BAD" : "ok",
		text,
		strlen( text )
	);
}

int
main(
	int		argc		_unused,
	char * *	argv		_unused
)
{
	size_t const		len = strlen( msg );

	process( "sizeof()",	sizeof( msg ) );
	process( "strlen()",	len );
	process( "strlen()-1",	len - 1 );
	process( "strlen()+1",	len + 1 );
	return( 0 );
}
