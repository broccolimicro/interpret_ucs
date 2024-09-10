/*
 * export.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: nbingham
 */

#include "export.h"
#include "import.h"

parse_ucs::slice export_slice(int lb, int ub)
{
	parse_ucs::slice result;
	result.valid = true;
	result.lower = ::to_string(lb);
	result.upper = ::to_string(ub);
	return result;
}

parse_ucs::member_name export_member_name(ucs::instance instance)
{
	parse_ucs::member_name result;
	result.valid = true;
	result.name = instance.name;
	for (int i = 0; i < (int)instance.slice.size(); i++)
		result.slices.push_back(export_slice(instance.slice[i], instance.slice[i]));
	return result;
}

parse_ucs::variable_name export_variable_name(ucs::variable variable)
{
	parse_ucs::variable_name result;
	result.valid = true;
	for (int i = 0; i < (int)variable.name.size(); i++)
		result.names.push_back(export_member_name(variable.name[i]));
	result.region = ::to_string(variable.region);
	return result;
}

parse_ucs::variable_name export_variable_name(int variable, const ucs::variable_set &variables)
{
	parse_ucs::variable_name result;
	if (variable >= 0 && variable < (int)variables.nodes.size()) {
		result = export_variable_name(variables.nodes[variable]);
	} else if (variable < 0) {
		result = export_variable_name(ucs::variable("#"+to_string(-variable-1)));
	}
	return result;
}

vector<parse_ucs::variable_name> export_variable_names(const ucs::variable_set &variables)
{
	vector<parse_ucs::variable_name> result;

	for (int i = 0; i < (int)variables.nodes.size(); i++)
		result.push_back(export_variable_name(i, variables));

	return result;
}

