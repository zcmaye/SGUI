#include "SWidget.h"
#include"Configure.h"
#include"SWindow.h"
#include"SApplication.h"
#include"SSurface.h"
#define MAXZ	10		//窗口最大层级
/*@ SWidget*/
SWidget::SWidget(SObject* parent)
	:SObject(parent)
	, m_Window(nullptr)
	, m_Renderer(nullptr)
	, m_WinId(0)
	, _rect(0, 0, 640, 480)
	, m_isPress(false)
{
	std::cout << "SWidget init" << std::endl;
	if (!SDL_WasInit(SDL_INIT_VIDEO))
	{
		SDL_Log("No initialization SDL~");
	}

	if (parent == nullptr)
	{
		m_Window = SDL_CreateWindow("SDL window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _rect.width(), _rect.height(), SDL_WINDOW_SHOWN);
		if (m_Window == nullptr)
		{
			SDL_Log("create window failed~");
			return;
		}
		m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
		if (m_Renderer == nullptr)
		{
			SDL_Log("create renderer falied~");
			return;
		}
		m_WinId.mainId = SDL_GetWindowID(m_Window);
		m_WinId.selfId = 0;
		SApplication::addWindow(this);
	}
	else
	{
		auto pw = dynamic_cast<SWidget*>(parent);
		m_WinId.mainId = pw->m_WinId.mainId;
		m_WinId.selfId = ++pw->m_WinId.selfId;
		m_Renderer = pw->renderer();
		_rect.setSize(150, 30);

	}

}
SWidget::~SWidget()
{
	if (m_Window)
	{
		SDL_DestroyWindow(m_Window);
		SDL_DestroyRenderer(m_Renderer);
		m_Window = nullptr;
		m_Renderer = nullptr;
	}
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
	return SRect(0, 0, _rect.width(), _rect.height());
}

SPoint SWidget::windowPos()const
{
	return _rect.leftTop();
}

void SWidget::setWindowPos(int x, int y)
{
	if (m_Window)
	{

	}
	else
	{
		_rect.moveLeftTop(SPoint(x, y));
	}
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
	if (!_parent)
		SDL_SetWindowSize(m_Window, _rect.width() + _rect.x1(), _rect.height() + _rect.y1());
}

std::string SWidget::windowTitle()const
{
	return _text;
}

void SWidget::setWindowTitle(const std::string& title)
{
	_text = title;
	if(!_parent)
		SDL_SetWindowTitle(m_Window,_text.c_str());
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

bool SWidget::isHidden() const
{
	if (SDL_GetWindowFlags(m_Window) & SDL_WINDOW_HIDDEN)
	{
		return true;
	}
	return false;
}

void SWidget::update()
{
	//event(new SEvent(SEvent::Paint));
}

void SWidget::setBackgroundColor(SColor c)
{
	_bkColor = c;
}

SWidget* SWidget::parentWidget() const
{
	auto* w = dynamic_cast<SWidget*>(_parent);
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

SPoint SWidget::mapToParent(const SPoint& pos) const
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

SWidget* SWidget::topLevelParentWidget()
{
	SWidget* pw = parentWidget();
	while (pw && pw->parentWidget())
	{
		pw = pw->parentWidget();
	}
	return pw;
}

/*
* 查找指定坐标所在的第一个控件，把obj的所有子控件都遍历一遍
*/
static SObject* findLastChild(SObject* obj, int x, int y)
{
	SObject* returnObj = nullptr;
	for (auto child : obj->children())
	{
		auto* widget = dynamic_cast<SWidget*>(child);
		auto* parentWidget = dynamic_cast<SWidget*>(obj);
		SPoint leftTop = widget->mapFrom(parentWidget, SPoint(x, y));

		if (widget && widget->rect().contains(leftTop.x(), leftTop.y()))
		{
			if (!widget->children().empty())
				returnObj = findLastChild(widget, leftTop.x(), leftTop.y());
			if (returnObj == nullptr)
				return widget;
			else
				return returnObj;

		}

	}
	return returnObj;
}

bool SWidget::event(SDL_Event* ev)
{
	//有事件就重绘
	paintEvent(ev);
	if (ev->window.windowID != m_WinId.mainId)
	{
		return false;
	}
	if (ev->type == SDL_WINDOWEVENT)
	{
		switch (ev->window.event)
		{
		case SDL_WINDOWEVENT_NONE:           /**< Never used */
			break;
		case SDL_WINDOWEVENT_SHOWN:          /**< 窗口显示 */
			showEvent(ev);
			break;
		case SDL_WINDOWEVENT_HIDDEN:         /**< 窗口隐藏 */
			hiddenEvent(ev);
			break;
		case SDL_WINDOWEVENT_EXPOSED:        /**< 窗口被显露出来且必须被重画（这种情况一般是窗口被其他窗口挡住，然后被遮挡部分又显示出来时 */
			paintEvent(ev);
			break;
		case SDL_WINDOWEVENT_MOVED:          /**< 窗口移动到 data1, data2 位置*/
			moveEvent(ev);
			break;
		case SDL_WINDOWEVENT_RESIZED:        /**< 窗口重置大小为 data1xdata2 */
		case SDL_WINDOWEVENT_SIZE_CHANGED:   /**< 窗口大小已经改变，不管是调用API改变还是用户改变窗口大小 */
			resizeEvent(ev);
			break;
		case SDL_WINDOWEVENT_MINIMIZED:      /**< 窗口最小化 */
		case SDL_WINDOWEVENT_MAXIMIZED:      /**< 窗口最大化 */
		case SDL_WINDOWEVENT_RESTORED:       /**< 窗口已恢复到正常的大小和位置   */
			changeEvent(ev);
			break;
		case SDL_WINDOWEVENT_ENTER:          /**< 窗口获得鼠标焦点 */
			enterEvent(ev);
			m_mouseFocus = true;
			break;
		case SDL_WINDOWEVENT_LEAVE:          /**< 窗口失去鼠标焦点 */
			leaveEvent(ev);
			m_mouseFocus = false;
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:   /**< 窗口获得键盘焦点 */
			m_keyboardFocus = true;
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:     /**< 窗口丢失键盘焦点 */
			m_keyboardFocus = false;
			break;
		case SDL_WINDOWEVENT_CLOSE:          /**< 窗口管理器请求窗口关闭 */
			closeEvent(ev);
			break;
		case SDL_WINDOWEVENT_TAKE_FOCUS:     /**< 窗口被提供了一个焦点(应该将SetWindowInputFocus()设置在自身或子窗口上，或者忽略)   */
			break;
		case SDL_WINDOWEVENT_HIT_TEST:       /**< Window had a hit test that wasn't SDL_HITTEST_NORMAL. */
			break;
		case SDL_WINDOWEVENT_ICCPROF_CHANGED:/**< The ICC profile of the window's display has changed. */
			break;
		case SDL_WINDOWEVENT_DISPLAY_CHANGED: /**< 窗口移动到data1屏幕显示 */
			break;
		default:
			SDL_Log("Other Window event\n");
			break;
		}
	}
	if (ev->type == SDL_MOUSEBUTTONDOWN)
	{
		auto pos = this->mapFrom(this->topLevelParentWidget(), SPoint(ev->button.x, ev->button.y));
		if (_rect.contains(pos))
		{
			SDL_Event e = *ev;
			e.button.x = pos.x();
			e.button.y = pos.y();
			mousePressEvent(&e.button);
		}
	}
	else if (ev->type == SDL_MOUSEBUTTONUP)
	{
		auto pos = this->mapFrom(this->topLevelParentWidget(), SPoint(ev->button.x, ev->button.y));
		if (_rect.contains(pos))
		{
			SDL_Event e = *ev;
			e.button.x = pos.x();
			e.button.y = pos.y();
			mouseReleaseEvent(&e.button);
		}
	}
	else if (ev->type == SDL_MOUSEMOTION)
	{
		auto pos = this->mapFrom(this->topLevelParentWidget(), SPoint(ev->motion.x, ev->motion.y));
		if (_rect.contains(pos))
		{
			SDL_Event e = *ev;
			e.motion.x = pos.x();
			e.motion.y = pos.y();
			mouseMoveEvent(&e.motion);
			//如果原来没有鼠标焦点，就初始进入事件
			if (!m_mouseFocus)
			{
				m_mouseFocus = true;
				enterEvent(ev);
			}
		}
		//如果原来有鼠标焦点，但是现在鼠标没有到控件上，就触发离开事件
		else if (m_mouseFocus)
		{
			m_mouseFocus = false;
			leaveEvent(ev);
		}
	}

	return false;
}

void SWidget::clear() const
{
	SDL_SetRenderDrawColor(m_Renderer, _bkColor.red(), _bkColor.green(), _bkColor.blue(), _bkColor.alpha());
	SDL_RenderClear(m_Renderer);

}

void SWidget::paintEvent(SDL_Event* ev)
{
	auto* renderer = m_Renderer;
	if (!renderer)
		return;

	//计算在父对象中实际应该绘制的矩形区域
	SRect irect(frameGeometry());
	if (_parent)
	{
		SWidget* parentWidget = this->parentWidget();
		if (parentWidget)
		{
			//父子对象相交矩形
			irect = parentWidget->rect().intersected(this->frameGeometry());
			//把自己左上角相对于父对象的坐标转为相对于SWindow的全局坐标
			irect.moveLeftTop(parentWidget->mapTo(topLevelParentWidget(), irect.leftTop()));
			//std::clog << "_rrect " << _text << _rrect << std::endl;
			_rrect = irect;	//实际绘制的矩形

			//如果父对象还有父对象必须计算一下,相对于当前父对象的实际绘制区域
			auto pparent = parentWidget->parentWidget();
			if (pparent)
			{
				//父子对象相交矩形
				irect = pparent->_rrect.intersected(irect);
			}
		}
	}

	//绘制自己
	const SDL_Rect& sdlRect = _parent?irect.sdlRect(): _rect.sdlRect();
	SDL_SetRenderDrawColor(renderer, _bkColor.red(), _bkColor.green(), _bkColor.blue(), _bkColor.alpha());
	SDL_RenderFillRect(renderer, &sdlRect);

	//孩子也重绘
	for (auto child : children())
	{
		//SDL_Event tev = *ev;
		//tev.window.event = SDL_WINDOWEVENT_EXPOSED;
		child->event(ev);
	}
}

void SWidget::mousePressEvent(SDL_MouseButtonEvent* ev)
{
	//m_isPress = true;
	//m_begPos = SPoint(ev->x, ev->y);
	//std::clog << "press "<<_text<<" " << ev->x << " " << ev->y << std::endl;
	//ev->ignore();
}

void SWidget::mouseReleaseEvent(SDL_MouseButtonEvent* ev)
{
	//m_isPress = false;
	//m_begPos = SPoint();
	//std::clog << "release" << SPoint(ev->x, ev->y) << std::endl;
	//SDL_Log("mouseReleaseEvent\n");
}

void SWidget::mouseMoveEvent(SDL_MouseMotionEvent* ev)
{
	//if (m_isPress && m_begPos != SPoint(0, 0))
	//{
	//	move(mapToParent(SPoint(ev->x, ev->y)) - m_begPos);
	//	//std::clog << "mouse move" << *this << "" << m_begPos<< ev->pos() << std::endl; ;
	//}
	std::clog << "mouse move " << _text << " " << ev->x << " " << ev->y << std::endl;
}

void SWidget::wheelEvent(SDL_MouseWheelEvent* ev)
{
}

void SWidget::enterEvent(SDL_Event* ev)
{
	std::clog << "enterEvent " << _text << std::endl;
}

void SWidget::leaveEvent(SDL_Event* ev)
{
	std::clog << "leaveEven " << _text << std::endl;
}

void SWidget::closeEvent(SDL_Event* ev)
{
	SDL_HideWindow(m_Window);
}

void SWidget::showEvent(SDL_Event* ev)
{
}

void SWidget::hiddenEvent(SDL_Event* ev)
{
}

void SWidget::resizeEvent(SDL_Event* ev)
{
}

void SWidget::moveEvent(SDL_Event* ev)
{
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
