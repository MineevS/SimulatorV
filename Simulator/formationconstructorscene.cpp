#include "formationconstructorscene.h"

#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>

#include "line_point.h"

#include <QApplication>

#include <QDebug>

//#include <QEventLoop>
//#include <QCoreApplication>

FormationConstructorScene::FormationConstructorScene(QObject *parent) : QGraphicsScene(parent)
{
    //setForegroundBrush(QBrush(Qt::lightGray, Qt::CrossPattern)); // Добавление сетки на QGraphicsScene, но она не фиксированна.
}

enum FLAGS_ITEMM{
    null_t = 0,
    Ground = 1,
    electric_Lemp = 2,
    Detector = 3,
    Selector = 4,
    Battery = 5
};

union OBJ
{
    class Ground* OBJ;
    class Electric_Lamp* OBJ_L;
    class Detector* OBJ_D;
    class Selector* OBJ_S;
    class Battery* OBJ_BTR;
};

struct ELEM{

    FLAGS_ITEMM type_item = FLAGS_ITEMM::null_t;
    OBJ ELM;
};

auto FUN(const QGraphicsItem* itemm, FormationConstructorScene* THIS) // Функция для определения объекта.
{
    auto it = std::find(THIS->Grounditems.begin(), THIS->Grounditems.end(), itemm);

    ELEM OBJECT;

    if(it != THIS->Grounditems.end())
    {
        foreach(auto GR, THIS->Grounditems)
        {
            if(GR->pos() == itemm->pos()){

                 OBJECT.type_item = FLAGS_ITEMM::Ground;
                 OBJECT.ELM.OBJ = GR;
            }
        }

    }else{

        auto it = std::find(THIS->Lempsitems.begin(), THIS->Lempsitems.end(), itemm);

        if(it != THIS->Lempsitems.end())
        {
            //qDebug() << &it;

            foreach(Electric_Lamp* LM, THIS->Lempsitems)
            {
                if(LM->pos() == itemm->pos()){

                     OBJECT.type_item = FLAGS_ITEMM::electric_Lemp;
                     OBJECT.ELM.OBJ_L = LM;
                }
            }

        }else{

            auto it = std::find(THIS->DETECTORS.begin(), THIS->DETECTORS.end(), itemm);

            if(it != THIS->DETECTORS.end())
            {
                //qDebug() << &it;

                foreach(class Detector* DT, THIS->DETECTORS)
                {
                    foreach(auto v, THIS->Grounditems){

                        foreach(auto f, v->QDC)
                        {
                            if(f == DT)
                            {
                                //qDebug() << "Проверка № 45";

                                //qDebug() << DT->pos();

                                if(DT->pos() == itemm->pos()){

                                     OBJECT.type_item = FLAGS_ITEMM::Detector;
                                     OBJECT.ELM.OBJ_D = DT;
                                }
                            }
                        }
                    }

                    foreach(auto v, THIS->Lempsitems){

                        foreach(auto f, v->QDL)
                        {
                            if(f == DT)
                            {
                                //qDebug() << "Проверка № 50";

                                //qDebug() << DT->pos();

                                if(DT->pos() == itemm->pos()){

                                     OBJECT.type_item = FLAGS_ITEMM::Detector;
                                     OBJECT.ELM.OBJ_D = DT;
                                }
                            }
                        }
                    }


                    foreach(auto v, THIS->SelectorItems){

                        foreach(auto f, v->QDS)
                        {
                            if(f == DT)
                            {
                                //qDebug() << "Проверка № 50";

                                //qDebug() << DT->pos();

                                if(DT->pos() == itemm->pos()){

                                     OBJECT.type_item = FLAGS_ITEMM::Detector;
                                     OBJECT.ELM.OBJ_D = DT;
                                }
                            }
                        }
                    }


                    foreach(auto v, THIS->BatteryItems){

                        foreach(auto f, v->QDB)
                        {
                            if(f == DT)
                            {
                                //qDebug() << "Проверка № 50";

                                //qDebug() << DT->pos();

                                if(DT->pos() == itemm->pos()){

                                     OBJECT.type_item = FLAGS_ITEMM::Detector;
                                     OBJECT.ELM.OBJ_D = DT;
                                }
                            }
                        }
                    }
                }

                // Здесь обязательно указате реализауию для включения функции отрисовки лигннии для определяемого(нового) типа.

                // TODO

            }else{

                auto it = std::find(THIS->SelectorItems.begin(), THIS->SelectorItems.end(), itemm);

                if(it != THIS->SelectorItems.end()){

                    foreach(class Selector* SL, THIS->SelectorItems){
                        if(SL->pos() == itemm->pos()){
                            OBJECT.type_item = FLAGS_ITEMM::Selector;
                            OBJECT.ELM.OBJ_S = SL;
                        }
                    }

                }else{

                    auto it = std::find(THIS->BatteryItems.begin(), THIS->BatteryItems.end(), itemm);

                    if(it != THIS->BatteryItems.end()){

                        foreach(class Battery* BTR, THIS->BatteryItems){
                            if(BTR->pos() == itemm->pos()){
                                OBJECT.type_item = FLAGS_ITEMM::Battery;
                                OBJECT.ELM.OBJ_BTR = BTR;
                            }
                        }

                }else{

                        // Здесь обязательно указате реализауию для включения функции отрисовки лигннии для определяемого(нового) типа.

                        // TODO
                    }
                }
            }
        }
    }

    return OBJECT;
}

