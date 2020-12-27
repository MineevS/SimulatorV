#include "mainwindow.h"             // ..

#include <QApplication>             // Внешнее окружение для работы данной программы.

int main(int argc, char *argv[])    // ..
{
    QApplication a(argc, argv);     // Создание Обьекта внешнего окружения и передача, переменных, для общения программы и внешней среды.

        MainWindow w;               // Создание экземпляра класса: MainWindow.
        w.show();                   // Запуск экземпляра класса: MainWindow.

    return a.exec();                // Запускаем цикл обработки событий, вызывая QApplication::exec().
}
