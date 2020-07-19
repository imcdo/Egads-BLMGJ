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
static Normal* GetNormal()
{
	if (NormalType == nullptr)
	{
		NormalType = new Normal();
	}
	return NormalType;
}

static Flame* FlameType = nullptr;
static Flame* GetFlame()
{
	if (FlameType == nullptr)
	{
		FlameType = new Flame();
	}
	return FlameType;
}

static Water* WaterType = nullptr;
static Water* GetWater()
{
	if (WaterType == nullptr)
	{
		WaterType = new Water();
	}
	return WaterType;
}

static Nature* NatureType = nullptr;
static Nature* GetNature()
{
	if (NatureType == nullptr)
	{
		NatureType = new Nature();
	}
	return NatureType;
}

static Abyssal* AbyssalType = nullptr;
static Abyssal* GetAbyssal()
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

Water::Water()
{
}

float Water::GetDamageMultiplierAgainst(static Element* otherElement)
{
	if (otherElement == GetFlame())
		return SUPER_EFFECTIVE;
	else if (otherElement == GetNature())
		return RESISTANT;
	else
		return NEUTRAL;
}

Nature::Nature()
{
}

float Nature::GetDamageMultiplierAgainst(static Element* otherElement)
{
	if (otherElement == GetWater())
		return SUPER_EFFECTIVE;
	else if (otherElement == GetFlame())
		return RESISTANT;
	else
		return NEUTRAL;
}

Flame::Flame()
{
}

float Flame::GetDamageMultiplierAgainst(static Element* otherElement)
{
	if (otherElement == GetNature())
		return SUPER_EFFECTIVE;
	else if (otherElement == GetWater())
		return RESISTANT;
	else
		return NEUTRAL;
}

Abyssal::Abyssal()
{
}

float Abyssal::GetDamageMultiplierAgainst(static Element* otherElement)
{
	if (otherElement == GetAbyssal())
		return SUPER_EFFECTIVE;
	else if (otherElement == GetNormal())
		return RESISTANT;
	else
		return NEUTRAL;
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
	string typeString = json["element"].get<string>();
	if (NormalString.compare(typeString) == 0)
	{
		element = GetNormal();
	}
	else if (FlameString.compare(typeString) == 0)
	{
		element = GetFlame();
	}
	else if (WaterString.compare(typeString) == 0)
	{
		element = GetWater();
	}
	else if (NatureString.compare(typeString) == 0)
	{
		element = GetNature();
	}
	else if (AbyssalString.compare(typeString) == 0)
	{
		element = GetAbyssal();
	}
	else
	{
		cout << "ERROR :: Couldn't read element. Setting to NORMAL. " << NatureString.compare(typeString) << endl;
		element = GetNormal();
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
	if (e == GetFlame())
		return strm << FlameString;
	else if (e == GetWater())
		return strm << WaterString;
	else if (e == GetNature())
		return strm << NatureString;
	else if (e == GetNormal())
		return strm << NormalString;
	else if (e == GetAbyssal())
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
		std::cout << "PARSED -- " << bestiary.back() << std::endl;
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
	int randomIdx = rand() % bestiary.size();
	return &(bestiary[randomIdx]);
}


