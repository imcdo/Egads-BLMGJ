#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <nlohmann\json.hpp>
#include "sprite.h"

using namespace nlohmann;
using namespace glm;
using namespace std;

// Element / type labels
class Element
{
public:
	virtual float GetDamageMultiplierAgainst(Element* otherElement) = 0;
};

class Fire : public Element
{
public:
	Fire();
	float GetDamageMultiplierAgainst(Element* otherElement);
};

struct MonsterData {
public:
	// Unique ID
	int id = -1;
	std::string name = "ERROR";
	std::string species = "";
	std::string flavor = "";
	std::string sprite = "";

	// Combat values
	Element* type;
	int health = 1;
	int damage = 1;
	int decay = 1;
	int bounce = 1;

	MonsterData(Element*);
	MonsterData(json json);
};

ostream& operator<<(ostream& strm, const MonsterData& a);

class Bestiary
{
private:

	const std::string JSON_FILE_NAME = "bestiary.json";

	vector<MonsterData> bestiary;

public:
	Bestiary();
};

