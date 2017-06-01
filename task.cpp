#include "task.h"

Task::Task(QObject *parent) : QObject(parent)
{

}

Task::~Task()
{

}

QString Task::name() const
{
    return m_name;
}

void Task::setName(const QString &name)
{
    if(m_name!=name){
        m_name = name;
        emit nameChanged();
    }
}

QDate Task::startDate() const
{
    return m_startDate;
}

void Task::setStartDate(const QDate &startDate)
{
    if(m_startDate!=startDate){
        m_startDate = startDate;
        emit startDateChanged();
    }
}

QDate Task::endDate() const
{
    return m_endDate;
}

void Task::setEndDate(const QDate &endDate)
{
    if(m_endDate!=endDate){
        m_endDate = endDate;
        emit endDateChanged();
    }
}

QTime Task::startTime() const
{
    return m_startTime;
}

void Task::setStartTime(const QTime &startTime)
{
    if(m_startTime!=startTime){
        m_startTime = startTime;
        emit startTimeChanged();
    }
}

QTime Task::endTime() const
{
    return m_endTime;
}

void Task::setEndTime(const QTime &endTime)
{
    if(m_endTime!=endTime){
        m_endTime = endTime;
        emit endDateChanged();
    }
}

int Task::type() const
{
    return m_type;
}

void Task::setType(int type)
{
    m_type = type;
}

QString Task::comment() const
{
    return m_comment;
}

void Task::setComment(const QString &comment)
{
    m_comment = comment;
}

bool Task::saved() const
{
    return m_saved;
}

void Task::setSaved(bool saved)
{
    m_saved = saved;
}
