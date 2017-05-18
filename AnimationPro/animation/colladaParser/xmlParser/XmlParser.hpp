//
//  XmlParser.hpp
//  AnimationPro
//
//  Created by 陈主润 on 16/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#ifndef XmlParser_hpp
#define XmlParser_hpp

#include <iostream>
#include <fstream>
#include <sstream>

#include "XmlNode.hpp"

class XmlParser {
    
public:
    XmlParser();
    
    static XmlNode loadXmlFile(string path);
    
    static XmlNode loadNode();
    
    static void addData();
    
    static void addAttributes(string titleParts[], XmlNode node);
    
    static void addAttribute(string attribLine, XmlNode node);
    
    static string getStartTag(string line);
    
private:
    static ifstream file;

};

#endif /* XmlParser_hpp */
