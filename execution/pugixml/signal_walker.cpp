#include "signal_walker.h"
#include <iostream>

bool signal_walker::for_each(pugi::xml_node& node)
{
	std::string targetName1 = "signal";
	std::string targetName2 = "insignal";
	std::string targetName3 = "outsignal";
	const char* nodeName = node.name();
	if (nodeName == targetName1 || nodeName == targetName2 || nodeName == targetName3)
	{
		//std::cout << depth() << ":" << node.name() << std::endl;
		pugi::xml_attribute attrName = node.attribute("name"); //this returns a attribute
		//object that's constructed using a pointer to the node's attribute, which means 
		//changes made using the 'attrParameter' variable will take effect within the original node
		std::string oldName = signalInfo.oldName;
		if (attrName.value() == oldName)
		{
            attrName.set_value(signalInfo.newName.c_str());
            std::cout << "new name:" << node.attribute("name").value() << std::endl;
            sig_num++;
        }
	}
	
	return true;
}


void signal_walker::setSigInfo(std::string oldName, std::string newName)
{
	signalInfo.oldName = oldName;
	signalInfo.newName = newName;
}
