#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <nlohmann\json.hpp>
#include "sprite.h"

using namespace nlohmann;
using namespace glm;

// Element / type labels
class Element
{
public:
	virtual float GetDamageMultiplierAgainst(Element otherElement) = 0;
};

class Fire : public Element
{
public:
	Fire();
	float GetDamageMultiplierAgainst(Element otherElement);
};

// Data objects for JSON-izing
struct CardData {
public:
	// Appearance
	std::string name = "ERROR"; // Unique ID
	std::string flavor = "";

	// Combat parameters
	int durability = 1;
	int damage = 1;
	int bounces = 1;

	Element* type;

	CardData(Element*);
};

struct MonsterData {
public:
	// Unique ID
	int id = -1;
	std::string name = "ERROR";
	std::string sprite = "";

	// Combat parameters
	int health = 1;
	int damage = 1;
	Element* type;

	// Card form
	CardData card;

	MonsterData(Element*);

	// Serialization
	MonsterData(json json);
	nlohmann::json Serialize();
};

class Bestiary
{

// will contain map / list of monsters
const std::string JSON_FILE_NAME = "bestiary.json";

public:
	Bestiary();
};

