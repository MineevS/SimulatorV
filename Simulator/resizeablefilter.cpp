#include "resizeablefilter.h"

//#include <QHBoxLayout>
//#include <QPushButton>
#include <QComboBox>
#include <QMouseEvent>

ResizableFilter::ResizableFilter(QObject* parent)
    : QObject(parent),
    m_rightBorderResizeFlag(false),
    m_leftBorderResizeFlag(false),
    m_topBorderResizeFlag(false),
    m_bottomBorderResizeFlag(false)
{

}

bool ResizableFilter::eventFilter(QObject* watched, QEvent* event )
{
    QWidget* watchedWgt = qobject_cast<QWidget*>(watched);
    watchedWgt->setMouseTracking(true);
    QMouseEvent* mEvent = static_cast<QMouseEvent*>(event);
    QRect wgtRect = watchedWgt->rect();
    const quint16 SENSIBLE_INDENT = 3;

    auto isRightBorderResizable = [&, this]()->bool
    {
        Q_UNUSED(this);

        return mEvent->pos().x() <= (wgtRect.right() + SENSIBLE_INDENT) && mEvent->pos().x() >= (wgtRect.right() - SENSIBLE_INDENT);
    };
    auto isLeftBorderResizable = [&, this]()->bool
    {
        Q_UNUSED(this);

        return mEvent->pos().x() <= (wgtRect.left() + SENSIBLE_INDENT) && mEvent->pos().x() >= (wgtRect.left() - SENSIBLE_INDENT);
    };
    auto isTopBorderResizable = [&, this]()->bool
    {
        Q_UNUSED(this);

        return mEvent->pos().y() <= (wgtRect.top() + SENSIBLE_INDENT) && mEvent->pos().y() >= (wgtRect.top() - SENSIBLE_INDENT);
    };
    auto isBottomBorderResizable = [&, this]()->bool
    {
        Q_UNUSED(this);
        return mEvent->pos().y() <= (wgtRect.bottom() + SENSIBLE_INDENT) && mEvent->pos().y() >= (wgtRect.bottom() - SENSIBLE_INDENT);
    };

    switch(event->type())
    {
        case QEvent::MouseButtonPress:
        {
            if(isRightBorderResizable())
            {
                m_rightBorderResizeFlag = true;
                return true;
            }
            else if(isLeftBorderResizable())
            {
                m_leftBorderResizeFlag = true;
                return true;
            }
            else if(isTopBorderResizable())
            {
                m_topBorderResizeFlag = true;
                return true;
            }
            else if(isBottomBorderResizable())
            {
                m_bottomBorderResizeFlag = true;
                return true;
            }
        }

        break;

         case QEvent::MouseButtonRelease:
        {
            m_rightBorderResizeFlag = false;
            m_leftBorderResizeFlag = false;
            m_topBorderResizeFlag = false;
            m_bottomBorderResizeFlag = false;
        }

        break;

        case QEvent::MouseMove:
        {
            if(isRightBorderResizable() || isLeftBorderResizable())
                watchedWgt->setCursor(Qt::SizeHorCursor);
            else if(isTopBorderResizable() || isBottomBorderResizable())
                watchedWgt->setCursor(Qt::SizeVerCursor);
            else
                watchedWgt->setCursor(Qt::ArrowCursor);

            QRect wgtGeometry = watchedWgt->geometry();
            if(m_rightBorderResizeFlag)
            {
                wgtGeometry.setWidth(mEvent->pos().x());
            }
            else if(m_leftBorderResizeFlag)
            {
                QPoint newPosition = watchedWgt->mapToParent(mEvent->pos());
                QPoint oldBottomRight = wgtGeometry.bottomRight();
                wgtGeometry.setX(newPosition.x());
                wgtGeometry.setBottomRight(oldBottomRight);
            }
            else if(m_topBorderResizeFlag)
            {
                QPoint newPosition = watchedWgt->mapToParent(mEvent->pos());
                QPoint oldBottomRight = wgtGeometry.bottomRight();
                wgtGeometry.setY(newPosition.y());
                wgtGeometry.setBottomRight(oldBottomRight);
            }
            else if(m_bottomBorderResizeFlag)
            {
                QPoint newPosition = watchedWgt->mapToParent(mEvent->pos());
                QPoint oldTopLeft = wgtGeometry.topLeft();
                wgtGeometry.setBottom(newPosition.y());
                wgtGeometry.setTopLeft(oldTopLeft);
            }
            watchedWgt->setGeometry(wgtGeometry);
        }

        default:
            break;
    }

    return QObject::eventFilter(watched, event);
}
