#ifndef SELECTOR_H
#define SELECTOR_H

#include <QObject>
#include <QGraphicsItem>

#include "Orientation.h"

#include "formationconstructorscene.h"
#include "detector.h"

#include <QDebug>

class FormationConstructorScene;
class Detector;

class Selector : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem);
public:
    explicit Selector(QObject *parent = 0, Orientation_selector OL = Orientation_selector::hor);
    ~Selector();

    FormationConstructorScene* fcs;

    bool IN_OUT = false;

    QList<Detector*> QDS;
    Orientation_selector OS;

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // SELECTOR_H
