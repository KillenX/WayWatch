#include <iostream>
#include "WWExit.h"
#include "../common/Login.h"

int main()
{
	Login::tryLogin();

	WWExit app;

	app.run();
}
