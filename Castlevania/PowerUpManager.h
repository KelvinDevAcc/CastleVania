#pragma once
#include "PowerUp.h"
#include <vector>
#include <SoundEffect.h>
#include "Level.h"
#include "structs.h"
#include "Player.h"

class PowerUpManager final
{
public:
	PowerUpManager(Level* level, Player* player );
	~PowerUpManager( );
	PowerUpManager(const PowerUpManager&) = delete;
	PowerUpManager& operator=(const PowerUpManager&) = delete;
	PowerUpManager(PowerUpManager&&) = delete;
	PowerUpManager& operator=(PowerUpManager&&) = delete;

	PowerUp* AddItem(int rows, int coloms, float scale, int startrow, Point2f bottomleft, PowerUp::Type Type);
	void ClearStatueVec();
	void Update( float elapsedSec );
	void Draw( ) const;

	size_t Size( ) const;
	bool HitItem( const Rectf& rect ) ;

private:
	std::vector<PowerUp*> m_pItems;
	SoundEffect* m_PickUpSoundEffect;
	Level* m_level;
	Player* m_player;
};
