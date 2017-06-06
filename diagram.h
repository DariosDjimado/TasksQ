#ifndef DIAGRAM_H
#define DIAGRAM_H
#include "task.h"
#include <QGraphicsView>

class Diagram
{
public:
    Diagram(QGraphicsView *view);
    void drawDiagramForTasks(Task *selectedTask, QList<Task *> taskList);

private:
    QGraphicsView * m_view;
    QGraphicsScene * m_scene;
    qreal startX(int msec);
    qreal endX(int msec);
};

#endif // DIAGRAM_H
