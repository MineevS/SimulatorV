#ifndef BATTERY_H
#define BATTERY_H

#include <QObject>
#include <QGraphicsItem>

#include "formationconstructorscene.h"

#include "Orientation.h"
#include "detector.h"

#include <QDebug>

class FormationConstructorScene;
class Detector;

class Battery : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem);
public:
    explicit Battery(QObject *parent = 0, Orientation_battery OB = Orientation_battery::BTR_horV);
    ~Battery();

    FormationConstructorScene* fcs;

    bool IN_OUT = false;

    QList<Detector*> QDB;
    Orientation_battery OB;

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // BATTERY_H
