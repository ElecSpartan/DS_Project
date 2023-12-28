#ifndef DS_PROJECT_XML_PARSER_H
#define DS_PROJECT_XML_PARSER_H
#include "Graph.h"
#include<fstream>
#include<stack>
int num_of_new_lines(string &x);
void write_to_file(string address,string content);
string read_file(string address);
bool temp_is_dummy(string &temp);
string trim(string&x);
vector<string> divide_string_for_graph(string &file);
pair<vector<string>,int>  divide_string_for_correction(string &file);
Graph parse(string &file);
void visualize_graph(Graph &g);
#endif
