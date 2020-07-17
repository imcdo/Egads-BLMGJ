#pragma once
#include <vector>
#include "Shader.h"
#include <unordered_map>
#include "gameObject.h"
#include <string>

using namespace std;

class SpriteRenderer {
private:
	unordered_map<Shader*, vector<GameObject>> bigDumDum; // shaders to sprite batching
	unordered_map<string, Shader> shaderBank;
	unordered_map<string, GameObject> gameObjects;
public:
	void draw() const {
		for (const pair<Shader*, vector<GameObject>>& renderPass : bigDumDum) {
			renderPass.first->use();
			for (const GameObject& gameObject : renderPass.second) {
				gameObject.draw();
			}
		}
	}

};
