%{
#include <stdio.h>
%}

%%
"CREATE"           				printf("TARGET CREATE\n");
"TABLE"           				printf("TARGET TABLE\n");
"SHOW CREATE TABLE"           	printf("TARGET SHOW CREATE\n");
%%