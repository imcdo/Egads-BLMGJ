#include "monsterData.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

// Element Singleton BS

static string NormalString = "Normal";
static string FlameString = "Flame";
static string WaterString = "Water";
static string NatureString = "Nature";
static string AbyssalString = "Abyssal";

static Normal* NormalType = nullptr;
Normal* Normal::GetNormal()
{
	if (NormalType == nullptr)
	{
		NormalType = new Normal();
	}
	return NormalType;
}

static Flame* FlameType = nullptr;
Flame* Flame::GetFlame()
{
	if (FlameType == nullptr)
	{
		FlameType = new Flame();
	}
	return FlameType;
}

static Water* WaterType = nullptr;
Water* Water::GetWater()
{
	if (WaterType == nullptr)
	{
		WaterType = new Water();
	}
	return WaterType;
}

static Nature* NatureType = nullptr;
Nature* Nature::GetNature()
{
	if (NatureType == nullptr)
	{
		NatureType = new Nature();
	}
	return NatureType;
}

static Abyssal* AbyssalType = nullptr;
Abyssal* Abyssal::GetAbyssal()
{
	if (AbyssalType == nullptr)
	{
		AbyssalType = new Abyssal();
	}
	return AbyssalType;
}

Normal::Normal()
{}

float Normal::GetDamageMultiplierAgainst(static Element* otherElement)
{
	return NEUTRAL;
}

settings::ELEMENTS Normal::GetElementEnum()
{
	return settings::NORMAL;
}

Water::Water()
{
}

float Water::GetDamageMultiplierAgainst(static Element* otherElement)
{
	if (otherElement == Flame::GetFlame())
		return SUPER_EFFECTIVE;
	else if (otherElement == Nature::GetNature())
		return RESISTANT;
	else
		return NEUTRAL;
}

settings::ELEMENTS Water::GetElementEnum()
{
	return settings::WATER;
}

Nature::Nature()
{
}

float Nature::GetDamageMultiplierAgainst(static Element* otherElement)
{
	if (otherElement == Water::GetWater())
		return SUPER_EFFECTIVE;
	else if (otherElement == Flame::GetFlame())
		return RESISTANT;
	else
		return NEUTRAL;
}

settings::ELEMENTS Nature::GetElementEnum()
{
	return settings::NATURE;
}

Flame::Flame()
{
}

float Flame::GetDamageMultiplierAgainst(static Element* otherElement)
{
	if (otherElement == Nature::GetNature())
		return SUPER_EFFECTIVE;
	else if (otherElement == Water::GetWater())
		return RESISTANT;
	else
		return NEUTRAL;
}

settings::ELEMENTS Flame::GetElementEnum()
{
	return settings::FLAME;
}

Abyssal::Abyssal()
{
}

float Abyssal::GetDamageMultiplierAgainst(static Element* otherElement)
{
	if (otherElement == GetAbyssal())
		return SUPER_EFFECTIVE;
	else if (otherElement == Normal::GetNormal())
		return RESISTANT;
	else
		return NEUTRAL;
}

settings::ELEMENTS Abyssal::GetElementEnum()
{
	return settings::ABYSSAL;
}

// Monster card tracking and JSON interface

MonsterData::MonsterData(Element* e) : element(e)
{}

MonsterData::MonsterData(nlohmann::json json) :
	id(stoi(json["id"].get<string>())),
	rank(json["rank"].get<int>()),
	name(json["name"].get<string>()),
	species(json["species"].get<string>()),
	sprite(json["sprite"].get<string>()),
	health(json["hp"].get<int>()),
	damage(json["attack"].get<int>()),
	decay(json["decay"].get<int>()),
	bounce(json["bounce"].get<int>())
{
	if (json["size"].get<string>().compare("boss") == 0)
	{
		size = 1;
	}
	else
	{
		size = 0;
	}

	string typeString = json["element"].get<string>();
	if (NormalString.compare(typeString) == 0)
	{
		element = Normal::GetNormal();
	}
	else if (FlameString.compare(typeString) == 0)
	{
		element = Flame::GetFlame();
	}
	else if (WaterString.compare(typeString) == 0)
	{
		element = Water::GetWater();
	}
	else if (NatureString.compare(typeString) == 0)
	{
		element = Nature::GetNature();
	}
	else if (AbyssalString.compare(typeString) == 0)
	{
		element = Abyssal::GetAbyssal();
	}
	else
	{
		cout << "ERROR :: Couldn't read element. Setting to NORMAL. " << NatureString.compare(typeString) << endl;
		element = Normal::GetNormal();
	}
}

ostream& operator<<(ostream& strm, const MonsterData& m)
{
	return strm <<
		m.id << " -- " <<
		m.name <<
		"(" << m.species << ")" <<
		"[" << m.health << ","
		<< m.damage << ","
		<< m.decay << ","
		<< m.bounce << "]\t"
		<< m.sprite;
}

ostream& operator<<(ostream& strm, const Element* e)
{
	string ret = "";
	if (e == Flame::GetFlame())
		return strm << FlameString;
	else if (e == Water::GetWater())
		return strm << WaterString;
	else if (e == Nature::GetNature())
		return strm << NatureString;
	else if (e == Normal::GetNormal())
		return strm << NormalString;
	else if (e == Abyssal::GetAbyssal())
		return strm << AbyssalString;
	else
		return strm << "<ERROR NO ELEMENT>";
}

Bestiary::Bestiary()
{
	bestiary = vector<MonsterData>();

	std::fstream bestiaryFile;
	bestiaryFile.open(JSON_FILE_NAME);

	nlohmann::json parsedBestiary = nlohmann::json::array();

	bestiaryFile >> parsedBestiary;

	bestiaryFile.close();

	for (auto it = parsedBestiary.begin(); it != parsedBestiary.end(); ++it)
	{
		bestiary.push_back(MonsterData((*it)));
		//std::cout << "PARSED -- " << bestiary.back() << std::endl;
	}

	std::cout << "READ [" << bestiary.size() << "] MONSTERS..." << std::endl;

	//int testBeast = 105;
	//std::cout 
	//	<< bestiary[testBeast].name << "(" 
	//	<< bestiary[testBeast].element << ") gets a " 
	//	<< bestiary[testBeast].element->GetDamageMultiplierAgainst(GetAbyssal()) 
	//	<< " multiplier against abyssal!" << endl;
}

MonsterData* Bestiary::getRandomMonster() {

	int randomIdx;
	do
	{
		randomIdx = rand() % bestiary.size();
	} while (bestiary[randomIdx].size > 0); // exclude boss monsters for now

	return &(bestiary[randomIdx]);
}


