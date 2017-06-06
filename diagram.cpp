#include "diagram.h"

Diagram::Diagram(QGraphicsView *view)
    :m_view(view)
{
    Q_ASSERT(view!=nullptr);
    m_scene=new QGraphicsScene();

    m_view->setScene(m_scene);
}

void Diagram::drawDiagramForTasks(Task *selectedTask, QList<Task *> taskList)
{
    auto gap=m_view->height()/(taskList.size()+1);                        // Get the gap between two tasks
    auto step=gap-m_view->height()/2;                                    // Where the first line will begin (y-axis
    m_scene->clear();                                                   // clear the scene


    for(int j=-m_view->width()/2; j<m_view->width()/2; j+=m_view->width()/24){
        m_scene->addRect(j,-m_view->height()/2,m_view->width()/24,m_view->height());

    }


    for(auto it=taskList.begin(); it!=taskList.end();it++){
        Task* taskElement=*it;

        QPen linePen(QColor(taskElement->type()->backgroundColor()));    // same color as the task
        linePen.setWidth(10);                                            // default pen width
        if(selectedTask==taskElement){
            linePen.setWidth(20);
        }

        qreal start=startX(taskElement->startTime().msecsSinceStartOfDay());
        qreal end=endX(int(QDateTime(taskElement->startDate(),taskElement->startTime())
                       .msecsTo(QDateTime(taskElement->endDate(),taskElement->endTime()))))+start;


        m_scene->addLine(start,step,end,step,linePen);
        step+=gap;
    }
}

qreal Diagram::startX(int msec)
{
    int minutes=msec/60000;                             // 60*1000
    int ladder=minutes*m_view->width()/1440;            // 1440= 24*60minutes
    return ladder-m_view->width()/2;                    // since the center of graphicsView is (x=0, y=0)
}

qreal Diagram::endX(int msec)
{
    int minutes=msec/60000;
    int ladder=minutes*m_view->width()/1440;
    return ladder;
}
