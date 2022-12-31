#include<iostream>
#include<fstream>
#include<string>
#include <nlohmann/json.hpp>
#include "bvh_parser.h"
#include "json.hpp"

using namespace std;
using json=nlohmann::json; 


void jsonify(joint root, META meta_data) {
    ofstream outfile;
    outfile.open("output.json");
    
    //create and define the JSON object
    json js; 

    js["name"]=root.name;
    js["type"]=root.joint_type;
    js["offset_x"]=root.offset_x;
    js["offset_y"]=root.offset_y;
    js["offset_z"]=root.offset_z;
    js["channels"]=root.channels;

    //create a JSON array for the children of the joint
    json jchild=json::array();
    for(auto &child:root.children){
        jsonify(*child,meta_data);
        jchild.push_back(*child);
    }
    js["children"]=jchild;

    //serialize the object into a JSON string
    string js_str=js.dump();

    // output the root and meta_data
    if(!outfile.is_open()){
        cout<<"Error opening file for writing!"<<endl;
        return 1;
    }
    else outfile<<js_str<<endl;
    
    outfile.close();
}