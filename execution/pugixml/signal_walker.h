#pragma once
#include "pugixml.hpp"
class signal_walker : public pugi::xml_tree_walker
{
public:
	virtual bool for_each(pugi::xml_node& node) override;


	//old-new signal pair
	struct sig_info 
	{
		std::string oldName;
		std::string newName;
	};

	sig_info signalInfo;
	void setSigInfo(std::string oldName, std::string newName);
	int sig_num = 0;
};

