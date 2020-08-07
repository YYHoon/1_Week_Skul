#pragma once
#include "gameNode.h"

struct tagBullet
{
	image* img;		
	RECT rc;				
	float x, y;				
	float angle;			
	float radius;			
	float speed;			
	float fireX, fireY;		
	bool isFire;			
	int count;				
};
class bullet : public gameNode
{
private:
	vector<tagBullet> _vB;
	vector<tagBullet>::iterator _viB;

	const char* _imageName;
	float _range;
	int _bulletMax;
public:

	virtual HRESULT init(const char* imageName, int bulletMax, float range);
	virtual void release();
	virtual void update();
	virtual void render();
	void fire(float x, float y, float speed);
	void fire(float x, float y, float angle,float speed);

	void move();

	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vB; }
	vector<tagBullet>::iterator getVIBullet() { return _viB; }
};

