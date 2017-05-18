//
//  XmlNode.hpp
//  AnimationPro
//
//  Created by 陈主润 on 16/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef XmlNode_hpp
#define XmlNode_hpp

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;


class XmlNode {
    
public:
    XmlNode();
    XmlNode(string name);
    
    void addAttribute(string name, string attr);
    void addChild(XmlNode child);
    
    void setData(string data);
    string getData();
    
    string getName();
    string getAttribute(string name);
    XmlNode getChild(string name);
    XmlNode getChildWithAttrib(string childName, string name, string attr);
    vector<XmlNode> getChildren(string name);
    
private:
    string name;
    
    map<string, string> attributes;
    
    string data;
    
    map<string, vector<XmlNode>> childNodes;
};

#endif /* XmlNode_hpp */
