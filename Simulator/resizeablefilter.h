#ifndef RESIZEABLEFILTER_H
#define RESIZEABLEFILTER_H

#include <QObject>


class ResizableFilter: public QObject
{
    Q_OBJECT
public:
    ResizableFilter(QObject* parent = 0);

protected:
    bool eventFilter(QObject* watched, QEvent* event );

private:
    bool m_rightBorderResizeFlag;
    bool m_leftBorderResizeFlag;
    bool m_topBorderResizeFlag;
    bool m_bottomBorderResizeFlag;
};

#endif // RESIZEABLEFILTER_H
