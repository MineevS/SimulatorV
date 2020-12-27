
#include "mainwindow.h"
#include "ui_mainwindow.h"

// Доп:
//#include <iostream>
#include <QRandomGenerator>

// Классы, обьекты которых, могут создаваться от MainWindow:
//#include "Ground.h"
//#include "electric_lamp.h"
//#include "selector.h"

// Реестр ориентации для выше включенных обьектов.
#include "Orientation.h"

// Отладчик.
#include <QDebug>


//+
static int randomBetween(int low, int high)                                                                 // Функция для получения рандомного числа в диапазоне от минимального(low) до максимального(high).
{
    /* Функция для получения рандомного числа
     * в диапазоне от минимального(low) до максимального(high)
     * */

   std::uniform_int_distribution<int> dist(low, high);                                                      // Переменная преобразователь и хранения рандомного числа.

   return dist(*QRandomGenerator::global());                                                                // Вывод рандомного числа.
}

//+
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);                                                                                      // Настройка пользовательского интерфейса для указанного виджета.
    ui->formationConstructoView->scene = new FormationConstructorScene();                                   // Добавление FormationConstructorScene на formationConstructoView.
    ui->formationConstructoView->setScene(ui->formationConstructoView->scene);                              // Добавляем сцену на нашу форму.
    ui->formationConstructoView->setRenderHint(QPainter::Antialiasing);                                     // Настраиваем рендер.
    ui->formationConstructoView->setCacheMode(QGraphicsView::CacheBackground);                              // Кэш фона.
    ui->formationConstructoView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);          //граничивающий прямоугольник всех изменений в видовом окне будет перерисован заново. Этот режим имеет то преимущество, что QGraphicsView ищет изменения только в одной области, сводя к минимуму время, затрачиваемое на определение того, что нуждается в перерисовке. Недостатком является то, что области, которые не изменились, также должны быть перерисованы.
}

//+
MainWindow::~MainWindow()                                                                                   // Деструктор.
{
    delete ui;                                                                                              // Удаление Ui::MainWindow.
}

//+
void MainWindow::wheelEvent(QWheelEvent *event)                                                             // Обработка событий прокрутки колесика.
{
    ui->formationConstructoView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);                  // AnchorUnderMouse // AnchorViewCenter// Находится ли указатель мыши в области окна?

    double scale = 0.90;                                                                                    // Масштаб.

    event->angleDelta().y() > 0 ? ui->formationConstructoView->scale(scale, scale) :                        // delta() - позволяет узнать направление поворота колеса.
                                  ui->formationConstructoView->scale(1/scale, 1/scale);
}

//+
void MainWindow::on_pushButton_clicked()                                                                    // Процедура создания графического элемента: Ground(Земля).
{
    // Код создания графического элемента: Ground(Земля).

    Ground *item = new Ground(ui->formationConstructoView, ORIENTATION::From_top_To_bottom);                // Создаём графический элемент.
    item->setPos(randomBetween(30, 300),randomBetween(30, 300));                                            // Устанавливаем случайную позицию элемента.

    item->fcs = ui->formationConstructoView->scene;                                                         // Передача указателя в item, для возможности инменения внешних данных из вне.
    ui->formationConstructoView->scene->addItem(item);                                                      // Добавляем элемент на графическую сцену.
    ui->formationConstructoView->scene->Grounditems.append(item);                                           // Добавление item в реестр Grounditems, для возможности дальнейшего отслеживания и изменения свойств данного item.
}

//+
void MainWindow::on_pushButton_2_clicked()                                                                  // Процедура создания графического элемента: Electric_Lamp(Электрическая лампа).
{
    // Код создания графического элемента: Electric_Lamp(Электрическая лампа).

    Electric_Lamp *item = new Electric_Lamp(ui->formationConstructoView, Orientation_lemp::horizontally);   // Создаём графический элемент.
    item->setPos(randomBetween(30, 300), randomBetween(30, 300));                                           // Устанавливаем случайную позицию элемента.

    item->fcs = ui->formationConstructoView->scene;                                                         // Передача указателя в item, для возможности инменения внешних данных из вне.
    ui->formationConstructoView->scene->addItem(item);                                                      // Добавляем элемент на графическую сцену.
    ui->formationConstructoView->scene->Lempsitems.append(item);                                            // Добавление item в реестр Grounditems, для возможности дальнейшего отслеживания и изменения свойств данного item.
}

void MainWindow::on_pushButton_3_clicked()
{
    // Код создания графического элемента: Electric_Lamp(Электрическая лампа).

    Selector *item = new Selector(ui->formationConstructoView, Orientation_selector::horV);                 // Создаём графический элемент.
    item->setPos(randomBetween(30, 300), randomBetween(30, 300));                                           // Устанавливаем случайную позицию элемента.

    item->fcs = ui->formationConstructoView->scene;                                                         // Передача указателя в item, для возможности инменения внешних данных из вне.
    ui->formationConstructoView->scene->addItem(item);                                                      // Добавляем элемент на графическую сцену.
    ui->formationConstructoView->scene->SelectorItems.append(item);                                         // Добавление item в реестр Grounditems, для возможности дальнейшего отслеживания и изменения свойств данного item.

}

void MainWindow::on_pushButton_4_clicked()
{// Пуск:

    ui->formationConstructoView->scene->FormationConstructorScene::Cadr();                                  // ...
}

void MainWindow::on_pushButton_5_clicked()
{// Стоп:

    ui->formationConstructoView->scene->FormationConstructorScene::Stop();                                  // ...
}

void MainWindow::on_pushButton_6_clicked()
{
    // Код создания графического элемента: Electric_Lamp(Электрическая лампа).

    Battery *item = new Battery(ui->formationConstructoView, Orientation_battery::BTR_horV);                 // Создаём графический элемент.
    item->setPos(randomBetween(30, 300), randomBetween(30, 300));                                            // Устанавливаем случайную позицию элемента.

    item->fcs = ui->formationConstructoView->scene;                                                          // Передача указателя в item, для возможности инменения внешних данных из вне.
    ui->formationConstructoView->scene->addItem(item);                                                       // Добавляем элемент на графическую сцену.
    ui->formationConstructoView->scene->BatteryItems.append(item);                                           // Добавление item в реестр BatteryItems, для возможности дальнейшего отслеживания и изменения свойств данного item.

}
