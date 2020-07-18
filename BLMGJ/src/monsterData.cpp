#include "monsterData.h"
#include <iostream>
#include <fstream>


// Elements
Fire::Fire()
{}


float Fire::GetDamageMultiplierAgainst(Element otherElement)
{
	return 0.05;
}

CardData::CardData(Element* e) : type(e)
{}

MonsterData::MonsterData(Element* e) : type(e)
{}

MonsterData::MonsterData(nlohmann::json json)
{
	name = json["name"];
	health = json["health"];
	damage = json["damage"];
	//type = ??

	//card = CardData();
	card.name = json["name"];
	card.flavor = json["flavor"];
	card.durability = json["durability"];
	card.bounces = json["bounces"];
	card.damage = json["damage"];
	//card.type
}


// Probably wont even use this
nlohmann::json MonsterData::Serialize()
{
	nlohmann::json json = {
	{"name", name},

	{"health", health},
	{"damage", damage},

	{"element", "NULL"},

	{"card",
		{
			{"name", card.name},
			{"flavor", card.flavor},

			{"durability", card.durability},
			{"bounces", card.bounces},
			{"damage", card.damage},

			{"element", "NULL"},
		}
	} };

	return json;
}


Bestiary::Bestiary()
{
	std::fstream bestiaryFile;
	bestiaryFile.open(JSON_FILE_NAME);

	nlohmann::json parsedBestiary = nlohmann::json::array();

	bestiaryFile >> parsedBestiary;

	bestiaryFile.close();

	for (auto it = parsedBestiary.begin(); it != parsedBestiary.end(); ++it)
	{
		std::cout << "PARSED:" << (*it) << "\n\n" << std::endl;
	}
}
