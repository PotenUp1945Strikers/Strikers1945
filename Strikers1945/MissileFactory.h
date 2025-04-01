#pragma once
#include "config.h"
#include "Missile.h"

class MissileFactory
{
protected:
	std::vector<Missile*> missiles;
	virtual Missile* CreateMissile() = 0;

public:
	void AddMissile(FPOINT pos);
	std::vector<Missile*>& GetMissiles() { return missiles; }

	MissileFactory() {};
	virtual ~MissileFactory() {};
};

class PlayerNormalMissileFactory : public MissileFactory
{
private:
	virtual Missile* CreateMissile() override;

public:
	PlayerNormalMissileFactory() {};
	virtual ~PlayerNormalMissileFactory() {};
};

class PlayerBombMissileFactory : public MissileFactory
{
private:
	virtual Missile* CreateMissile() override;

public:
	PlayerBombMissileFactory() {};
	virtual ~PlayerBombMissileFactory() {};
};

class EnemyNormalMissileFactory : public MissileFactory
{
private:
	virtual Missile* CreateMissile() override;

public:
	EnemyNormalMissileFactory() {};
	virtual ~EnemyNormalMissileFactory() {};
};

class EnemyLargeMissileFactory : public MissileFactory
{
private:
	virtual Missile* CreateMissile() override;

public:
	EnemyLargeMissileFactory() {};
	virtual ~EnemyLargeMissileFactory() {};
};