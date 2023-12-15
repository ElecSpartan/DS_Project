#ifndef DS_PROJECT_XML_PARSER_H
#define DS_PROJECT_XML_PARSER_H
#include "Graph.h"
#include<fstream>
#include<stack>


void write_to_file(string address,string &content);
string read_file(string address);
bool temp_is_dummy(string &temp);
string trim(string&x);
vector<string> divide_string_for_graph(string &file);
vector<string> divide_string_for_correction(string &file);
Graph parse(string &file);
#endif
