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

static char	msg[] = { "12345678901234567890" };

static	void
process(
	char * const	title,
	size_t const	len
)
{
	size_t const	t_len = len + 2;
	char * const	text = alloca( t_len );
	size_t		needed;

	memset( text, 0, t_len );
	needed = snprintf( text, len, "%s", msg );
	printf(
		"%-12s %d\t%d\t%02X:%02X:%02X:%02X %s\t%s\n",
		title,
		needed,
		len,
		text[ t_len - 4 ] & 0xFF,
		text[ t_len - 3 ] & 0xFF,
		text[ t_len - 2 ] & 0xFF,
		text[ t_len - 1 ] & 0xFF,
		(needed > len) ? "BAD" : "ok",
		text
	);
}

int
main(
	int		argc		_unused,
	char * *	argv		_unused
)
{
	size_t const		len = strlen( msg );

	process( "Original",	sizeof( msg ) );
	process( "Exact",	len );
	process( "Shorter",	len - 2 );
	process( "Longer",	len + 2 );
	return( 0 );
}
