#include "formationconstructorview.h"
#include "resizeablefilter.h"

FormationConstructorView::FormationConstructorView(QWidget *parent) : QGraphicsView(parent)
{
    setMouseTracking(true); // Следим за всеми нажатиями мышки.
}

void FormationConstructorView::resizeEvent(QResizeEvent *event)
{
    QRect rect = this->rect();

    rect.setHeight(rect.height() - 5);
    rect.setWidth(rect.width() - 5);

    scene->setSceneRect(rect);

    Q_UNUSED(event);
}

