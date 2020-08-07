#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(float x, float y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarTop = IMAGEMANAGER->addImage("Front_Bar", "img/Effect/enemy_HP.bmp", width, height, true, RGB(255, 0, 255));
	_progressBarMid=IMAGEMANAGER->addImage("Hit_Bar", "img/Effect/enemy_HP_Hit.bmp", width, height, true, RGB(255, 0, 255));
	_progressBarBottom = IMAGEMANAGER->addImage("Back_Bar", "img/Effect/enemy_HP_Bar_Frame.bmp", width, height, true, RGB(255, 0, 255));

	//뒤에 깔리는 게이지의 가로크기를 기준으로 삼는다
	_width = _progressBarBottom->getWidth();
	_hitWidth = _width;
	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	_rcProgress = RectMakeCenter(_x, _y,
		_progressBarTop->getWidth(),
		_progressBarBottom->getHeight());
	_hitWidth -= (_hitWidth-_width)*0.1;
}

void progressBar::render()

{
	CAMERAMANAGER->render(getMemDC(), _progressBarBottom, _rcProgress.left + _progressBarBottom->getWidth() / 2,
		_y + _progressBarBottom->getHeight() / 2,
		0, 0,
		_progressBarBottom->getWidth(), _progressBarBottom->getHeight());
	if (_width && _width < _hitWidth) {
		CAMERAMANAGER->render(getMemDC(), _progressBarMid, _rcProgress.left + _progressBarBottom->getWidth() / 2,
			_y + _progressBarBottom->getHeight() / 2,
			0, 0,
			_hitWidth, _progressBarBottom->getHeight());
	}
	CAMERAMANAGER->render(getMemDC(), _progressBarTop, _rcProgress.left + _progressBarBottom->getWidth() / 2,
		_y + _progressBarBottom->getHeight() / 2,
		0, 0,
		_width, _progressBarBottom->getHeight());

}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	//백분율 구하는 공식이에여!
	_width = (currentGauge / maxGauge) * _progressBarBottom->getWidth();
}
