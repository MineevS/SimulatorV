#include "battery.h"
/*
Battery::Battery()
{

}
*/

Battery::Battery(QObject *parent, Orientation_battery OB)
{
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);

    this->OB = OB;

    Q_UNUSED(parent);
    Q_UNUSED(OB);
}

Battery::~Battery()
{

    this->fcs->removeItem(QDB.last());
    this->fcs->removeItem(QDB.first());

    this->fcs->DETECTORS.removeOne(QDB.last());
    this->fcs->DETECTORS.removeOne(QDB.first());

    this->fcs->BatteryItems.removeOne(this);

    QDB.removeLast();
    QDB.removeFirst();


    scene()->update();
}

QRectF Battery::boundingRect() const
{
    return QRectF(-40,-40,80,80);
}

void Battery::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int x_L, y_L;
    int x_R, y_R;
    bool L = false, R = false;

    QPen pen(Qt::black, 2 ,Qt::SolidLine);
    painter->setPen(pen);
    painter->setBrush( !(option->state & QStyle::State_Selected) ? Qt::yellow : Qt::green); // Смена Цвета.



    if(this->OB == Orientation_battery::BTR_horV){

        if(this->IN_OUT == true){

        //painter->drawLine(-30, 0, 30, 0); // L

        }else if(this->IN_OUT == false){

            QFont Font_1(painter->font());
            Font_1.setPointSize(13);
            painter->setFont(Font_1);

            painter->drawText(5, -5,"+");
            painter->drawText(-13, -3,"-");

            painter->drawLine(3, -12 , 3, 12); // VR
            painter->drawLine(-3, -7, -3, 7); // VL

            painter->drawLine(3, 0 , 30, 0); // R
            painter->drawLine(-30, 0, -3, 0); // L



            //painter->drawLine(-15, 0, 12, -18);
        }

        painter->setBrush( !(option->state & QStyle::State_Selected) ?  Qt::red :  Qt::magenta);

        painter->drawEllipse(-40, -4, 9, 9);
        painter->drawEllipse(30, -4, 9, 9);

        x_L = -36;
        y_L = -1;
        x_R = 34;
        y_R = -1;

        L = false;
        R = true;

    }else if(this->OB == Orientation_battery::BTR_horN){

        if(this->IN_OUT == true){

        painter->drawLine(-30, 0, 30, 0); // L

        }else if(this->IN_OUT == false){

            QFont Font_1(painter->font());
            Font_1.setPointSize(13);
            painter->setFont(Font_1);

            painter->drawText(5, 15,"+");
            painter->drawText(-12, 12,"-");

            painter->drawLine(3, -12 , 3, 12); // VR
            painter->drawLine(-3, -7, -3, 7); // VL

            painter->drawLine(3, 0 , 30, 0); // R
            painter->drawLine(-30, 0, -3, 0); // L

            //painter->drawLine(15, 0 , 30, 0); // R
            //painter->drawLine(-30, 0, -15, 0); // L

            //painter->drawLine(-15, 0, 12, +18);
        }

        painter->setBrush( !(option->state & QStyle::State_Selected) ?  Qt::red :  Qt::magenta);

        painter->drawEllipse(-40, -4, 9, 9);
        painter->drawEllipse(30, -4, 9, 9);

        x_L = -36;
        y_L = -1;
        x_R = 34;
        y_R = -1;

        L = false;
        R = true;

    }else if(this->OB == Orientation_battery::BTR_verL){

        if(this->IN_OUT == true){

        painter->drawLine(0, -30, 0, 30); // L

        }else if(this->IN_OUT == false){

            QFont Font_1(painter->font());
            Font_1.setPointSize(13);
            painter->setFont(Font_1);

            painter->drawText(7, 18,"+");

            Font_1.setPointSize(7);
            painter->setFont(Font_1);

            painter->drawText(5, -8,"|");

            painter->drawLine(-12, 3 , 12, 3); // HR
            painter->drawLine(-7, -3, 7, -3); // HL

            painter->drawLine(0, 3 , 0, 30); // R
            painter->drawLine(0, -30, 0, -3); // L

            //painter->drawLine(0, -15, 18, 12);
        }

        painter->setBrush( !(option->state & QStyle::State_Selected) ?  Qt::red :  Qt::magenta);

        painter->drawEllipse(-4, -40, 9, 9);
        painter->drawEllipse(-4, 30, 9, 9);

        x_L = 0;
        y_L = -37;
        x_R = 0;
        y_R = 33;



    }else if(this->OB == Orientation_battery::BTR_verR){

        if(this->IN_OUT == true){

        painter->drawLine(0, -30, 0, 30); // L

        }else if(this->IN_OUT == false){

            QFont Font_1(painter->font());
            Font_1.setPointSize(13);
            painter->setFont(Font_1);

            painter->drawText(-18, 16,"+");

            Font_1.setPointSize(6);
            painter->setFont(Font_1);

            painter->drawText( -10, -8,"|");

            painter->drawLine(-12, 3 , 12, 3); // HR
            painter->drawLine(-7, -3, 7, -3); // HL

            painter->drawLine(0, 3 , 0, 30); // R
            painter->drawLine(0, -30, 0, -3); // L


            //painter->drawLine(0, 15 , 0, 30); // R
            //painter->drawLine(0, -30, 0, -15); // L

            //painter->drawLine(0, -15, -18, 12);
        }

        painter->setBrush( !(option->state & QStyle::State_Selected) ?  Qt::red :  Qt::magenta);

        painter->drawEllipse(-4, -40, 9, 9);
        painter->drawEllipse(-4, 30, 9, 9);

        x_L = 0;
        y_L = -37;
        x_R = 0;
        y_R = 33;
    }

    ///////////////////////////////////////////////////////////////////////////

    if(QDB.empty()){

        //qDebug() << "Проверка № 1.1";

        Detector* Detect_L = new Detector(this, this->OB);
        Detector* Detect_R = new Detector(this, this->OB);

        Detect_L->setPos(this->pos().x() + x_L, this->pos().y() + y_L);
        Detect_R->setPos(this->pos().x() + x_R, this->pos().y() + y_R);

        Detect_L->SIGN = L;
        Detect_R->SIGN = R;

        Detect_L->Level = true;
        Detect_R->Level = true;

        Detect_L->DT.append(Detect_R);
        Detect_R->DT.append(Detect_L);

        this->scene()->addItem(Detect_L);
        this->scene()->addItem(Detect_R);

        Detect_L->fcs = this->fcs;
        Detect_R->fcs = this->fcs;

        this->fcs->DETECTORS.append(Detect_L);
        this->fcs->DETECTORS.append(Detect_R);

        this->QDB.append(Detect_L);
        this->QDB.append(Detect_R);

        Detect_L->UT.BTR = this;
        Detect_R->UT.BTR = this;

        //qDebug() << "Проверка № 1.2";

    }else if(!QDB.empty()){

        QDB.first()->setPos(this->pos().x() + x_L, this->pos().y() + y_L);
        QDB.last()->setPos(this->pos().x() + x_R, this->pos().y() + y_R);

        QDB.first()->update();
        QDB.last()->update();
    }

    //////////////////////////////////////////////

    //Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Battery::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    this->setPos(mapToScene(event->pos()));

   Q_UNUSED(event);
}

void Battery::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}
