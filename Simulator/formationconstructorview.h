#ifndef FORMATIONCONSTRUCTORVIEW_H
#define FORMATIONCONSTRUCTORVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QResizeEvent>

#include "formationconstructorscene.h"
#include "detector.h"

class FormationConstructorView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit FormationConstructorView(QWidget *parent = nullptr);

public:
    FormationConstructorScene* scene;
    QList<Detector*> DETECTORS;

signals:

public slots:

protected:
    void resizeEvent(QResizeEvent *event);

};

#endif // FORMATIONCONSTRUCTORVIEW_H
