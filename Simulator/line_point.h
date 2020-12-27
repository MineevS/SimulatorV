#ifndef LINE_POINT_H
#define LINE_POINT_H


#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
//#include <QAbstractGraphicsShapeItem>
#include <QPaintEvent>

#include <QStyleOptionGraphicsItem>
#include <formationconstructorscene.h>
#include "Orientation.h"
//#include "Ground.h"
//#include "electric_lamp.h"
#include <QElapsedTimer>

#include "detector.h"

class FormationConstructorScene;
class Detector;

class Line_point : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem);
public:
    explicit Line_point(QObject *parent = 0, QList<Detector*> ptr = QList<Detector*>());

    ~Line_point();
    //QList<UTS> UT;

    FormationConstructorScene* fcs;
    QList<QPointF> LP;
    QList<Detector*> DT;
    //QObject* QOB;

    bool animat = false;
    bool Level = true;

private:
    int i = 0;
    int buff = 100;
    int shag = 5;
    int interval;

    QElapsedTimer timer;

signals:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public slots:

protected:
    void paintEvent(QPaintEvent *painter);
    void drawLines(QPainter *qp);

};

#endif // LINE_POINT_H
