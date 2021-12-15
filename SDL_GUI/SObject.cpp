#include "SObject.h"
#include"SApplication.h"
#include"SWindow.h"
#include"SEvent.h"
#define MAXZ	10		//窗口最大层级
/*@ SObject*/

SObject::SObject(SObject* parent)
	:_parent(parent)
{
	if (_parent)
		_parent->_children.push_back(this);	//把this设为父对象的孩子


	std::cout << "SObject init" << std::endl;
}
SObject::~SObject()
{
	//1,先释放孩子
	if(!_children.empty())
		this->clearChildern();
	if (!isFree)
	{
		isFree = true;
		delete this;
	}

	std::cout << "~SObject destroy" << std::endl;
}
void SObject::setParent(SObject* parent)
{
	//if (_parent)
	//{
	//	//把this从原来的父对象的孩子列表中移除
	//	auto it = _parent->_children.find(this);
	//	if (it != _parent->_children.end())
	//	{
	//		_parent->_children.erase(this);
	//	}
	//}
	////设置新的父对象，并添加进孩子列表
	//_parent = parent;
	//if (_parent)
	//	_parent->_children.insert(this);
}

void SObject::clearChildern()
{
	SObject* currentChildBeingDeleted = nullptr;
	//1,先释放孩子
	for (int i = 0; i < _children.size(); ++i)
	{
		currentChildBeingDeleted = _children.at(i);
		_children[i] = nullptr;
		delete currentChildBeingDeleted;
	}
	_children.clear();
}

bool SObject::event(SEvent* ev)
{
	SDL_Log(" SObject  event\n");
	return false;
}


/*@ SWidget*/
void SWidget::show()
{
	_isHiden = false;
	update();
}

void SWidget::raise()
{
	_z = MAXZ;
}

float SWidget::windowOpacity()
{
	return _opacity;
}

void SWidget::setWindowOpacity(float opacity)
{
	_opacity = opacity;
}

SRect SWidget::frameGeometry()
{
	return SRect(_pos,_size);
}


SPoint SWidget::windowPos()
{
	return _pos;
}

void SWidget::setWindowPos(int x, int y)
{
	_pos.x = x;
	_pos.y = y;
}

SSize SWidget::windowSize()
{
	return _size;
}

void SWidget::setWindowSize(int w, int h)
{
	_size.w = w;
	_size.h = h;
}

std::string SWidget::windowTitle()
{
	return _title;
}

void SWidget::setWindowTitle(const std::string& title)
{
	_title = title;
}

SSurface* SWidget::windowIcon()
{
	return _icon;
}

void SWidget::setWindowIcon(SSurface* icon)
{
	_icon = icon;
}

void SWidget::hide()
{
	_isHiden = true;
}

void SWidget::update()
{
	event(new SEvent(SEvent::Paint));
}

bool SWidget::event(SEvent* ev)
{
	switch (ev->type())
	{
	case SEvent::Paint:
		paintEvent();
		break;
	default:
		break;
	}
	SDL_Log(" SWidget  event %s\n",_title.c_str());
	return false;
}

void SWidget::paintEvent()
{
	 auto *renderer = SWindow::instance()->renderer();
	 if (!renderer)
		 return;

	 auto rect =  frameGeometry().sdlRect();
	 SDL_SetRenderDrawColor(renderer, 194, 195, 201,255);
	 SDL_RenderFillRect(renderer, &rect);
	 SDL_RenderPresent(renderer);
}
