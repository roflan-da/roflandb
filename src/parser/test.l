%{
#include <stdio.h>
%}

%%
CREATE           				return CREATE;
TABLE           				return TABLE\n;
SHOW CREATE TABLE           	return TARGET SHOW CREATE;
%%