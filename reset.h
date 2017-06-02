#ifndef RESET_H
#define RESET_H

#include <QObject>

class Reset : public QObject
{
    Q_OBJECT
public:
    explicit Reset(QObject *parent = nullptr);
    void doReset();

signals:

public slots:
private:
    void resetTypes();
    void resetTasks();
};

#endif // RESET_H
