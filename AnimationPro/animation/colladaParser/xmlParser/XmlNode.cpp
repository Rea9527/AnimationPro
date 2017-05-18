//
//  XmlNode.cpp
//  AnimationPro
//
//  Created by 陈主润 on 16/05/2017.
//  Copyright © 2017 陈主润. All rights reserved.
//

#include "XmlNode.hpp"


XmlNode::XmlNode() { }

XmlNode::XmlNode(string name) {
    this->name = name;
}

void XmlNode::addAttribute(string name, string attr) {
    this->attributes.insert(make_pair(name, attr));
}

void XmlNode::addChild(XmlNode child) {
    
    map<string, vector<XmlNode>>::iterator it = this->childNodes.find(child.getName());
    if (it != this->childNodes.end()) {
        it->second.push_back(child);
    } else {
        vector<XmlNode> childNode;
        childNode.push_back(child);
        this->childNodes.insert(make_pair(child.getName(), childNode));
    }
}

void XmlNode::setData(string data) {
    this->data = data;
}

string XmlNode::getName() {
    return this->name;
}

string XmlNode::getData() {
    return this->data;
}

string XmlNode::getAttribute(string name) {
    if (!this->attributes.empty()) {
        return this->attributes[name];
    } else {
        return NULL;
    }
}

XmlNode XmlNode::getChild(string name) {
    map<string, vector<XmlNode>>::iterator it = this->childNodes.find(name);
    if (it != this->childNodes.end()) {
        vector<XmlNode> nodes = this->childNodes[name];
        if (!nodes.empty()) {
            return nodes.front();
        }
    }
    return XmlNode();
}

XmlNode XmlNode::getChildWithAttrib(string childName, string name, string attr) {
    vector<XmlNode> children = getChildren(childName);
    if (children.empty()) {
        return XmlNode();
    } else {
        for (XmlNode child : children) {
            string _attr = child.getAttribute(name);
            if (_attr == attr) {
                return child;
            }
        }
    }
    return XmlNode();
}

vector<XmlNode> XmlNode::getChildren(string name) {
    map<string, vector<XmlNode>>::iterator it = this->childNodes.find(name);
    if (it != this->childNodes.end()) {
        return it->second;
    }
    return vector<XmlNode>();
}