void FormationConstructorScene::keyPressEvent(QKeyEvent *event)
{
    /*Метод нажатия на компонент сцены:
     * - Позволяет создать item и заркасить его.
     * */

    if(event->key() == Qt::Key_Delete)
    {
        if(Cursor.iten){

            foreach(class Ground* GR, Grounditems){

                if(Cursor.iten == GR){

                    Cursor.iten = nullptr;

                    delete GR;
                }
            }
        }

        if(Cursor.itew){

            foreach(Electric_Lamp* EL, Lempsitems){

                if(Cursor.itew == EL){

                    Cursor.itew = nullptr;

                    delete EL;
                }
            }
        }

        if(Cursor.itesl){

            foreach(class Selector* SL, SelectorItems){

                if(Cursor.itesl == SL){

                    Cursor.itesl = nullptr;

                    delete SL;
                }
            }
        }

        if(Cursor.itebtr){

            foreach(class Battery* BTR, BatteryItems){

                if(Cursor.itebtr == BTR){

                    Cursor.itebtr = nullptr;

                    delete BTR;
                }
            }
        }

        // При определении нового элемента схемы сюда нужна указать реализацию для включения функции: Удаления элемента с помощью кнопки на клавиатуре: DELETE.

        // TODO

    }

    if(event->key() == Qt::Key_Down)        // Стрелка вниз
    {
        if(Cursor.iten){

            foreach(class Ground* GR, Grounditems)
            {
                if(Cursor.iten == GR){

                    Cursor.iten = nullptr;
                    GR->ort = ORIENTATION::From_top_To_bottom;
                    GR->update();
                }
            }
        }

        if(Cursor.itew){

            foreach(Electric_Lamp* EL, Lempsitems){

                if(Cursor.itew == EL){

                    Cursor.itew = nullptr;

                    EL->OL = Orientation_lemp::vertically;
                    EL->update();
                }
            }
        }

        if(Cursor.itesl){

            foreach(class Selector* EL, SelectorItems){

                if(Cursor.itesl == EL){

                    Cursor.itew = nullptr;

                    EL->OS = Orientation_selector::horN;
                    EL->update();
                }
            }
        }

        if(Cursor.itebtr){

            foreach(class Battery* BTR, BatteryItems){

                if(Cursor.itebtr == BTR){

                    Cursor.itebtr = nullptr;

                    BTR->OB = Orientation_battery::BTR_horN;
                    BTR->update();
                }
            }
        }

       // При определении нового элемента схемы сюда нужна указать реализацию для включения функции: Смена ориентации по направлению  вниз(горизонтально).

      // TODO

    }
    else if(event->key() == Qt::Key_Right)  // Стрелка в лево.
    {
        if(Cursor.iten){

            foreach(class Ground* GR, Grounditems)
            {
                if(Cursor.iten == GR){

                    Cursor.iten = nullptr;
                    GR->ort = ORIENTATION::From_left_To_right;
                    GR->update();
                }
            }
        }

        if(Cursor.itew){

            foreach(Electric_Lamp* EL, Lempsitems){

                if(Cursor.itew == EL){

                    Cursor.itew = nullptr;

                    EL->OL = Orientation_lemp::horizontally;
                    EL->update();
                }
            }
        }

        if(Cursor.itesl){

            foreach(class Selector* EL, SelectorItems){

                if(Cursor.itesl == EL){

                    Cursor.itew = nullptr;

                    EL->OS = Orientation_selector::verL;
                    EL->update();
                }
            }
        }


        if(Cursor.itebtr){

            foreach(class Battery* BTR, BatteryItems){

                if(Cursor.itebtr == BTR){

                    Cursor.itebtr = nullptr;

                    BTR->OB = Orientation_battery::BTR_verL;
                    BTR->update();
                }
            }
        }

       // При определении нового элемента схемы сюда нужна указать реализацию для включения функции: Смена ориентации по направлению  вверх(вертикально) влево.

      // TODO
    }
    else if(event->key() == Qt::Key_Left)   // Стрелка в право.
    {
        if(Cursor.iten)
        {
            foreach(class Ground* GR, Grounditems)
            {
                if(Cursor.iten == GR){

                    Cursor.iten = nullptr;

                    GR->ort = ORIENTATION::From_right_To_left;
                    GR->update();
                }
            }
        }

        if(Cursor.itew){

            foreach(Electric_Lamp* EL, Lempsitems){

                if(Cursor.itew == EL){

                    Cursor.itew = nullptr;

                    EL->OL = Orientation_lemp::horizontally;
                    EL->update();
                }
            }
        }

        if(Cursor.itesl){

            foreach(class Selector* EL, SelectorItems){

                if(Cursor.itesl == EL){

                    Cursor.itew = nullptr;

                    EL->OS = Orientation_selector::verR;
                    EL->update();
                }
            }
        }

        if(Cursor.itebtr){

            foreach(class Battery* BTR, BatteryItems){

                if(Cursor.itebtr == BTR){

                    Cursor.itebtr = nullptr;

                    BTR->OB = Orientation_battery::BTR_verR;
                    BTR->update();
                }
            }
        }

       // При определении нового элемента схемы сюда нужна указать реализацию для включения функции: Смена ориентации по направлению  вверх(вертикально) вправо.

      // TODO


    }
    else if(event->key() == Qt::Key_Up)     // Стрелка вверх.
    {
        if(Cursor.iten){

            foreach(class Ground* GR, Grounditems)
            {
                if(Cursor.iten == GR){

                    Cursor.iten = nullptr;

                    GR->ort = ORIENTATION::From_bottom_To_top;
                    GR->update();
                }
            }
        }

        if(Cursor.itew){

            foreach(Electric_Lamp* EL, Lempsitems){

                if(Cursor.itew == EL){

                    Cursor.itew = nullptr;

                    EL->OL = Orientation_lemp::vertically;
                    EL->update();

                    }
                }
            }

        if(Cursor.itesl){

            foreach(class Selector* EL, SelectorItems){

                if(Cursor.itesl == EL){

                    Cursor.itew = nullptr;

                    EL->OS = Orientation_selector::horV;
                    EL->update();
                }
            }
        }


        if(Cursor.itebtr){

            foreach(class Battery* BTR, BatteryItems){

                if(Cursor.itebtr == BTR){

                    Cursor.itebtr = nullptr;

                    BTR->OB = Orientation_battery::BTR_horV;
                    BTR->update();
                }
            }
        }

       // При определении нового элемента схемы сюда нужна указать реализацию для включения функции: Смена ориентации по направлению  вверх(вертикально) вправо.

      // TODO

    }
}

void FormationConstructorScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem* itemm = itemAt(event->scenePos(), QTransform());

 if(itemm != NULL){

     foreach(class Detector* DT, DETECTORS){

         if(DT->pos() == itemm->pos()){

             if(itemm->isSelected())/////
              {//

             }else{
                DT->setSelected(true);
                DT->update();
             }

         }

     }

     foreach(class Selector* Sl, SelectorItems){

         if(event->buttons() == Qt::MouseButton::RightButton){
             if(itemm->pos() == Sl->pos()){

                 Sl->IN_OUT = !Sl->IN_OUT;
                 Sl->update();
             }
         }
     }

     QGraphicsScene::mousePressEvent(event);

   }else{

       QGraphicsScene::mousePressEvent(event);
   }
}

void FormationConstructorScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem* itemm = itemAt(event->scenePos(), QTransform());

    //qDebug() << itemm->isSelected();

    if(itemm != NULL){

        ELEM OBJ_R = FUN(itemm, this);

        switch(OBJ_R.type_item)
        {
            case(FLAGS_ITEMM::electric_Lemp):

                        Cursor.itew = OBJ_R.ELM.OBJ_L;

                        OBJ_R.ELM.OBJ_L->setPos(event->scenePos().x(), event->scenePos().y());
                        OBJ_R.ELM.OBJ->setSelected(false);
                        OBJ_R.ELM.OBJ_L->update();

                        /*
                        item_lemps = new Electric_Lamp(this, OBJ_R.ELM.OBJ_L->OL);
                        item_lemps->setPos(event->scenePos().x(), event->scenePos().y());
                        this->addItem(item_lemps);
                        Lempsitems.append(item_lemps);
                        Cursor.itew = item_lemps;
                        item_lemps->fcs = this;
                        //Lempsitems.removeOne(OBJ_R.ELM.OBJ_L);
                        delete(itemm);
                        */
                break;
            case(FLAGS_ITEMM::Ground):

                        Cursor.iten = OBJ_R.ELM.OBJ;
                        OBJ_R.ELM.OBJ->setPos(event->scenePos().x(), event->scenePos().y());
                        OBJ_R.ELM.OBJ->setSelected(false);
                        OBJ_R.ELM.OBJ->update();

                        /*
                        item = new class Ground(this, OBJ_R.ELM.OBJ);
                        item->setPos(event->scenePos().x(), event->scenePos().y());
                        this->addItem(item);
                        Grounditems.append(item);
                        item->fcs = this;
                        Cursor.iten = item;
                        //Grounditems.removeOne(OBJ_R.ELM.OBJ);
                        delete(itemm);
                        */
                break;
            case(FLAGS_ITEMM::Detector):

                        /*
                        if(itemm->isSelected())/////
                         {//Рисуем прямую:
                        }else{
                            itemm->setSelected(true);
                            itemm->update();
                        }
                        */

                        //qDebug() << "Проверка № 087";

                        if(DTS.size() == 2){
                            DTS.clear();
                        }

                        if(DTS.size() == 1){

                            //qDebug() << itemm->pos();
                            //qDebug() << DTS.first()->pos();
                            //qDebug() << LPS.first();

                             if((itemm->pos() != LPS.first()))
                             {
                                 foreach(class Detector* DT, DETECTORS)
                                 {
                                     if(itemm->pos() == DT->pos()){
                                         DTS.append(DT);
                                         LPS.append(itemm->pos());//Передаем в LPS координаты двух объектов.
                                     }
                                 }

                             }else{
                                 DTS.clear();
                                 LPS.clear();
                                 break;
                             }

                        }else{

                            foreach(class Detector* DT, DETECTORS){

                                if(itemm->pos() == DT->pos()){
                                    DTS.append(DT);
                                    LPS.append(itemm->pos());//Передаем в LPS координаты двух объектов.
                                }
                            }
                        }

                        if(DTS.size() == 2) // Как только два объекта выбраны.
                        {
                            //qDebug() << "Проверка № 100";

                            item_line = new Line_point(this, DTS);

                            item_line->fcs = this;

                            //V1:
                            // Проходимся по всем lamp(QDL) и Ground(QDC), отыскивая нужные detector-ы
                            // Говорим detectors, что они хранят указатель на Line.

                            foreach(Electric_Lamp* e, Lempsitems)
                            {
                                foreach(class Detector* t, e->QDL)
                                {
                                    foreach(QPointF p, LPS){

                                        if(t->pos() == p)
                                        {
                                            t->LPs.append(item_line);
                                            //item_line->DT.append(t);

                                            ///////////////////////////////////////////////

                                            foreach(class Detector* tl, DTS){

                                                if(tl->pos() != t->pos()){

                                                    if(tl->Level){

                                                        t->SIGN = !tl->SIGN;
                                                        t->DT.first()->SIGN =!t->SIGN;

                                                    }else{
                                                        item_line->Level = false;

                                                        //item_Lins.append(item_line);
                                                    }
                                                }
                                            }

                                            /////////////////////////////////////////////
                                        }
                                    }
                                }
                            }

                            foreach(class Ground* e, Grounditems)
                            {
                                foreach(class Detector* t, e->QDC)
                                {
                                    foreach(QPointF p, LPS){

                                        if(t->pos() == p)
                                        {
                                            t->LPs.append(item_line);
                                            //item_line->DT.append(t);

                                            ///////////////////////////////////////////////

                                            foreach(class Detector* tl, DTS){

                                                if(tl->pos() != t->pos()){

                                                    if(tl->Level){

                                                        if(t->pos().x() < tl->pos().x() | t->pos().y() < tl->pos().y()){

                                                            t->SIGN_R = !tl->SIGN;
                                                        }else if(t->pos().x() > tl->pos().x() | t->pos().y() > tl->pos().y()){

                                                            t->SIGN_L = !tl->SIGN;
                                                        }

                                                        //t->SIGN = !tl->SIGN;

                                                    }else{
                                                        item_line->Level = false;

                                                        //item_Lins.append(item_line);
                                                    }
                                                }
                                            }

                                            /////////////////////////////////////////////
                                        }
                                    }
                                }
                            }

                            foreach(class Selector* SL, SelectorItems)
                            {
                                foreach(class Detector* t, SL->QDS)
                                {
                                    foreach(QPointF p, LPS){

                                        if(t->pos() == p)
                                        {
                                            t->LPs.append(item_line);
                                            //item_line->DT.append(t);

                                            ///////////////////////////////////////////////

                                            foreach(class Detector* tl, DTS){

                                                if(tl->pos() != t->pos()){

                                                    if(tl->Level){

                                                        t->SIGN = !tl->SIGN;
                                                        t->DT.first()->SIGN =!t->SIGN;

                                                    }else{

                                                        item_line->Level = false;

                                                        //item_Lins.append(item_line);
                                                    }
                                                }
                                            }

                                            /////////////////////////////////////////////
                                        }
                                    }
                                }
                            }

                            foreach(class Battery* BTR, BatteryItems)
                            {
                                foreach(class Detector* t, BTR->QDB)
                                {
                                    foreach(QPointF p, LPS){

                                        if(t->pos() == p)
                                        {
                                            t->LPs.append(item_line);
                                            //item_line->DT.append(t);// ?

                                            // Level: true;

                                            ///////////////////////////////////////////////

                                            foreach(class Detector* tl, DTS){

                                                if(tl->pos() != t->pos()){

                                                    if(tl->Level){

                                                        t->SIGN = !tl->SIGN;

                                                    }else{

                                                        item_line->Level = false;

                                                        //item_Lins.append(item_line);
                                                    }
                                                }
                                            }

                                            /////////////////////////////////////////////


                                        }
                                    }
                                }
                            }

                            item_line->fcs = this;

                            //item_line->update();

                            addItem(item_line);

                            this->update();
                            this->Line_points.append(item_line);

                            //qDebug() << "Проверка № 101";

                            LPS.clear();
                       }

                break;
              case(FLAGS_ITEMM::Selector):

                    Cursor.itesl = OBJ_R.ELM.OBJ_S;
                    OBJ_R.ELM.OBJ_S->setPos(event->scenePos().x(), event->scenePos().y());
                    OBJ_R.ELM.OBJ->setSelected(false);
                    OBJ_R.ELM.OBJ->update();

            break;
        case(FLAGS_ITEMM::Battery):

                    Cursor.itebtr = OBJ_R.ELM.OBJ_BTR;
                    OBJ_R.ELM.OBJ_BTR->setPos(event->scenePos().x(), event->scenePos().y());
                    OBJ_R.ELM.OBJ_BTR->setSelected(false);
                    OBJ_R.ELM.OBJ_BTR->update();

            break;
            default:;
                break;

            // При определении нового элемента схемы сюда нужна указать реализацию для включения функции: Смена ориентации по направлению  вверх(вертикально) вправо.

           // TODO
     }

    }else{

        QGraphicsScene::mouseReleaseEvent(event);
    }

    //QApplication::processEvents();

    qDebug() << "1. DETECTORS.size(): " << this->DETECTORS.size();
    qDebug() << "2. Grounditems.size():  " << this->Grounditems.size();
    qDebug() << "3. Lempsitems.size(): " << this->Lempsitems.size();
    qDebug() << "4. Line_points.size(): " << this->Line_points.size();
    qDebug() << "5. SelectorItems.size(): " << this->SelectorItems.size();
    qDebug() << "6. BatteryItems.size(): " << this->BatteryItems.size();
}

void FormationConstructorScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   //qDebug() <<"Проверка № 6690";
    QGraphicsScene::mouseMoveEvent(event);
}

bool f = false;
void FormationConstructorScene::drawBackground(QPainter *pointer, const QRectF &rect)
{
    //qDebug() << "rect: " << rect;

    //qDebug() << "rect(): " << this->views().first()->rect();

    if(f == false)
    {
        Q_UNUSED(pointer);
        Q_UNUSED(rect);

        QRectF nRect = this->views().first()->rect(); // Обязательно подключить QGraphicsVeiw

        for(auto iter = _backgroundLines.begin(); iter != _backgroundLines.end(); ++iter)
        {
            removeItem((QGraphicsItem*)(*iter));
            delete *iter;
        }

        _backgroundLines.clear();

        for(int i = 0; i < 20; i++){

            if(i <= 15){

                QLineF lineV(QPointF(nRect.width() / 15 * i, 0), QPointF(nRect.width() / 15 * i, nRect.height()));
                _backgroundLines.push_back(addLine(lineV));
            }

            if(i <= 14){
                QLineF lineVl(QPointF(nRect.width() / 15 * (i + 0.5), 0), QPointF(nRect.width() / 15 * (i + 0.5), nRect.height()));
                _backgroundLines.push_back(addLine(lineVl, QPen(Qt::lightGray)));
            }


            if(i <= 10){

                QLineF lineH(QPointF(0, nRect.height() / 10 * i), QPointF(nRect.width(), nRect.height() / 10 * i));
                _backgroundLines.push_back(addLine(lineH));//V
            }

            if(i < 10){
                QLineF lineHl(QPointF(0, nRect.height() / 10 * (i + 0.5)), QPointF(nRect.width(), nRect.height() / 10 * (i + 0.5)));
                _backgroundLines.push_back(addLine(lineHl, QPen(Qt::lightGray)));
            }
        }

        f = true;
    }
}

