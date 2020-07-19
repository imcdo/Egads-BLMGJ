#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <nlohmann\json.hpp>
#include "sprite.h"

using namespace nlohmann;
using namespace glm;
using namespace std;

const float SUPER_EFFECTIVE = 2;
const float NEUTRAL = 1;
const float RESISTANT = 0.5f;

const string NORMAL = "Normal";

// Element / type labels
class Element
{
public:
	virtual float GetDamageMultiplierAgainst(static Element* otherElement) = 0;
};

class Normal : public Element
{
public:
	Normal();
	float GetDamageMultiplierAgainst(static Element* otherElement) override;
};

class Water : public Element
{
public:
	Water();
	float GetDamageMultiplierAgainst(static Element* otherElement) override;
};

class Nature : public Element
{
public:
	Nature();
	float GetDamageMultiplierAgainst(static Element* otherElement) override;
};

static class Flame : public Element
{
public:
	Flame();
	float GetDamageMultiplierAgainst(static Element* otherElement) override;
};

static class Abyssal : public Element
{
public:
	Abyssal();
	float GetDamageMultiplierAgainst(static Element* otherElement) override;
};

struct MonsterData {
public:
	// Unique ID
	int id = -1;
	int rank = -1;
	string name = "ERROR";
	string species = "";
	string flavor = "";
	string sprite = "";

	// Combat values
	Element* element;
	int health = -1;
	int damage = -1;
	int decay = -1;
	int bounce = -1;

	MonsterData(Element*);
	MonsterData(json json);
};

ostream& operator<<(ostream& strm, const MonsterData& a);
ostream& operator<<(ostream& strm, const Element* e);


class Bestiary
{
private:

	const std::string JSON_FILE_NAME = "bestiary.json";

	vector<MonsterData> bestiary;

public:
	Bestiary();
	MonsterData* getRandomMonster();
};
