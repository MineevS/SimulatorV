#include "line_point.h"
#include <QTime>
#include <QElapsedTimer>

Line_point::Line_point(QObject *parent, QList<Detector*> ptr)
{
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);


   // QOB = parent;

    DT = ptr;
    LP.append(ptr.first()->pos());
    LP.append(ptr.last()->pos());

    Q_UNUSED(parent);
}

Line_point::~Line_point()
{
    // TODO;

   this->fcs->Line_points.removeOne(this);
}

QRectF Line_point::boundingRect() const
{    /*
    Эта чисто виртуальная функция определяет внешние границы элемента как прямоугольник;
    вся живопись должна быть ограничена внутри ограничивающей прямой линии элемента.
    QGraphicsView этот параметр используется для определения необходимости перерисовки элемента.
    Хотя форма элемента может быть произвольной, ограничивающая прямая всегда прямоугольная, и на нее не влияет трансформация элементов.
    Если вы хотите изменить ограничивающий прямоугольник элемента, вы должны сначала вызвать prepareGeometryChange().
    Это уведомляет сцену о неизбежном изменении, так что она может обновить свой индекс геометрии элемента;
    в противном случае сцена не будет знать о новой геометрии элемента, и результаты будут неопределенными (как правило, артефакты рендеринга остаются внутри представления).
    Повторите эту функцию, чтобы QGraphicsView определил, какие части виджета, если таковые имеются, необходимо перерисовать.
    */

    //this->DT.first()->x();

    if((this->LP.first().x() < this->LP.last().x()) | (this->LP.first().y() < this->LP.last().y())){

        return QRectF (this->LP.first().x(), this->LP.first().y(), this->LP.last().x() - this->LP.first().x(), this->LP.last().y() - this->LP.first().y());
    }else if((this->LP.last().x() < this->LP.first().x()) | (this->LP.last().y() < this->LP.first().y())){

        return QRectF (this->LP.first().x(), this->LP.first().y(), this->LP.last().x() - this->LP.first().x(), this->LP.last().y() - this->LP.first().y());
    }

    return QRectF (this->LP.first().x() + 0,this->LP.first().y() + 0, this->LP.last().x() + 0, this->LP.last().y() + 0);// Определяет границы для последующих отрисовок данного элемента.
    //return QRectF (this->DT.first()->x(), this->DT.first()->y(), this->DT.last()->x() - this->DT.first()->x(), this->DT.last()->y() - this->DT.first()->y());// Определяет границы для последующих отрисовок данного элемента.
}



