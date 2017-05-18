//
//  XmlParser.cpp
//  AnimationPro
//
//  Created by 陈主润 on 16/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "XmlParser.hpp"


XmlParser::XmlParser() {
    
}

XmlNode XmlParser::loadXmlFile(string path) {
    file.open(path.c_str(), std::ios::in);
    string row;
    getline(file, row);
    XmlNode node = loadNode();
    
    return node;
}

XmlNode XmlParser::loadNode() {
    string line;
    getline(file, line);
    
}
