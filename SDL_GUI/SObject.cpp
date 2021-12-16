#include "SObject.h"
#include"SApplication.h"
#include"SWindow.h"
#include"SEvent.h"
#define MAXZ	10		//窗口最大层级
using namespace std;
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

	if (_parent)
	{
		//把this从原来的父对象的孩子列表中移除
		auto it = std::find(_parent->_children.begin(), _parent->_children.end(),this);
		if (it != _parent->_children.end())
		{
			_parent->_children.erase(it);
		}
	}

	std::cout << "~SObject destroy" << std::endl;
}
SObject* SObject::parent()
{
	return _parent;
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

float SWidget::windowOpacity()const
{
	return _opacity;
}

void SWidget::setWindowOpacity(float opacity)
{
	_opacity = opacity;
}

SRect SWidget::frameGeometry()const
{
	return SRect(_pos,_size);
}


SPoint SWidget::windowPos()const
{
	return _pos;
}

void SWidget::setWindowPos(int x, int y)
{
	_pos.x = x;
	_pos.y = y;
}

SSize SWidget::windowSize()const
{
	return _size;
}

void SWidget::setWindowSize(int w, int h)
{
	_size.w = w;
	_size.h = h;
}

std::string SWidget::windowTitle()const
{
	return _title;
}

void SWidget::setWindowTitle(const std::string& title)
{
	_title = title;
}

SSurface* SWidget::windowIcon()const
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

void SWidget::setBackgroundColor(SColor c)
{
	_bkColor = c;
}

bool SWidget::event(SEvent* ev)
{
	switch (ev->type())
	{
	case SEvent::Paint:
		paintEvent();
		break;
	case SDL_MOUSEBUTTONDOWN:
		mousePressEvent((SMouseEvent*)ev);
		break;
	case SDL_MOUSEBUTTONUP:
		mouseReleaseEvent((SMouseEvent*)ev);
		break;
	default:
		break;
	}
	//cout << this << " " << ev << endl;
	//如果事件是接受的，则销毁
	if (ev->isAccepted())
	{
		delete ev;
	}
	//如果有父组件，则传给父组件
	else if(_parent)
	{
		this->_parent->event(ev);
	}
	//否则销毁事件
	else
	{
		delete ev;
	}
	
	return false;
}

void SWidget::paintEvent()
{
	 auto *renderer = SWindow::instance()->renderer();
	 if (!renderer)
		 return;
	 
	 SPoint leftTop;
	 if (_parent)
	 {
		 auto widget = dynamic_cast<SWidget*>(_parent);
		 if (widget)
			 leftTop = widget->windowPos() +this->windowPos();
	 }
	 else
	 {
		 leftTop = this->windowPos();
	 }
	 const SDL_Rect& sdlRect = SRect(leftTop, this->windowSize()).sdlRect();
	 SDL_SetRenderDrawColor(renderer, _bkColor.red(), _bkColor.green(), _bkColor.blue(), _bkColor.alpha());
	 SDL_RenderFillRect(renderer, &sdlRect);
	 SDL_RenderPresent(renderer);
	 //SDL_Log("paintEvent\n");
}

void SWidget::mousePressEvent(SMouseEvent* ev)
{
	//SDL_Log("mousePressEvent\n");
	//ev->ignore();
}

void SWidget::mouseReleaseEvent(SMouseEvent* ev)
{
	//SDL_Log("mouseReleaseEvent\n");
}

//250 250
//0 0 500 500
//20 20 400 400 ->

SPoint SWidget::mapFromParent(const SPoint& point)
{
	if (_parent)
		return SPoint(this->_pos.x - point.x, this->_pos.y - point.y);
	else
		return point;
}


std::ostream& operator<<(std::ostream& out, const SWidget& widget)
{
	out << "SWidget(" << /*&widget*/widget.frameGeometry() << "," << widget._title << ") ";
	return out;
}

std::ostream& operator<<(std::ostream& out, const SWidget* const widget)
{
	out << "SWidget(" << /*(int*)widget*/widget->frameGeometry() << "," << widget->_title << ") ";
	return out;
}
