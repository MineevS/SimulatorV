#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "formationconstructorscene.h"
#include "formationconstructorview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);  // Конструктор по умолчанию.
    ~MainWindow();                          // Диструктор.

private:
    Ui::MainWindow *ui;                     // Указатель на экземпляр: Ui::MainWindow.

protected:
    void wheelEvent(QWheelEvent *event);    //обработка событий прокрутки колесика.

private slots:
    void on_pushButton_clicked();           // Процедура создания графического элемента: Ground(Земля).
    void on_pushButton_2_clicked();         // Процедура создания графического элемента: Electric_Lamp(Электрическая лампа).
    void on_pushButton_3_clicked();         // Процедура создания графического элемента: Selector(Переключатель).
    void on_pushButton_4_clicked();         // Вызов мутода Card() для запуска симуляии.
    void on_pushButton_5_clicked();         // Вызов мутода Card() для остановки симуляии.
    void on_pushButton_6_clicked();         // Процедура создания графического элемента: Battery(Переключатель).
};
#endif // MAINWINDOW_H
