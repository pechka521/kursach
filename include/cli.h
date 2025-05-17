#ifndef CLI_H
#define CLI_H

#include "fixed_point.h"

void run_cli_interface(void);
void print_help(void);
int parse_fixed(const char *str, fixed_point *result);

#endif
