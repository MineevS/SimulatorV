#include "selector.h"

Selector::Selector(QObject *parent, Orientation_selector OS)
{
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);

    this->OS = OS;

    Q_UNUSED(parent);
    Q_UNUSED(OS);
}

Selector::~Selector()
{
    this->fcs->removeItem(QDS.last());
    this->fcs->removeItem(QDS.first());

    this->fcs->DETECTORS.removeOne(QDS.last());
    this->fcs->DETECTORS.removeOne(QDS.first());

    this->fcs->SelectorItems.removeOne(this);

    QDS.removeLast();
    QDS.removeFirst();

    scene()->update();
}

QRectF Selector::boundingRect() const
{
    return QRectF(-40,-40,80,80);
}

void Selector::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int x_L, y_L;
    int x_R, y_R;

    QPen pen(Qt::black, 2 ,Qt::SolidLine);
    painter->setPen(pen);
    painter->setBrush( !(option->state & QStyle::State_Selected) ? Qt::yellow : Qt::green); // Смена Цвета.

    if(this->OS == Orientation_selector::horV){

        if(this->IN_OUT == true){

        painter->drawLine(-30, 0, 30, 0); // L

        }else if(this->IN_OUT == false){

            painter->drawLine(15, 0 , 30, 0); // R
            painter->drawLine(-30, 0, -15, 0); // L

            painter->drawLine(-15, 0, 12, -18);
        }

        painter->setBrush( !(option->state & QStyle::State_Selected) ?  Qt::red :  Qt::magenta);

        painter->drawEllipse(-40, -4, 9, 9);
        painter->drawEllipse(30, -4, 9, 9);

        x_L = -36;
        y_L = -1;
        x_R = 34;
        y_R = -1;

    }else if(this->OS == Orientation_selector::horN){

        if(this->IN_OUT == true){

        painter->drawLine(-30, 0, 30, 0); // L

        }else if(this->IN_OUT == false){

            painter->drawLine(15, 0 , 30, 0); // R
            painter->drawLine(-30, 0, -15, 0); // L

            painter->drawLine(-15, 0, 12, +18);
        }

        painter->setBrush( !(option->state & QStyle::State_Selected) ?  Qt::red :  Qt::magenta);

        painter->drawEllipse(-40, -4, 9, 9);
        painter->drawEllipse(30, -4, 9, 9);

        x_L = -36;
        y_L = -1;
        x_R = 34;
        y_R = -1;

    }else if(this->OS == Orientation_selector::verL){

        if(this->IN_OUT == true){

        painter->drawLine(0, -30, 0, 30); // L

        }else if(this->IN_OUT == false){

            painter->drawLine(0, 15 , 0, 30); // R
            painter->drawLine(0, -30, 0, -15); // L

            painter->drawLine(0, -15, 18, 12);
        }

        painter->setBrush( !(option->state & QStyle::State_Selected) ?  Qt::red :  Qt::magenta);

        painter->drawEllipse(-4, -40, 9, 9);
        painter->drawEllipse(-4, 30, 9, 9);

        x_L = 0;
        y_L = -37;
        x_R = 0;
        y_R = 33;

    }else if(this->OS == Orientation_selector::verR){

        if(this->IN_OUT == true){

        painter->drawLine(0, -30, 0, 30); // L

        }else if(this->IN_OUT == false){

            painter->drawLine(0, 15 , 0, 30); // R
            painter->drawLine(0, -30, 0, -15); // L

            painter->drawLine(0, -15, -18, 12);
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

    if(QDS.empty()){

        //qDebug() << "Проверка № 1.1";

        Detector* Detect_L = new Detector(this, this->OS);
        Detector* Detect_R = new Detector(this, this->OS);

        Detect_L->setPos(this->pos().x() + x_L, this->pos().y() + y_L);
        Detect_R->setPos(this->pos().x() + x_R, this->pos().y() + y_R);

        Detect_L->DT.append(Detect_R);
        Detect_R->DT.append(Detect_L);

        this->scene()->addItem(Detect_L);
        this->scene()->addItem(Detect_R);

        Detect_L->fcs = this->fcs;
        Detect_R->fcs = this->fcs;

        this->fcs->DETECTORS.append(Detect_L);
        this->fcs->DETECTORS.append(Detect_R);

        this->QDS.append(Detect_L);
        this->QDS.append(Detect_R);

        Detect_L->UT.SLD = this;
        Detect_R->UT.SLD = this;

        //qDebug() << "Проверка № 1.2";

    }else if(!QDS.empty()){

        QDS.first()->setPos(this->pos().x() + x_L, this->pos().y() + y_L);
        QDS.last()->setPos(this->pos().x() + x_R, this->pos().y() + y_R);

        QDS.first()->update();
        QDS.last()->update();
    }

    //////////////////////////////////////////////

    //Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Selector::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    this->setPos(mapToScene(event->pos()));

   Q_UNUSED(event);
}

void Selector::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}
