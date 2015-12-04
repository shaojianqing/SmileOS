#include "../const/const.h"
#include "../type/type.h"
#include "../execute/systemApi.h"

int cata = 88;

int data = 11;

void initApplication()
{	
	int a = firstApi(0xff8822);
	
	while(TRUE) {
		a++;
	}
}
