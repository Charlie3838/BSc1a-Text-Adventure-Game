#include "PlayerInfo.h"
#include <string>


PlayerInfo::PlayerInfo(string _name, int _age) {
	this->name = _name;
	this->age = _age;
}
PlayerInfo::PlayerInfo(string _name, int _age, string _favColour) {
	this->name = _name;
	this->age = _age;
	this->favColour = _favColour;
}

