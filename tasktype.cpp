#include "tasktype.h"

TaskType::TaskType(QObject *parent) : QObject(parent)
{

}

QString TaskType::name() const
{
    return m_name;
}

void TaskType::setName(const QString &name)
{
    m_name = name;
}

QString TaskType::backgroundColor() const
{
    return m_backgroundColor;
}

void TaskType::setBackgroundColor(const QString &backgroundColor)
{
    m_backgroundColor = backgroundColor;
}

QString TaskType::textColor() const
{
    return m_textColor;
}

void TaskType::setTextColor(const QString &textColor)
{
    m_textColor = textColor;
}
