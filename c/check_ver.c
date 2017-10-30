#define _GNU_SOURCE
#include <gnu/libc-version.h>
#include <stdio.h>
int main (void) { puts (gnu_get_libc_version ()); return 0; }
