#ifndef TASKTYPE_H
#define TASKTYPE_H

#include <QObject>

class TaskType : public QObject
{
    Q_OBJECT
public:
    explicit TaskType(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QString backgroundColor() const;
    void setBackgroundColor(const QString &backgroundColor);

    QString textColor() const;
    void setTextColor(const QString &textColor);

signals:

public slots:

private:
    QString m_name;
    QString m_backgroundColor;
    QString m_textColor;
};

#endif // TASKTYPE_H
