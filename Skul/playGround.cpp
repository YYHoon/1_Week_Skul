#include "stdafx.h"
#include "playGround.h"
#include "mapManager.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	gameNode::init(true);
	
	imginit(); // 모든 이미지를 여기다 넣도록
	_mM = new mapManager;
	_pl = new player;
	_pl->init();
	_mM->setAdressLinkP(_pl);
	_mM->init();
	
	_pl->setLinkMap(_mM);
	

	_pl->setLocation(1238, 619);
	_pl->setStage("MAP_1_P");
	//_pM = new playerManager;
	//_pM->init();
	SCENEMANAGER->changeScene("MAP1");
	
	return S_OK;
}

//메모리 해제
void playGround::release()
{
	
}

//연산
void playGround::update()
{
	gameNode::update();
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) {
		_pl->setLocation(1238, 619);
		_pl->setStage("MAP_1_P");
		SCENEMANAGER->changeScene("MAP1"); 
	}

	SCENEMANAGER->update();
	

	_mM->update();
//	_pM->update();
	_pl->update();
}

//그리기 전용
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	//_mM->render();
	SCENEMANAGER->render();
	
	//_pM->render();
	_pl->render();
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);
	//TIMEMANAGER->render(getMemDC());
	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}

void playGround::imginit()
{
	// map
	IMAGEMANAGER->addImage("BOSS_MAP", "img/map/boss_map.bmp", 3417, 1344, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BOSS_MAP_P", "img/map/boss_map_pix.bmp", 3417, 1344, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MAP_1", "img/map/map_1.bmp", 2501, 2102, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MAP_1_P", "img/map/map_1_pix.bmp", 2501, 2102, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_F", "img/map/bg_first.bmp", 2304, 1920, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_M", "img/map/bg_mid.bmp", 2304, 1920, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BG_L", "img/map/bg_last.bmp", 2304,1920, true, RGB(255, 0, 255));

	// mage
	IMAGEMANAGER->addFrameImage("mage_Attack", "img/enemy/mage/mage_Attack.bmp", 3040, 390, 20, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mage_Attack_Ready", "img/enemy/mage/mage_Attack_Ready.bmp", 1872, 582, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mage_back_move", "img/enemy/mage/mage_back_move.bmp", 780, 348, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mage_idle", "img/enemy/mage/mage_idle.bmp", 666, 408, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mage_move", "img/enemy/mage/mage_move.bmp", 954, 306, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mage_skill_casting_Ready", "img/enemy/mage/mage_skill_casting_Ready.bmp", 540, 514, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mage_skill_casting", "img/enemy/mage/mage_skill_casting.bmp", 540, 514, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mage_skill_charge", "img/enemy/mage/mage_skill_charge.bmp", 1080, 510, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mage_skill_charging", "img/enemy/mage/mage_skill_charging.bmp", 5760, 510, 48, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mage_start", "img/enemy/mage/mage_start.bmp", 288, 191, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mage_start_end", "img/enemy/mage/mage_start_end.bmp", 1134, 282, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mage_start_up", "img/enemy/mage/mage_start_up.bmp", 651, 299, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mage_Death", "img/enemy/mage/mage_death.bmp", 594,105,3,1, true, RGB(255, 0, 255));

	// skul_base
	IMAGEMANAGER->addFrameImage("skul_base_attack_a", "img/skul_base/Attack/skul_Attack_A.bmp", 800, 238, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_attack_b", "img/skul_base/Attack/skul_Attack_B.bmp", 800, 238, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_attack_na", "img/skul_base/Attack/skul_Attack_A_NoHead.bmp", 800, 238, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_attack_nb", "img/skul_base/Attack/skul_Attack_B_NoHead.bmp", 800, 238, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_dash", "img/skul_base/Dash/skul_Dash.bmp", 324, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_ndash", "img/skul_base/Dash/skul_Dash_NoHead.bmp", 324, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_fall", "img/skul_base/Fall/skul_Fall.bmp", 800, 238, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_falling", "img/skul_base/Fall/skul_Falling.bmp", 480, 238, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_nfall", "img/skul_base/Fall/skul_Fall_NoHead.bmp", 800, 238, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_nfalling", "img/skul_base/Fall/skul_Falling_NoHead.bmp", 480, 238, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_idle", "img/skul_base/Idle/skul_Idle_HaveWeapon.bmp", 640, 238, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_nidle", "img/skul_base/Idle/skul_Idle_HaveWeapon_NoHead.bmp", 640, 238, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_jump", "img/skul_base/Jump/skul_Jump.bmp", 320, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_njump", "img/skul_base/Jump/skul_Jump_NoHead.bmp", 320, 238, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_jump_attack", "img/skul_base/Jump/skul_Jump_Attack.bmp", 640, 238, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_njump_attack", "img/skul_base/Jump/skul_Jump_NoHead_Attack.bmp", 640, 238, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_skill", "img/skul_base/Skill/skul_Skill.bmp", 640, 238, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_skill_head", "img/skul_base/Skill/skul_Skill_head.bmp", 120, 60, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_move", "img/skul_base/Walk/skul_Walk_Weapon.bmp", 1280, 238, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skul_base_nmove", "img/skul_base/Walk/skul_Walk_NoHead_Weapon.bmp", 1280,238, 8, 2, true, RGB(255, 0, 255));

	//berserker
	IMAGEMANAGER->addFrameImage("berserker_Attack_A", "img/player/player_Attack_A.bmp", 3168, 678, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("berserker_Attack_B", "img/player/player_Attack_B.bmp", 2265, 636, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("berserker_Dash", "img/player/player_dash.bmp", 450, 278, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("berserker_Fall", "img/player/player_fall.bmp", 708, 346, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("berserker_Falling", "img/player/player_falling.bmp", 531, 346, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("berserker_Idle", "img/player/player_Idle.bmp", 1044, 282, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("berserker_Jump", "img/player/player_jump.bmp", 165, 258, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("berserker_Jump_Attack", "img/player/player_jump_attack.bmp", 2373, 606, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("berserker_Skill", "img/player/player_skill.bmp", 336, 246, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("berserker_Move", "img/player/player_Move.bmp",1320,330,8, 2, true, RGB(255, 0, 255));

	//soldier
	IMAGEMANAGER->addFrameImage("soldier_Attack", "img/enemy/soldier/Attack/soldier_Attack.bmp", 860, 240, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("soldier_Idle", "img/enemy/soldier/Idle/soldier_Idle.bmp", 860, 240, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("soldier_Hit", "img/enemy/soldier/Hit/soldier_Hit.bmp", 344, 240, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("soldier_Walk", "img/enemy/soldier/Walk/soldier_Walk.bmp", 1376, 240, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("soldier_Die", "img/enemy/soldier/Die/Die_Right.bmp", 144,34,1,1, true, RGB(255, 0, 255));

	//archer
	IMAGEMANAGER->addFrameImage("archer_Attack", "img/enemy/archer/Attack/archer_Attack.bmp", 620,250, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("archer_Idle", "img/enemy/archer/Idle/archer_Idle.bmp", 620,250,4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("archer_Hit", "img/enemy/archer/Hit/archer_Hit.bmp", 310, 250, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("archer_Walk", "img/enemy/archer/Walk/archer_Walk.bmp", 775, 250, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("archer_Die", "img/enemy/archer/Die/Die_Right.bmp", 144, 36,1, 1, true, RGB(255, 0, 255));

	//effect
	IMAGEMANAGER->addFrameImage("Effect_skul_jump", "img/Effect/Skul_Jump_Effect.bmp", 4654, 199, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Effect_skul_Double_jump", "img/Effect/Skul_Double_Jump_Effect.bmp", 3580, 199, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Effect_Arrow", "img/Effect/enemy_Arrow.bmp", 10, 44, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_BASE", "img/Effect/UI_Base.bmp", 123, 114, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_BASE_M", "img/Effect/UI_Base_mini.bmp", 57, 38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_BERSERKER", "img/Effect/UI_Berserker.bmp", 123, 114, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_BERSERKER_M", "img/Effect/UI_Berserker_mini.bmp", 57,38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_STATUS", "img/Effect/UI_Status.bmp", 498, 198, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_HP", "img/Effect/UI_Hp.bmp", 348, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_HP_HIT", "img/Effect/UI_Hp_Hit.bmp", 348, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("FIRE", "img/Effect/FireBall.bmp", 58, 59, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("DASH", "img/Effect/skul_Dash_Effect.bmp", 4654,398,13,2, true, RGB(255, 0, 255));
	//sound

	SOUNDMANAGER->addSound("Sound_Map_1", "img/Sound/CHAPTER NO.1.mp3", true, true);
	SOUNDMANAGER->addSound("Sound_Boss", "img/Sound/The_Adventurers.mp3", true, true);
	SOUNDMANAGER->addSound("END", "img/Sound/end.mp3", true, true);
}
