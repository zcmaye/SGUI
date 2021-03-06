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
SWidget::SWidget(SObject* parent)
	:SObject(parent)
	, _rect(0, 0, 150, 25)
	, m_isPress(false)
{
	std::cout << "SWidget init" << std::endl;

}
SWidget::~SWidget()
{
	std::cout << "~SWidget destroy " << _text << std::endl;
}

void SWidget::show()
{
	_isHiden = false;
	//update();
	_rrect = _rect;
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
	return _rect;
}

SRect SWidget::rect() const
{
	return SRect(0,0,_rect.width(),_rect.height());
}

SPoint SWidget::windowPos()const
{
	return _rect.leftTop();
}

void SWidget::setWindowPos(int x, int y)
{
	_rect.moveLeftTop(SPoint(x, y));
	//update();
}

void SWidget::setWindowPos(const SPoint& pos)
{
	setWindowPos(pos.x(), pos.y());
}

void SWidget::move(int x, int y)
{
	move(SPoint(x, y));
	
}

void SWidget::move(const SPoint& pos)
{
	_rect.moveLeftTop(pos);
	//update();
}

SSize SWidget::windowSize()const
{
	return _rect.size();
}

void SWidget::setWindowSize(int w, int h)
{
	_rect.setSize(w, h);
}

std::string SWidget::windowTitle()const
{
	return _text;
}

void SWidget::setWindowTitle(const std::string& title)
{
	_text = title;
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

SWidget* SWidget::parentWidget() const
{
	auto *w= dynamic_cast<SWidget*>(_parent);
	return w;
}

SPoint SWidget::mapToGlobal(const SPoint& pos) const
{
	return SPoint();
}

SPoint SWidget::mapFromGlobal(const SPoint& pos) const
{
	return SPoint();
}

SPoint SWidget::mapToParent(const SPoint&pos) const
{
	return pos + _rect.leftTop();
}

SPoint SWidget::mapFromParent(const SPoint& pos) const
{
	return pos - _rect.leftTop();
}

SPoint SWidget::mapTo(const SWidget* parent, const SPoint& pos) const
{
	SPoint p(pos);
	if (parent)
	{
		const SWidget* w = this;
		while (w && w != parent)
		{
			p = w->mapToParent(p);
			w = w->parentWidget();
		}
		if (!w)
		{
			throw "mapTo ：parent must be in parent hierarchy";
		}
	}
	return p;
}

SPoint SWidget::mapFrom(const SWidget* parent, const SPoint& pos) const
{
	SPoint p(pos);
	if (parent)
	{
		const SWidget* w = this;
		while (w && w != parent)
		{
			p = w->mapFromParent(p);
			w = w->parentWidget();
		}
		if (!w)
		{
			throw "mapFrom ：parent must be in parent hierarchy";
		}
	}

	return p;
}

bool SWidget::event(SEvent* ev)
{
	switch (ev->type())
	{
	case SEvent::Paint:
	{
		//绘制自己
		paintEvent();
		//孩子也重绘
		for (auto child : children())
		{
			child->event(new SEvent(ev->type()));
		}
		SDL_RenderPresent(SWindow::instance()->renderer());
	}
		break;
	case SDL_MOUSEBUTTONDOWN:
		mousePressEvent((SMouseEvent*)ev);
		break;
	case SDL_MOUSEBUTTONUP:
		mouseReleaseEvent((SMouseEvent*)ev);
		break;
	case SDL_MOUSEMOTION:
		mouseMoveEvent((SMouseEvent*)ev);
		break;
	case SEvent::Enter:
		enterEvent(ev);
		break;
	case SEvent::Leave:
		leaveEvent(ev);
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
 
	 //计算在父对象中实际应该绘制的矩形区域
	 SRect irect(frameGeometry());
	 if (_parent)
	 {
		 SWidget*  parentWidget = this->parentWidget();
		 if (parentWidget)
		 {
			 //父子对象相交矩形
			 irect = parentWidget->rect().intersected(this->frameGeometry());	
			 //把自己左上角相对于父对象的坐标转为相对于SWindow的全局坐标
			 irect.moveLeftTop(parentWidget->mapTo(SWindow::instance(), irect.leftTop()));
			 std::clog <<"_rrect "<<_text << _rrect << std::endl;
		}
	 }
		

	 const SDL_Rect& sdlRect = irect.sdlRect();
	 SDL_SetRenderDrawColor(renderer, _bkColor.red(), _bkColor.green(), _bkColor.blue(), _bkColor.alpha());
	 SDL_RenderFillRect(renderer, &sdlRect);
}

void SWidget::mousePressEvent(SMouseEvent* ev)
{
	m_isPress = true;
	m_begPos = ev->pos();
	std::clog << "press" << ev->button()<<" "<<ev->buttons() << std::endl;
	SDL_Log("mousePressEvent\n");
	//ev->ignore();
}

void SWidget::mouseReleaseEvent(SMouseEvent* ev)
{
	m_isPress = false;
	m_begPos = SPoint();
	std::clog << "release" << ev->pos() << std::endl;
	SDL_Log("mouseReleaseEvent\n");
}

void SWidget::mouseMoveEvent(SMouseEvent* ev)
{
	if (m_isPress && m_begPos != SPoint(0,0))
	{
		auto t = ev->pos() - m_begPos;
		move(mapToParent(ev->pos()) - m_begPos);
		//std::clog << "mouse move" << *this << "" << m_begPos<< ev->pos() << std::endl; ;
	}
}

void SWidget::enterEvent(SEvent* ev)
{
	std::clog << "enterEvent " <<_text<< std::endl;
}

void SWidget::leaveEvent(SEvent* ev)
{
	std::clog << "leaveEven " << _text<< std::endl;
}

std::ostream& operator<<(std::ostream& out, const SWidget& widget)
{
	out << "SWidget(" << /*&widget*/widget.frameGeometry() << "," << widget._text << ") ";
	return out;
}

std::ostream& operator<<(std::ostream& out, const SWidget* const widget)
{
	out << "SWidget(" << /*(int*)widget*/widget->frameGeometry() << "," << widget->_text << ") ";
	return out;
}
