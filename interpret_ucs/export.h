/*
 * export.h
 *
 *  Created on: Feb 6, 2015
 *      Author: nbingham
 */

#include <common/standard.h>

#include <ucs/variable.h>
#include <parse_ucs/variable_name.h>

#ifndef interpret_ucs_export_h
#define interpret_ucs_export_h

parse_ucs::slice export_slice(int lb, int ub);
parse_ucs::member_name export_member_name(ucs::instance instance);
parse_ucs::variable_name export_variable_name(ucs::variable variable);
parse_ucs::variable_name export_variable_name(int variable, const ucs::variable_set &variables);
vector<parse_ucs::variable_name> export_variable_names(const ucs::variable_set &variables);

#endif
