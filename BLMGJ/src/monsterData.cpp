#include "monsterData.h"
#include <iostream>
#include <fstream>

using namespace std;

// Elements
Fire::Fire()
{}


float Fire::GetDamageMultiplierAgainst(Element* otherElement)
{
	return 0.05;
}

MonsterData::MonsterData(Element* e) : type(e)
{}

MonsterData::MonsterData(nlohmann::json json)
{
	std::string stringID = json["id"].get<std::string>();
	id = stoi(stringID);
	name = json["name"].get<std::string>();
	species = json["species"].get<std::string>();
	flavor = "NULL";			//FIX
	sprite = json["sprite"].get<std::string>();

	type = new Fire();			//FIX
	health = json["hp"];
	damage = json["attack"];
	decay = json["decay"];
	bounce = json["bounce"];
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
}
