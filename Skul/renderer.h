#pragma once
#include "Transform.h"
#include "gameNode.h"
#include <map>
#include <algorithm>
#include "singletonBase.h"

using namespace std;
class renderer
{
public:
	/// <summary>
	/// 이 값이 클 수록 앞에 그려짐(나중에그려진다는 뜻)
	/// </summary>
	int drawOrder;
	Transform* transform;
	int imgSizeX, imgSizeY;
	renderer(gameNode* gamenode) { transform = &(gamenode->transform); }
	void awake();
	void render();
	void update();
private:
	
};

class renderManager : public singletonBase<renderManager>
{
//private:
//	map<int, std::vector<renderer*>*> renderers;
//
//	void RenderList(vector<renderer*> rl) {
//		for_each(&rl.begin(), &rl.end(), Render);
//	}
//	void Render(renderer* r)
//	{
//		r->render();
//	}
//public :
//	
//	void AddRenderer(renderer* r) {
//	}
//
//	void RenderAll() {
//		for_each(renderers.begin(), renderers.end(), RenderList);
//
//	}
};