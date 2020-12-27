#include "electric_lamp.h"

#include <QDebug>
#include "formationconstructorview.h"
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QPainter>
#include "detector.h"
//#include "line_point.h"
#include <QApplication>
//+
Electric_Lamp::Electric_Lamp(QObject *parent, Orientation_lemp QOL) :
    QObject(parent), QGraphicsItem()
{
    //QAbstractGraphicsShapeItem()
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);

    this->OL=QOL;
}

//+-
Electric_Lamp::~Electric_Lamp()
{
    this->fcs->removeItem(QDL.last());
    this->fcs->removeItem(QDL.first());

    this->fcs->DETECTORS.removeOne(QDL.last());
    this->fcs->DETECTORS.removeOne(QDL.first());

    this->fcs->Lempsitems.removeOne(this);

    QDL.removeLast();
    QDL.removeFirst();

    scene()->update();
}

//+
QRectF Electric_Lamp::boundingRect() const
{
    /*
    Эта чисто виртуальная функция определяет внешние границы элемента как прямоугольник;
    вся живопись должна быть ограничена внутри ограничивающей прямой линии элемента.
    QGraphicsView этот параметр используется для определения необходимости перерисовки элемента.
    Хотя форма элемента может быть произвольной, ограничивающая прямая всегда прямоугольная, и на нее не влияет трансформация элементов.
    Если вы хотите изменить ограничивающий прямоугольник элемента, вы должны сначала вызвать prepareGeometryChange().
    Это уведомляет сцену о неизбежном изменении, так что она может обновить свой индекс геометрии элемента;
    в противном случае сцена не будет знать о новой геометрии элемента, и результаты будут неопределенными (как правило, артефакты рендеринга остаются внутри представления).
    Повторите эту функцию, чтобы QGraphicsView определил, какие части виджета, если таковые имеются, необходимо перерисовать.
    */

    return QRectF (-40,-40,80,80);// Определяет границы для последующих отрисовок данного элемента.
}

//+
void Electric_Lamp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int x_L, y_L;
    int x_R, y_R;

    QPen pen(Qt::black, 2 ,Qt::SolidLine);
    painter->setPen(pen);
    //painter->setPen(!(option->state & QStyle::State_Selected) ? Qt::yellow :  Qt::black);
    painter->setBrush( !(option->state & QStyle::State_Selected) ? Qt::yellow : Qt::green); // Смена Цвета.

    if(this->OL == Orientation_lemp::horizontally){

        painter->drawEllipse(-15,-15, 30, 30);
        painter->drawLine(15, 0 , 30, 0);
        painter->drawLine(-30, 0, -15, 0);

        painter->drawLine(-8, -10, 8, 10);
        painter->drawLine(8, -10, -8, 10);

        painter->setBrush( !(option->state & QStyle::State_Selected) ?  Qt::red :  Qt::magenta);

        painter->drawEllipse(-40, -4, 9, 9);
        painter->drawEllipse(30, -4, 9, 9);

        x_L = -36;
        y_L = -1;
        x_R = 34;
        y_R = -1;

    }else if(this->OL == Orientation_lemp::vertically){

        painter->drawEllipse(-15,-15, 30, 30);
        painter->drawLine(0, 15 , 0, 30);
        painter->drawLine(0, -30, 0, -15);

        painter->drawLine(-8, -10, 8, 10);
        painter->drawLine(8, -10, -8, 10);

        painter->setBrush( !(option->state & QStyle::State_Selected) ? Qt::red : Qt::magenta);

        painter->drawEllipse(-4, -40, 9, 9);//?
        painter->drawEllipse(-4, 30, 9, 9);//?

        x_L = 0;
        y_L = -37;
        x_R = 0;
        y_R = 33;
    }

    //////////////////////////////////////////////////

    if(QDL.empty()){

        //qDebug() << "Проверка № 1.1";

        Detector* Detect_L = new Detector(this, this->OL);
        Detector* Detect_R = new Detector(this, this->OL);

        Detect_L->setPos(this->pos().x() + x_L, this->pos().y() + y_L);
        Detect_R->setPos(this->pos().x() + x_R, this->pos().y() + y_R);

        Detect_R->R_N = true;
        Detect_L->L_V = true;

        Detect_L->DT.append(Detect_R);
        Detect_R->DT.append(Detect_L);

        this->scene()->addItem(Detect_L);
        this->scene()->addItem(Detect_R);

        Detect_L->fcs = this->fcs;
        Detect_R->fcs = this->fcs;

        this->fcs->DETECTORS.append(Detect_L);
        this->fcs->DETECTORS.append(Detect_R);

        this->QDL.append(Detect_L);
        this->QDL.append(Detect_R);

        Detect_L->UT.ELD = this;
        Detect_R->UT.ELD = this;

        //qDebug() << "Проверка № 1.2";

    }else if(!QDL.empty())
    {
        QDL.first()->setPos(this->pos().x() + x_L, this->pos().y() + y_L);
        QDL.last()->setPos(this->pos().x() + x_R, this->pos().y() + y_R);

        QDL.first()->update();
        QDL.last()->update();

    }
    else if(!QDL.empty() && isUnderMouse() && (option->state & QStyle::State_Selected) && (QApplication::mouseButtons() & Qt::LeftButton))//Проверка, что нажата нопка
    {
        QDL.first()->setPos(this->pos().x() + x_L, this->pos().y() + y_L);
        QDL.last()->setPos(this->pos().x() + x_R, this->pos().y() + y_R);

        QDL.first()->setSelected(true);
        QDL.last()->setSelected(true);

        QDL.first()->update();
        QDL.last()->update();


    }else if(!QDL.empty() && isUnderMouse() && (option->state & QStyle::State_Selected))
    {
        //
    }else if (QDL.first()->isSelected() && QDL.last()->isSelected()){

        QDL.first()->setPos(this->pos().x() + x_L, this->pos().y() + y_L);
        QDL.last()->setPos(this->pos().x() + x_R, this->pos().y() + y_R);

        QDL.first()->setSelected(false);
        QDL.last()->setSelected(false);

        QDL.first()->update();
        QDL.last()->update();

    }else{

        QDL.first()->setPos(this->pos().x() + x_L, this->pos().y() + y_L);
        QDL.last()->setPos(this->pos().x() + x_R, this->pos().y() + y_R);

        QDL.first()->setSelected(QDL.first()->isSelected());
        QDL.last()->setSelected(QDL.last()->isSelected());

        QDL.first()->update();
        QDL.last()->update();

    }

    /////////////////////////////////////////////////

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//+
void Electric_Lamp::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    this->setPos(mapToScene(event->pos()));
}

//+-
void Electric_Lamp::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void Electric_Lamp::paintEvent(QPaintEvent* painter)
{
    Q_UNUSED(painter);

    qDebug() << "Проверка № 34";

    QPainter qp;
    drawLines(&qp);
}

void Electric_Lamp::drawLines(QPainter *qp)
{
    QPen pen(Qt::black, 7, Qt::SolidLine);
    qp->setPen(pen);
    qp->drawLine(-10, 5, 20, 20);

}
