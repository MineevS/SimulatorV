#include "formationconstructorview.h"
#include "Ground.h"
#include "detector.h"
#include "Orientation.h"

#include <QApplication> // QApplication::mouseButtons()[Строка:136]

// Отладка:
#include <QDebug>

/*
//+
Ground::Ground(QObject *parent, Ground* GR) :
    QObject(parent), QGraphicsItem()
{
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);

    this->D_GR = GR;
    this->ort = GR->QDC.first()->ort;
}
*/

//+
Ground::Ground(QObject *parent, ORIENTATION ort)
{
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);

    this->ort = ort; // Передача ориентации.

    Q_UNUSED(parent);
}

//+
Ground::~Ground()
{
    this->fcs->DETECTORS.removeOne(QDC.first());
    this->fcs->removeItem(QDC.first());
    this->fcs->Grounditems.removeOne(this);
    this->fcs->removeItem(this);

    delete QDC.first();
}

//+
QRectF Ground::boundingRect() const
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

    return QRectF (-30,-30,60,60);// Определяет границы для последующих отрисовок данного элемента.
}

//+
void Ground::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int x = 0, y = 0; // Переменные для хранения приращений для координат detector.

    QPen pen(Qt::black, 3 ,Qt::SolidLine);

    painter->setPen(pen);
    painter->setBrush( !(option->state & QStyle::State_Selected) ? Qt::red : Qt::green); // Смена Цвета.

    if(this->ort == ORIENTATION::From_top_To_bottom){

        painter->drawEllipse(-4,-25, 9, 9);
        painter->drawLine(0, -15 , 0, -2);
        painter->drawLine(-10, 0, 10, 0);
        painter->drawLine(-5, 5, 5, 5);
        painter->drawLine(-2, 10, 2, 10);
        x = 0;
        y = -22;

    }else if(this->ort == ORIENTATION::From_left_To_right){

        painter->drawEllipse(-25,-4, 9, 9);
        painter->drawLine(-15, 0 , -2, 0);
        painter->drawLine(0, -10, 0, 10);
        painter->drawLine(5, -5, 5, 5);
        painter->drawLine(10, -2, 10, 2);
        x = -21;
        y = -1;

    }else if(this->ort == ORIENTATION::From_right_To_left){

        painter->drawEllipse(20, -5, 9, 9);
        painter->drawLine(1, 0 , 20, 0);
        painter->drawLine(0, -10, 0, 10);
        painter->drawLine(-5, -5, -5, 5);
        painter->drawLine(-10, -2, -10, 2);
        x = 24;
        y = -2;

    }else if(this->ort == ORIENTATION::From_bottom_To_top){

        painter->drawEllipse(-4, 19, 9, 9);
        painter->drawLine(0, 2 , 0, 18);
        painter->drawLine(-10, 0, 10, 0);
        painter->drawLine(-5, -5, 5, -5);
        painter->drawLine(-2, -10, 2, -10);
        x = 0;
        y = 22;
    }

    if(QDC.empty()){

        Detector* Detect = new Detector(this,this->ort);

        Detect->setPos(this->pos().x() + x, this->pos().y() + y);

        this->scene()->addItem(Detect);

        Detect->fcs = this->fcs;
        Detect->UT.GD = this;

        this->QDC.append(Detect);
        this->fcs->DETECTORS.append(Detect);
    }
    else if(!QDC.empty())
    {
        QDC.first()->setPos(this->pos().x() + x, this->pos().y() + y);

        QDC.first()->update();

    }else if(!QDC.empty() && this->isUnderMouse() && (option->state & QStyle::State_Selected && !(QApplication::mouseButtons() & Qt::LeftButton))){

        this->fcs->DETECTORS.removeOne(QDC.first());

        QDC.first()->deleteLater();

        QDC.removeFirst();

    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//+
void Ground::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */

    this->setPos(mapToScene(event->pos()));
}
