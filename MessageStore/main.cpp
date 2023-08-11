
#include "MessageStore.h"

int main(int, const char* [])
{
	MessageStore store;
	
	while (store.ProcessInput() == false);
	
	store.Terminate();
	
	return 0;
}
