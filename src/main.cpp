#include <stdio.h>
#include "app.h"

int main(int argc, char** argv) {
	struct app *app = NULL;
	
	app = app_create();
	app_run(app);
	app_destroy(app);
	
	return 0;
}



