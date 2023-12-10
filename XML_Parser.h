#ifndef DS_PROJECT_XML_PARSER_H
#define DS_PROJECT_XML_PARSER_H
#include "Graph.h"
#include<fstream>
#include<stack>

void write_to_file(string& address,string &content);
pair<string,Graph>  parsing_with_correcting_errors(string address,vector<int>&line_num_error);
string readFile(string address);
string trim(string x);


#endif
