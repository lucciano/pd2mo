#include <stdio.h>
#include <libgen.h>
char * getFullPath(){
char szTmp[320];
char pBuf[320];
int len = 320;
sprintf(szTmp, "/proc/%d/exe", getpid());
int bytes = readlink(szTmp, pBuf, len);
if(bytes >= 0)
	pBuf[bytes] = '\0';
return dirname(pBuf);
}