void Line_point::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPen pen(Qt::black, 3 ,Qt::SolidLine);
    painter->setPen(pen);
    painter->setBrush( !(option->state & QStyle::State_Selected) ? Qt::blue : Qt::yellow); // Смена Цвета.
    int sh = 5;
    if((this->LP.first().x() == this->LP.last().x()) | (this->LP.first().y() == this->LP.last().y()) | ((this->LP.first().x() - this->LP.last().x() < sh) && (this->LP.first().x() - this->LP.last().x() > (-sh))) | ((this->LP.first().y() - this->LP.last().y() < sh) && (this->LP.first().y() - this->LP.last().y() > (-sh)))){

        if((this->LP.first().x() == this->LP.last().x()) | ((this->LP.first().x() - this->LP.last().x() < sh) && (this->LP.first().x() - this->LP.last().x() > (-sh))))
        {
            if(this->LP.first().y() < this->LP.last().y()){

                //qDebug() << "Проверка № 1";

                painter->drawLine(this->LP.first().x() + 1,this->LP.first().y() + 6, this->LP.last().x() + 1 , this->LP.last().y() - 4);

            }else if(this->LP.first().y() > this->LP.last().y()){

                //qDebug() << "Проверка № 2";

                painter->drawLine(this->LP.first().x() + 1,this->LP.first().y() - 5, this->LP.last().x() + 1 , this->LP.last().y() + 7);
            }
        }
        else if((this->LP.first().y() == this->LP.last().y()) | ((this->LP.first().y() - this->LP.last().y() < sh) && (this->LP.first().y() - this->LP.last().y() > (-sh))))
        {
            if(this->LP.first().x() < this->LP.last().x()){

                //qDebug() << "Проверка № 3";
                painter->drawLine(this->LP.first().x() + 6,this->LP.first().y() + 1, this->LP.last().x() - 6 , this->LP.last().y() + 1);//#1

            }else if(this->LP.first().x() > this->LP.last().x()){

                //qDebug() << "Проверка № 4";

                painter->drawLine(this->LP.last().x() + 6,this->LP.last().y() + 1, this->LP.first().x() - 6 , this->LP.first().y() + 1);
            }
        }
    }else if((LP.first().x() - LP.last().x() >= sh) && (LP.first().y() - LP.last().y() >= sh)){
        // 4 четверть.

        foreach(auto DT, this->DT)
        {

            if((DT->pos().x() == LP.first().x()) && (DT->pos().y() == LP.first().y()) && (DT->R_N))
            {qDebug() << "4.1 четверть";

                painter->drawLine(this->LP.first().x() + 1,this->LP.first().y() - 5, this->LP.first().x() + 1 , this->LP.last().y() + 1);
                painter->drawLine(this->LP.last().x() + 6, this->LP.last().y() + 1, this->LP.first().x() + 1, this->LP.last().y() + 1);


            }else if((DT->pos().x() == LP.first().x()) && (DT->pos().y() == LP.first().y()) && (DT->L_V))
            {qDebug() << "4.2 четверть";

                painter->drawLine(this->LP.first().x() + 1,this->LP.first().y() - 5, this->LP.first().x() + 1 , this->LP.last().y() + 1);
                painter->drawLine(this->LP.last().x() + 6, this->LP.last().y() + 1, this->LP.first().x() + 1, this->LP.last().y() + 1);
            }

            if((DT->pos().x() == LP.last().x()) && (DT->pos().y() == LP.last().y()) && (DT->R_N))
            {qDebug() << "4.3 четверть";
                painter->drawLine(this->LP.first().x() + 1,this->LP.first().y() - 5, this->LP.first().x() + 1 , this->LP.last().y() + 1);
                painter->drawLine(this->LP.last().x() + 6, this->LP.last().y() + 1, this->LP.first().x() + 1, this->LP.last().y() + 1);


            }else if((DT->pos().x() == LP.last().x()) && (DT->pos().y() == LP.last().y()) && (DT->L_V))
            {qDebug() << "4.4 четверть";

                painter->drawLine(this->LP.first().x() - 5,this->LP.first().y() + 1, this->LP.last().x() + 1 , this->LP.first().y() + 1);//+
                painter->drawLine(this->LP.last().x() + 0, this->LP.last().y() + 7, this->LP.last().x() + 0, this->LP.first().y() + 1);//+
            }
        }

    }else if((LP.first().x() - LP.last().x() <= -sh) && (LP.first().y() - LP.last().y() <= -sh)){

        foreach(auto DT, this->DT)
        {// 2 четверть.

            if((DT->pos().x() == LP.first().x()) && (DT->pos().y() == LP.first().y()) && (DT->R_N))
            { qDebug() << "2.1 четверть";

                painter->drawLine(this->LP.first().x() + 6,this->LP.first().y() + 1, this->LP.last().x() + 0 , this->LP.first().y() + 1);
                painter->drawLine(this->LP.last().x() + 1, this->LP.first().y() + 1, this->LP.last().x() + 1, this->LP.last().y() - 5);//

            }else if((DT->pos().x() == LP.first().x()) && (DT->pos().y() == LP.first().y()) && (DT->L_V))
            {qDebug() << "2.2 четверть";//+

                //painter->drawLine(this->LP.first().x() + 6,this->LP.first().y() + 1, this->LP.last().x() + 0 , this->LP.first().y() + 1);
                //painter->drawLine(this->LP.last().x() + 1, this->LP.first().y() + 1, this->LP.last().x() + 1, this->LP.last().y() - 5);//

                painter->drawLine(this->LP.first().x() + 0,this->LP.first().y() + 7, this->LP.first().x() + 0 , this->LP.last().y() + 0);//++
                painter->drawLine(this->LP.last().x() - 5, this->LP.last().y() + 0, this->LP.first().x() + 0, this->LP.last().y() + 0);//++
            }

            if((DT->pos().x() == LP.last().x()) && (DT->pos().y() == LP.last().y()) && (DT->R_N))
            { qDebug() << "2.3 четверть";//+

                painter->drawLine(this->LP.first().x() + 6,this->LP.first().y() + 1, this->LP.last().x() + 0 , this->LP.first().y() + 1);
                painter->drawLine(this->LP.last().x() + 1, this->LP.first().y() + 1, this->LP.last().x() + 1, this->LP.last().y() - 5);//

            }else if((DT->pos().x() == LP.last().x()) && (DT->pos().y() == LP.last().y()) && (DT->L_V))
            {qDebug() << "2.4 четверть";//+

                //painter->drawLine(this->LP.first().x() + 6,this->LP.first().y() + 1, this->LP.last().x() + 0 , this->LP.first().y() + 1);
                //painter->drawLine(this->LP.last().x() + 1, this->LP.first().y() + 1, this->LP.last().x() + 1, this->LP.last().y() - 5);//

                painter->drawLine(this->LP.first().x() + 6,this->LP.first().y() + 1, this->LP.last().x() + 0 , this->LP.first().y() + 1);
                painter->drawLine(this->LP.last().x() + 1, this->LP.first().y() + 1, this->LP.last().x() + 1, this->LP.last().y() - 5);//

            }
        }

    }else if((LP.first().x() - LP.last().x() >= sh) && (LP.first().y() - LP.last().y() <= -sh))
    {   // 1 четверть.

        foreach(auto DT, this->DT)
        {

            if((DT->pos().x() == LP.first().x()) && (DT->pos().y() == LP.first().y()) && (DT->R_N))
            {
                qDebug() << "1.1 четверть";

                painter->drawLine(this->LP.first().x() + 1,this->LP.first().y() + 7, this->LP.first().x() + 1 , this->LP.last().y() + 1);
                painter->drawLine(this->LP.last().x() + 6, this->LP.last().y() + 1, this->LP.first().x() + 1, this->LP.last().y() + 1);


            }else if((DT->pos().x() == LP.first().x()) && (DT->pos().y() == LP.first().y()) && (DT->L_V))
            {qDebug() << "1.2 четверть";

                //painter->drawLine(this->LP.first().x() + 1,this->LP.first().y() + 7, this->LP.first().x() + 1 , this->LP.last().y() + 1);
                //painter->drawLine(this->LP.last().x() + 6, this->LP.last().y() + 1, this->LP.first().x() + 1, this->LP.last().y() + 1);

                painter->drawLine(this->LP.last().x() + 1,this->LP.last().y() - 5, this->LP.last().x() + 1 , this->LP.first().y() + 1);//++
                painter->drawLine(this->LP.first().x() - 5, this->LP.first().y() + 1, this->LP.last().x() + 1, this->LP.first().y() + 1);//++

            }

            if((DT->pos().x() == LP.last().x()) && (DT->pos().y() == LP.last().y()) && (DT->R_N))
            { qDebug() << "1.3 четверть";

                painter->drawLine(this->LP.first().x() + 1,this->LP.first().y() + 7, this->LP.first().x() + 1 , this->LP.last().y() + 1);//+
                painter->drawLine(this->LP.last().x() + 6, this->LP.last().y() + 1, this->LP.first().x() + 1, this->LP.last().y() + 1);//+


            }else if((DT->pos().x() == LP.last().x()) && (DT->pos().y() == LP.last().y()) && (DT->L_V))
            {qDebug() << "1.4 четверть";

                painter->drawLine(this->LP.first().x() - 5 ,this->LP.first().y() + 1, this->LP.last().x() + 1 , this->LP.first().y() + 1);//+
                painter->drawLine(this->LP.last().x() + 1, this->LP.first().y() + 0, this->LP.last().x() + 1, this->LP.last().y() - 4);

            }
        }

    }else if((LP.first().x() - LP.last().x() <= -sh) && (LP.first().y() - LP.last().y() >= -sh))
    {   // 3 четверть.

        foreach(auto DT, this->DT)
        {

            if((DT->pos().x() == LP.first().x()) && (DT->pos().y() == LP.first().y()) && (DT->R_N))
            { qDebug() << "3.1 четверть";
                painter->drawLine(this->LP.first().x() + 6,this->LP.first().y() + 1, this->LP.last().x() + 1 , this->LP.first().y() + 1);
                painter->drawLine(this->LP.last().x() + 1, this->LP.first().y() + 0, this->LP.last().x() + 1, this->LP.last().y() + 7);


            }else if((DT->pos().x() == LP.first().x()) && (DT->pos().y() == LP.first().y()) && (DT->L_V))
            {qDebug() << "3.2 четверть";

                painter->drawLine(this->LP.first().x() + 6,this->LP.first().y() + 1, this->LP.last().x() + 1 , this->LP.first().y() + 1);
                painter->drawLine(this->LP.last().x() + 1, this->LP.first().y() + 0, this->LP.last().x() + 1, this->LP.last().y() + 7);

            }

            if((DT->pos().x() == LP.last().x()) && (DT->pos().y() == LP.last().y()) && (DT->R_N))
            { qDebug() << "3.3 четверть";
                painter->drawLine(this->LP.first().x() + 6,this->LP.first().y() + 1, this->LP.last().x() + 1 , this->LP.first().y() + 1);
                painter->drawLine(this->LP.last().x() + 1, this->LP.first().y() + 0, this->LP.last().x() + 1, this->LP.last().y() + 7);


            }else if((DT->pos().x() == LP.last().x()) && (DT->pos().y() == LP.last().y()) && (DT->L_V))
            {qDebug() << "3.4 четверть";

                painter->drawLine(this->LP.first().x() + 0,this->LP.first().y() - 5, this->LP.first().x() + 0 , this->LP.last().y() + 1);//
                painter->drawLine(this->LP.first().x() + 0, this->LP.last().y() + 1, this->LP.last().x() - 5, this->LP.last().y() + 1);//+

            }
        }



    }
    else{


        qDebug() << "LP.first().x(): " << LP.first().x();
        qDebug() << "LP.last().x(): " << LP.last().x();

        qDebug() << "LP.first().y(): " << LP.first().y();
        qDebug() << "LP.last().y(): " << LP.last().y();
    }


    ///////////////////////////////////////////////////

    foreach(Detector* DTR,this->fcs->DETECTORS){

        if(DTR == DT.first()){
           DTR->setSelected(false);
           DTR->update();

        }

        if(DTR == DT.last()){
           DTR->setSelected(false);
           DTR->update();

        }
    }

    ////////////////////////////////////////////////////

    if(this->animat)
    {
        QPen pen(Qt::black, 1 ,Qt::SolidLine);

        painter->setPen(pen);
        painter->setBrush(QColor(255,142,0,255)); // Смена Цвета.

        if(i == 0)
        {
            timer.start();
            i = 1;
        }

        if(timer.hasExpired(buff)){

            if(DT.first()->SIGN){

                if(!DT.last()->SIGN){

                    if(DT.first()->scenePos().y() < DT.last()->scenePos().y()){

                        qDebug() << "Проверка № А1";

                        painter->drawRect(this->DT.first()->scenePos().x() - 3, this->DT.first()->scenePos().y() + i * shag, 15, 8);

                    }else if(DT.last()->scenePos().y() < DT.first()->scenePos().y()){
                        qDebug() << "Проверка № А2";//+

                        painter->drawRect(this->DT.first()->scenePos().x() - 3, this->DT.first()->scenePos().y() - i * shag, 15, 8);

                    }

                    //painter->drawRect(this->DT.first()->scenePos().x() + i * shag, this->DT.first()->scenePos().y() - 3, 15, 8);
                }
            }else if(DT.last()->SIGN){

                if(!DT.first()->SIGN){

                    if(DT.last()->scenePos().y() < DT.first()->scenePos().y()){
                        qDebug() << "Проверка № А3";// +

                         painter->drawRect(this->DT.last()->scenePos().x() - 3, this->DT.last()->scenePos().y() + i * shag, 15, 8);

                         //painter->drawRect(this->DT.last()->scenePos().x() + i * shag, this->DT.last()->scenePos().y() - 3, 15, 8);

                    }else if(DT.first()->scenePos().y() < DT.last()->scenePos().y() && ((DT.last()->scenePos().x() - DT.first()->scenePos().y()) < 3 | (DT.last()->scenePos().x() - DT.first()->scenePos().y()) > -3)){
                        qDebug() << "Проверка № А4";

                        painter->drawRect(this->DT.last()->scenePos().x() - 3, this->DT.last()->scenePos().y() - i * shag, 15, 8);

                    }


                    //painter->drawRect(this->DT.last()->scenePos().x() - 3, this->DT.last()->scenePos().y() + i * shag, 15, 8);

                }


            }

        }

        if(timer.hasExpired(2*buff)){

            timer.restart();

            if((this->DT.first()->scenePos().x() + i * shag) < (this->DT.last()->scenePos().x() - 20 /* x_l */))
            {
                ++i;
            }else if((this->DT.first()->scenePos().y() + i * shag) < (this->DT.last()->scenePos().y() - 0 /* y_l */))
                {
                    ++i;

            }else if((this->DT.first()->scenePos().y() - i * shag) > (this->DT.last()->scenePos().y() - 0 /* y_l */)){

                ++i;

            }else{
                i = 1;
            }
        }
    }

    scene()->update();
    ////////////////////////////////////////////////////


    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);

}

void Line_point::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    this->setPos(mapToScene(event->pos()));

    Q_UNUSED(event);
}

void Line_point::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void Line_point::paintEvent(QPaintEvent *painter)
{
    Q_UNUSED(painter);

    QPainter qp;
    //drawLines(&qp);
}
