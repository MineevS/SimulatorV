#include "detector.h"

#include <QDebug>
#include "formationconstructorview.h"
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QPainter>
#include <QApplication>
#include <QString>

//+
Detector::Detector(QObject *parent, ORIENTATION ort_to) :
    QObject(parent), QGraphicsItem()
{
    setFlag(ItemIsSelectable);              //  Элемент поддерживает выбор.
    setFlag(ItemIsMovable);                 //  Элемент поддерживает интерактивное перемещение с помощью мыши.
    setFlag(ItemSendsGeometryChanges);      //  Элемент поддерживает измененеие позиции относительно всей сцены.

    this->ort = ort_to;                     //Передача ориентации объекта: GROUND.
}

Detector::Detector(QObject *parent, Orientation_lemp OL)
{
    setFlag(ItemIsSelectable);//Элемент поддерживает выбор.
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);

    Q_UNUSED(parent);

    this->OL = OL;//Передача ориентации объекта: ELECTRICK_LEMP.
}

Detector::Detector(QObject *parent, Orientation_selector OS)
{
    setFlag(ItemIsSelectable);//Элемент поддерживает выбор.
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);

    this->OS = OS;

    Q_UNUSED(parent);
}

Detector::Detector(QObject *parent, Orientation_battery OB)
{
    setFlag(ItemIsSelectable);//Элемент поддерживает выбор.
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);

    this->OB = OB;

    Q_UNUSED(parent);
}

//+
Detector::~Detector()
{
    //TODO
}

//+
QRectF Detector::boundingRect() const
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
    //return QRectF (-30,-30,60,60)
    return QRectF (-5, -5, 10, 10);// Определяет границы для последующих отрисовок данного элемента.
}

//+
void Detector::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //QPen pen(Qt::black, 1 ,Qt::SolidLine);
    //painter->setPen(pen);
    //qDebug() << (bool)(option->state & QStyle::State_Selected);
        //qDebug() << this->isSelected();
    //qDebug() << this->cursor().pos();
    //qDebug() << this->pos();
    //qDebug() << option->state;

    //qDebug() << "Проверка № 78: " << (bool)!(option->state & QStyle::State_Selected);
    //qDebug() << QApplication::mouseButtons();
    //qDebug() << ++i;
    //qDebug() << this->isUnderMouse();
    //qDebug() << this->acceptedMouseButtons();

    //qDebug() << this->isSelected();

    if(!(option->state & QStyle::State_Selected)){

        //qDebug() << this->isSelected();
        painter->setPen(!(option->state & QStyle::State_Selected) ? Qt::yellow :  Qt::gray);
        painter->setBrush( !(option->state & QStyle::State_Selected) ? Qt::blue : Qt::yellow); // Смена Цвета.
        painter->setOpacity(!(option->state & QStyle::State_Selected) ? 0.1 : 1);
        painter->drawEllipse(-4,-3, 9, 9);



        if(LPs.size() > 0){

        foreach(Line_point* LPS, this->fcs->Line_points){

            foreach(Detector* DT, LPS->DT){

                if(DT == this){

                    //qDebug() << LPS->DT.indexOf(DT);



                    LPS->LP[LPS->DT.indexOf(DT)].setX(this->pos().x());
                    LPS->LP[LPS->DT.indexOf(DT)].setY(this->pos().y());

                    LPS->update();

                    }
                }
            }
        }

        //QPen pen(Qt::black, 5 ,Qt::SolidLine);

        //painter->setPen(pen);

        //int x = this->pos().x();
        //int y = this->pos().y();
       // painter->drawText(0, 0, "Сообщение № 1");

    }else{

        //qDebug() << this->isSelected();

        painter->setPen(!(option->state & QStyle::State_Selected) ? Qt::yellow :  Qt::gray);
        painter->setBrush( !(option->state & QStyle::State_Selected) ? Qt::blue : Qt::yellow); // Смена Цвета.
        painter->setOpacity(!(option->state & QStyle::State_Selected) ? 0.1 : 1);
        painter->drawEllipse(-4,-3, 9, 9);  
    }

    //QPen pen(Qt::black, 5 ,Qt::SolidLine);

    //painter->setPen(pen);
    //painter->setPen(!(option->state & QStyle::State_Selected) ? Qt::black :  Qt::black);

    //painter->drawText(0, 0, "Сообщение № 2");

    //qDebug() <<"X: "  << x;
    //((QString)x +  " : " + (QString)y)

   //QTextItem mes(");

    //painter->drawTextItem(x,y,)



   // painter->drawText(, "Mes" );


    ///////////////////////////////////
    ///Повторная отрисовка прямой линии.

    //this->LPs;// Хранит  Line_point-S, которые нужно обновлять.

/*
    foreach(Line_point* LP, LPs){

        foreach(Detector* DT, LP->DT){

            if(DT == this){

                qDebug() << LP->DT.indexOf(DT);

              //LP[LP->DT.indexOf(DT)].setPos(this->pos());
              LP->update();
            }
        }
    }*/

    //////////////////////////////////

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//+
void Detector::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
   // this->setPos(mapToScene(event->pos()));

    Q_UNUSED(event);
}

//+-
void Detector::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    //this->setCursor(QCursor(Qt::ArrowCursor));

    Q_UNUSED(event);
}

void Detector::drawLines(QPainter *qp)
{
    QPen pen(Qt::black, 7, Qt::SolidLine);
    qp->setPen(pen);
    qp->drawLine(-10, 5, 20, 20);
}
