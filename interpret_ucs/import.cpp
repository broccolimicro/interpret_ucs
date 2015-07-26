/*
 * import.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: nbingham
 */

#include "import.h"

// parse_ucs::variable_name
vector<ucs::instance> import_instances(const parse_ucs::member_name &syntax, tokenizer *tokens)
{
	vector<ucs::instance> result;
	result.push_back(ucs::instance());
	result.back().name = syntax.name;
	for (int i = 0; i < (int)syntax.slices.size(); i++)
	{
		int lb = atoi(syntax.slices[i].lower.c_str());
		int ub = atoi(syntax.slices[i].upper.c_str());

		int count = (int)result.size()-1;
		for (int j = count; j >= 0; j--)
			for (int k = lb; k < ub; k++)
			{
				result.push_back(result[j]);
				result.back().slice.push_back(k);
			}

		for (int j = count; j >= 0; j--)
			result[j].slice.push_back(ub);
	}
	return result;
}

vector<ucs::variable> import_variables(const parse_ucs::variable_name &syntax, int default_id, tokenizer *tokens)
{
	vector<ucs::variable> result(1, ucs::variable());
	result.back().region = default_id;
	if (syntax.region != "")
		result.back().region = atoi(syntax.region.c_str());

	for (int i = 0; i < (int)syntax.names.size(); i++)
	{
		vector<ucs::instance> instances = import_instances(syntax.names[i], tokens);

		int count = (int)result.size()-1;
		for (int j = count; j >= 0; j--)
			for (int k = 0; k < (int)instances.size()-1; k++)
			{
				result.push_back(result[j]);
				result.back().name.push_back(instances[k]);
			}

		for (int j = count; j >= 0; j--)
			result[j].name.push_back(instances.back());
	}

	return result;
}

vector<int> define_variables(const parse_ucs::variable_name &syntax, ucs::variable_set &variables, int default_id, tokenizer *tokens, bool define, bool squash_errors)
{
	vector<ucs::variable> v = import_variables(syntax, default_id, tokens);
	vector<int> result;
	for (int i = 0; i < (int)v.size(); i++)
	{
		if (define)
		{
			result.push_back(variables.define(v[i]));
			if (result.back() == -1 && !squash_errors)
			{
				if (tokens != NULL)
				{
					tokens->load(&syntax);
					tokens->error("redefinition of variable '" + v[i].to_string() + "'", __FILE__, __LINE__);
					if (tokens->load(syntax.to_string()))
						tokens->note("previously defined here", __FILE__, __LINE__);
				}
				else
					error("", "redefinition of variable '" + v[i].to_string() + "'", __FILE__, __LINE__);
			}
			else if (result.back() == -1 && squash_errors)
				result.back() = variables.find(v[i]);
			else if (tokens != NULL)
				tokens->save(syntax.to_string(), &syntax);
		}
		else
		{
			result.push_back(variables.find(v[i]));

			if (result.back() == -1 && !squash_errors)
			{
				if (tokens != NULL)
				{
					tokens->load(&syntax);
					tokens->error("variable '" + v[i].to_string() + "' not yet defined", __FILE__, __LINE__);
				}
				else
					error("", "variable '" + v[i].to_string() + "' not yet defined", __FILE__, __LINE__);
			}
			else if (result.back() == -1 && squash_errors)
			{
				result.back() = variables.define(v[i]);
				if (tokens != NULL)
					tokens->save(syntax.to_string(), &syntax);
			}
		}
	}
	return result;
}


