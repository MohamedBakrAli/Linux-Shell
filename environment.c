#include "environment.h"
#include "variables.h"
#include <stdio.h>
#include <stdlib.h>

void setup_environment( void )
{
    project_path = getenv("PWD");
    home_path = getenv("HOME");
}
