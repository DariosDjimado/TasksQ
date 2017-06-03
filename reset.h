#ifndef RESET_H
#define RESET_H

#include <QObject>

class Reset : public QObject
{
    Q_OBJECT
public:
    explicit Reset(QObject *parent = nullptr);
    static bool doReset();

signals:

public slots:
private:
    static bool resetTypes();
    static bool resetTasks();
};

#endif // RESET_H
