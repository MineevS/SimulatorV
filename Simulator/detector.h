#ifndef DETECTOR_H
#define DETECTOR_H

#include <QObject>
#include <QGraphicsItem>

//#include <QPainter>
//#include <QGraphicsSceneMouseEvent>
//#include <QPaintEvent>
//#include <QCursor>
//#include "formationconstructorscene.h"

#include <QDebug>

#include "Orientation.h"

#include "Ground.h"
#include "electric_lamp.h"
#include "battery.h"

#include "line_point.h"

// INP && OUT
class Line_point;

//OUT && INP
class Ground;
class Electric_Lamp;
class Selector;
class Battery;

class Detector : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem);

public:
    explicit Detector(QObject *parent = 0, ORIENTATION ort = ORIENTATION::From_bottom_To_top);
    explicit Detector(QObject *parent = 0, Orientation_lemp OL = Orientation_lemp::horizontally);
    explicit Detector(QObject *parent = 0, Orientation_selector OS = Orientation_selector::horV);
    explicit Detector(QObject *parent = 0, Orientation_battery OB = Orientation_battery::BTR_horV);

    ~Detector();

    FormationConstructorScene* fcs;

    ORIENTATION ort;
    Orientation_lemp OL;
    Orientation_selector OS;
    Orientation_battery OB;

    /*
     *  Храним знак детектора:
     *  True: + ;
     *  False: - ;
    */

    bool SIGN = false;

    /*
     *  Храним уровень детектора:
     *  True: 1(Первый) - Фиксированный знак(SIGN) ;
     *  False: 0(Нулевой) - Нефиксированный знак(SIGN) ;
    */

    bool Level = false;

    /*
     *  Храним знак детектора для GROUND:
     *  True: + ;
     *  False: - ;
    */

    bool SIGN_V = false;
    bool SIGN_N = false;

    bool SIGN_L = false;
    bool SIGN_R = false;

    //Detector должен хранить массив удерживающих им линий.
    QList<Line_point*> LPs;

    union UTS{
        Electric_Lamp* ELD;
        Ground* GD;
        Selector* SLD;
        Battery* BTR;

    };

    UTS UT;

    bool L_V = false;
    bool R_N = false;

    QList<Detector*> DT;
signals:

public slots:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

protected:
    void drawLines(QPainter *qp);

};
#endif // DETECTOR_H
