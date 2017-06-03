#ifndef TASK_H
#define TASK_H
#include "tasktype.h"
#include <QObject>
#include <QString>
#include <QDate>
#include <QTime>
class Task : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    Q_PROPERTY(QDate startDate READ startDate WRITE setStartDate NOTIFY startDateChanged)
    Q_PROPERTY(QDate endDate READ endDate WRITE setEndDate NOTIFY endDateChanged)

    Q_PROPERTY(QTime startTime READ startTime WRITE setStartTime NOTIFY startTimeChanged)
    Q_PROPERTY(QTime endTime READ endTime WRITE setEndTime NOTIFY endTimeChanged)

public:
    explicit Task(QObject *parent = 0);
    ~Task();

    QString name() const;
    void setName(const QString &name);

    QDate startDate() const;
    void setStartDate(const QDate &startDate);

    QDate endDate() const;
    void setEndDate(const QDate &endDate);

    QTime startTime() const;
    void setStartTime(const QTime &startTime);

    QTime endTime() const;
    void setEndTime(const QTime &endTime);

    QString comment() const;
    void setComment(const QString &comment);

    bool saved() const;
    void setSaved(bool saved);

    TaskType *type() const;
    void setType(TaskType *type);

    enum {
        NAME, START_DATE,START_TIME, END_DATE, END_TIME, TYPE, COMMENT
    };

signals:
    void nameChanged();
    void startDateChanged();
    void endDateChanged();
    void startTimeChanged();
    void endTimeChanged();

public slots:


private:
    QString m_name;

    QDate m_startDate;
    QDate m_endDate;

    QTime m_startTime;
    QTime m_endTime;

    TaskType *m_type;

    QString m_comment;
    // used to flag saved task
    bool m_saved;


};

#endif // TASK_H
