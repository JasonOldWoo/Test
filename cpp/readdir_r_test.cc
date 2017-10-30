#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	struct stat st;
	struct dirent entry;
	struct dirent* pResult = NULL;
	DIR* pDir = opendir("./");
	if (!pDir) exit(1);
	while (!readdir_r(pDir, &entry, &pResult) && pResult) {
		std::cout << entry.d_name << '\n';
		std::cout << stat(entry.d_name, &st) << '\n';
	}
	closedir(pDir);
	return 0;
}
