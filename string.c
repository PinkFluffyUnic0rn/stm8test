#include "string.h"

size_t strlen(const char *s)
{
	size_t l;

	for (l = 0; s[l] != '\0'; ++l);

	return l;
}

void uint16toa(uint16_t i, char *s, int len)
{
	int e;
	int p;
	char *sp;

	sp = s;
	e = 10000;
	for (p = 0; p < 5; ++p) {
		if (!(i / e == 0 && sp == s))
			*sp++ = '0' + (i / e);

		i %= e;
		e /= 10;
	}

	if (sp == s)
		*sp++ = '0';

	*sp++ = '\0';
}

void int16toa(int16_t i, char *s, int len)
{
	int e;
	int p;
	char *sp;
	
	sp = s;

	if (i < 0) {
		i = -i;
		*sp++ = '-';
	}

	e = 10000;
	for (p = 0; p < 5; ++p) {
		if (!(i / e == 0 && (sp == s || *(sp - 1) == '-')))
			*sp++ = '0' + (i / e);

		i %= e;
		e /= 10;
	}

	if (sp == s)
		*sp++ = '0';

	*sp++ = '\0';
}

void uint32toa(uint32_t i, char *s, int len)
{
	uint32_t e;
	int p;
	char *sp;

	sp = s;
	e = 1000000000;
	for (p = 0; p < 10; ++p) {
		if (!(i / e == 0 && sp == s))
			*sp++ = '0' + (i / e);

		i %= e;
		e /= 10;
	}

	if (sp == s)
		*sp++ = '0';

	*sp++ = '\0';
}

void memset(void *s, int c, size_t n)
{
	int i;

	for (i = 0; i < n; ++i)
		((uint8_t *) s)[i] = c;
}
