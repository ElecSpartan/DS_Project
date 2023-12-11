#include "XML_Parser.h"


bool detection_function(string address){
    string detected_file = read_file(address);
    int opened_tag = 0;
    int closed_tag = 0;
    for(int i=0;i<detected_file.size();i++){
        if(detected_file[i]=='<'){
            if(detected_file[i+1]=='/')
                closed_tag ++;
            else
                opened_tag++;
        }
        if(closed_tag > opened_tag)
            return false;
    }
    if(closed_tag != opened_tag)
        return false;

    stack<string> name_check;

    for(int i=0;i<detected_file.size();i++){
        if(detected_file[i]=='<'){
            if(detected_file[i+1]=='/'){
                string tag = "</";
                for(int j = i+2;j<detected_file.size();j++){
                    tag.push_back(detected_file[j]);
                    if(detected_file[j]=='>')
                        break;
                }
                if(name_check.empty() || name_check.top().substr(1,name_check.top().size()-2) != tag.substr(2,tag.size()-3))
                    return false;
                name_check.pop();
            }
            else{
                string tag = "<";
                for(int j=i+1;j<detected_file.size();j++){
                    tag.push_back(detected_file[j]);
                    if(detected_file[j]=='>')
                        break;
                }
                name_check.push(tag);
            }
        }
    }

    if(!name_check.empty())
        return false;


    return true;
}