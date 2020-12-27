#ifndef FORMATIONCONSTRUCTORSCENE_H
#define FORMATIONCONSTRUCTORSCENE_H


#include <QObject>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>

#include <QPainter>
#include <QList>

#include "detector.h"
#include "Ground.h"
#include "electric_lamp.h"
#include "selector.h"
#include "battery.h"

#include "line_point.h"

// Классы, которые требуется использовать в данном классе,как переменные:

// Неявные элементы эдлектронной схемы(Элементы с которыми пользователь НЕ работает непосредственно и НЕ видит их.):
class Detector;

// Явные элементы электронной схемы(Элементы с которыми пользователь работает непосредственно и видит их.):

    // Элементы электронной схемы:
    class Ground;
    class Electric_Lamp;
    class Selector;
    class Battery;

    // Дополнительные элементы схемы:
    class Line_point;

//
class FormationConstructorScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit FormationConstructorScene(QObject *parent = nullptr); // Конструктор по умолчанию.

signals:

public slots:

public:
    QList<Battery*> BatteryItems;                               // Храним все item-ы типа: Battery.
    Battery* Battery_cursor=nullptr;                            // Храним указатель на выбраный itemm типа: Battery.

    QList<Selector*> SelectorItems;                             // Храним все item-ы типа: Selector.
    Selector* Selector_cursor=nullptr;                          // Храним указатель на выбраный itemm типа: Selector.

    QList<Ground*> Grounditems;                                 // Храним все item-ы типа: Ground.
    Ground* Ground_cursor=nullptr;                              // Храним указатель на выбраный itemm типа: Ground.

    QList<Electric_Lamp*> Lempsitems;                           // Храним все item-ы типа: Electric_Lamp.
    Electric_Lamp* Lemps_cursor=nullptr;                        // Храним указатель на выбраный itemm типа: Electric_Lamp.

    QList<Line_point*> Line_points;                             // Храним все item-ы типа: Line_points.
    Line_point* Lips_cursor=nullptr;                            // Храним указатель на выбраный itemm типа: Line_points.

    QList<QPointF> LPS;                                         // Храним координаты для будущей линии.
    QList<Detector*> DTS;                                       // Храним Детекторы для будущей линии.

    QList<Detector*> DETECTORS = QList<Detector*>();            // Реестр Детекторов(Датчиков).

    union ster{                                                 // Единая по памяти структура для хранения одного из указателей для Cursor.
        Ground* iten;                                           // Указатель, хранимый переменной Cursor, для Ground.
        Electric_Lamp* itew;                                    // Указатель, хранимый переменной Cursor, для Electric_Lamp.
        Line_point* itel;                                       // Указатель, хранимый переменной Cursor, для Line_point.
        Selector* itesl;                                        // Указатель, хранимый переменной Cursor, для Selector.
        Battery* itebtr;                                        // Указатель, хранимый переменной Cursor, для Selector.
    };

    ster Cursor;                                                // Курсор, для удержания тукущего выбранного элемента.

private:
    //Ground* item;                                             // Храним указатель на item типа: Ground.
    //Electric_Lamp* item_lemps;                                // Храним указатель на item типа: Electric_Lamp.
    Line_point* item_line;                                      // Храним указатель на item типа: Line_point.
    //QList<Line_point*> item_Lins;                               //

protected:
    virtual void keyPressEvent(QKeyEvent *event);               // Процедура улавнивания нажатия клавиш клавиатуры.
    void mousePressEvent(QGraphicsSceneMouseEvent *event);      // Процедура улавливания нажатия кнопки мыши.
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);    // Процедура улавливания отпускания кнопки мыши.
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);       // Процедура отслеживания Координат курсора мыши.
    void drawBackground(QPainter* pointer,const QRectF &rect);  // Процедура отрисовки сцены.

public:
    void Cadr();                                                // Процедура запуска анимации.
    void Stop();                                                // Процедура остановки анимации.

private:
    QList<QGraphicsItem*>_backgroundLines;                      // Массив линий для отрисовки сетки.

};

#endif // FORMATIONCONSTRUCTORSCENE_H
