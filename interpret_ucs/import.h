/*
 * import.h
 *
 *  Created on: Feb 6, 2015
 *      Author: nbingham
 */

#include <common/standard.h>

#include <ucs/variable.h>
#include <parse_ucs/variable_name.h>

#ifndef interpret_ucs_import_h
#define interpret_ucs_import_h

vector<ucs::instance> import_instances(const parse_ucs::member_name &syntax, tokenizer *tokens);
vector<ucs::variable> import_variables(const parse_ucs::variable_name &syntax, int default_id, tokenizer *tokens);

vector<int> define_variables(const parse_ucs::variable_name &syntax, ucs::variable_set &variables, int default_id, tokenizer *tokens, bool define = false, bool squash_errors = false);

#endif
