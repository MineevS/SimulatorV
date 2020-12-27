#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include <QCursor>
#include <QPaintEvent>

#include "detector.h"
#include "Orientation.h"
//#include <formationconstructorscene.h>
#include "line_point.h"

#include <QDebug>

class FormationConstructorScene;
class Detector;
class Line_point;

class Ground :public QObject, public QGraphicsItem
{
    Q_OBJECT

    Q_INTERFACES(QGraphicsItem);

public:
    explicit Ground(QObject *parent = 0, ORIENTATION ort = ORIENTATION::From_top_To_bottom);
    //explicit Ground(QObject *parent = 0, Ground* GR = nullptr);
    ~Ground();

    //friend class FormationConstructorScene;

    FormationConstructorScene* fcs;

    QList<Detector*> QDC;
    Ground* D_GR;//
    ORIENTATION ort; // Переменная хранит ориентацию Ground.

signals:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

public slots:

protected:

};

#endif // MOVEITEM_H
