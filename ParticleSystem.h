#pragma once
#include "ParticleModel.h"
#include <vector>
using namespace std;

class ParticleSystem
{
private:
	int numParticles;
	vector<ParticleModel *> particleList[];
public:
	void Update();
	void Draw();
	
	void CreateParticle();
	void DestroyParticle();
};