void FormationConstructorScene::Cadr()
{
    // TODO;
    int x = 0;
    qDebug() << "Проверка № 56";

    if(SelectorItems.size() > 0){

        foreach(auto sl, SelectorItems){
            sl->IN_OUT = true;
        }

    }

    if(Line_points.size() > 0){
        foreach(Line_point* LP, Line_points){
            if(LP->Level){
                LP->animat = true;
            }else{

                //LP->DT.first()

                 //LP->DT.first()->DT;// Хранит напарника.

                if(LP->DT.first()->DT.size() == 0){

                    // Значит у нас попался элемент с одним детектором(Ground).
                    if(LP->DT.first()->LPs.size() == 2){
                        LP->DT.first()->LPs.first();

                        /*
                        foreach(auto LP, LP->DT.first()->LPs){


                        }
                        */
                        if(LP->DT.first()->LPs.first()->DT.first() != LP->DT.first()){
                            // . . .
                            if(LP->DT.first()->LPs.last()->DT.first() != LP->DT.first()){



                            }else if(LP->DT.first()->LPs.last()->DT.last() != LP->DT.first()){

                            }

                        }//else if(){}

                        LP->DT.first()->LPs.first()->DT.first();
                        LP->DT.first()->LPs.first()->DT.last();

                        LP->DT.first()->LPs.last();

                    }

                }else if(LP->DT.first()->DT.size() == 1){

                    if(LP->DT.first()->SIGN != LP->DT.first()->DT.first()->SIGN){

                        LP->DT.last()->SIGN = !LP->DT.first()->SIGN;
                        LP->Level = true;
                        LP->animat = true;

                    }else{

                        ++x;

                    }

                }

            }
        }
    }
}

void FormationConstructorScene::Stop()
{
    qDebug() << "Проверка № 56";

    if(Line_points.size() > 0){
        foreach(Line_point* LP, Line_points){
            LP->animat = false;
        }
    }

}
