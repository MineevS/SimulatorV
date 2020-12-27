#ifndef ELECTRIC_LAMP_H
#define ELECTRIC_LAMP_H

#include <QObject>

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

//#include <QCursor>
//#include <QPaintEvent>

#include "Orientation.h"

#include "formationconstructorscene.h"
#include "detector.h"

#include <QDebug>

class FormationConstructorScene;
class Detector;

class Electric_Lamp : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem);

public:
    explicit Electric_Lamp(QObject *parent = 0, Orientation_lemp OL = Orientation_lemp::horizontally);
    ~Electric_Lamp();

    FormationConstructorScene* fcs;

    QList<Detector*> QDL;
    Orientation_lemp OL;

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *painter);// Не нужна.
    void drawLines(QPainter *qp);// Не нужна

};


#endif // ELECTRIC_LAMP_H
