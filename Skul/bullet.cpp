#include "stdafx.h"
#include "bullet.h"

HRESULT bullet::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;
	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	move();
}

void bullet::render()
{
	for (_viB = _vB.begin(); _viB != _vB.end(); ++_viB)
	{
		MYRECT rk = {(float) _viB->rc.left,(float)_viB->rc.top,(float)_viB->rc.right,(float)_viB->rc.bottom };
		 CAMERAMANAGER->frameRender(getMemDC(), _viB->img, _viB->rc.left, _viB->rc.top);
		// CAMERAMANAGER->rectangle(getMemDC(), rk);

	}
}

void bullet::fire(float x, float y, float speed)
{
	if (_bulletMax < _vB.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.img = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.radius = bullet.img->getWidth() / 2;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;

	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getWidth(),
		bullet.img->getHeight());

	_vB.push_back(bullet);
}
void bullet::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax < _vB.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.img = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.angle = angle;
	bullet.radius = bullet.img->getWidth() / 2;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;

	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getWidth(),
		bullet.img->getHeight());

	_vB.push_back(bullet);
}
void bullet::move()
{
	for (_viB = _vB.begin(); _viB != _vB.end();)
	{
		//_viB->x +=  _viB->speed;

		_viB->x += cosf(_viB->angle) * _viB->speed;
		_viB->y += -sinf(_viB->angle) * _viB->speed;
		_viB->rc = RectMakeCenter(_viB->x, _viB->y,
			_viB->img->getWidth(),
			_viB->img->getHeight());

		if (_range < getDistance(_viB->x, _viB->y,
			_viB->fireX, _viB->fireY))
		{
			_viB = _vB.erase(_viB);
		}
		else ++_viB;
	}
}

void bullet::removeBullet(int arrNum)
{
	_vB.erase(_vB.begin() + arrNum);
}
