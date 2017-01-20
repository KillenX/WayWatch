#include <iostream>
#include "WWExit.h"
#include "../common/Login.h"

void main()
{
	Login::tryLogin();

	WWExit app;

	app.run();
}