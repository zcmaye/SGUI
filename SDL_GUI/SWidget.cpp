#include "SWidget.h"
#include"Configure.h"
#include"SWindow.h"
#include"SApplication.h"
#include"SSurface.h"
#define MAXZ	10		//�������㼶
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
			throw "mapTo ��parent must be in parent hierarchy";
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
			throw "mapFrom ��parent must be in parent hierarchy";
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
* ����ָ���������ڵĵ�һ���ؼ�����obj�������ӿؼ�������һ��
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
	//���¼����ػ�
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
		case SDL_WINDOWEVENT_SHOWN:          /**< ������ʾ */
			showEvent(ev);
			break;
		case SDL_WINDOWEVENT_HIDDEN:         /**< �������� */
			hiddenEvent(ev);
			break;
		case SDL_WINDOWEVENT_EXPOSED:        /**< ���ڱ���¶�����ұ��뱻�ػ����������һ���Ǵ��ڱ��������ڵ�ס��Ȼ���ڵ���������ʾ����ʱ */
			paintEvent(ev);
			break;
		case SDL_WINDOWEVENT_MOVED:          /**< �����ƶ��� data1, data2 λ��*/
			moveEvent(ev);
			break;
		case SDL_WINDOWEVENT_RESIZED:        /**< �������ô�СΪ data1xdata2 */
		case SDL_WINDOWEVENT_SIZE_CHANGED:   /**< ���ڴ�С�Ѿ��ı䣬�����ǵ���API�ı仹���û��ı䴰�ڴ�С */
			resizeEvent(ev);
			break;
		case SDL_WINDOWEVENT_MINIMIZED:      /**< ������С�� */
		case SDL_WINDOWEVENT_MAXIMIZED:      /**< ������� */
		case SDL_WINDOWEVENT_RESTORED:       /**< �����ѻָ��������Ĵ�С��λ��   */
			changeEvent(ev);
			break;
		case SDL_WINDOWEVENT_ENTER:          /**< ���ڻ����꽹�� */
			enterEvent(ev);
			m_mouseFocus = true;
			break;
		case SDL_WINDOWEVENT_LEAVE:          /**< ����ʧȥ��꽹�� */
			leaveEvent(ev);
			m_mouseFocus = false;
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:   /**< ���ڻ�ü��̽��� */
			m_keyboardFocus = true;
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:     /**< ���ڶ�ʧ���̽��� */
			m_keyboardFocus = false;
			break;
		case SDL_WINDOWEVENT_CLOSE:          /**< ���ڹ��������󴰿ڹر� */
			closeEvent(ev);
			break;
		case SDL_WINDOWEVENT_TAKE_FOCUS:     /**< ���ڱ��ṩ��һ������(Ӧ�ý�SetWindowInputFocus()������������Ӵ����ϣ����ߺ���)   */
			break;
		case SDL_WINDOWEVENT_HIT_TEST:       /**< Window had a hit test that wasn't SDL_HITTEST_NORMAL. */
			break;
		case SDL_WINDOWEVENT_ICCPROF_CHANGED:/**< The ICC profile of the window's display has changed. */
			break;
		case SDL_WINDOWEVENT_DISPLAY_CHANGED: /**< �����ƶ���data1��Ļ��ʾ */
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
			//���ԭ��û����꽹�㣬�ͳ�ʼ�����¼�
			if (!m_mouseFocus)
			{
				m_mouseFocus = true;
				enterEvent(ev);
			}
		}
		//���ԭ������꽹�㣬�����������û�е��ؼ��ϣ��ʹ����뿪�¼�
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

	//�����ڸ�������ʵ��Ӧ�û��Ƶľ�������
	SRect irect(frameGeometry());
	if (_parent)
	{
		SWidget* parentWidget = this->parentWidget();
		if (parentWidget)
		{
			//���Ӷ����ཻ����
			irect = parentWidget->rect().intersected(this->frameGeometry());
			//���Լ����Ͻ�����ڸ����������תΪ�����SWindow��ȫ������
			irect.moveLeftTop(parentWidget->mapTo(topLevelParentWidget(), irect.leftTop()));
			//std::clog << "_rrect " << _text << _rrect << std::endl;
			_rrect = irect;	//ʵ�ʻ��Ƶľ���

			//����������и�����������һ��,����ڵ�ǰ�������ʵ�ʻ�������
			auto pparent = parentWidget->parentWidget();
			if (pparent)
			{
				//���Ӷ����ཻ����
				irect = pparent->_rrect.intersected(irect);
			}
		}
	}

	//�����Լ�
	const SDL_Rect& sdlRect = _parent?irect.sdlRect(): _rect.sdlRect();
	SDL_SetRenderDrawColor(renderer, _bkColor.red(), _bkColor.green(), _bkColor.blue(), _bkColor.alpha());
	SDL_RenderFillRect(renderer, &sdlRect);

	//����Ҳ�ػ�
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
