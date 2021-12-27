#ifndef TEST01_H
#define TEST01_H

#include <QObject>
#include <QString>
#include <QDebug>

class Test01 : public QObject
{
    Q_OBJECT
public:
    explicit Test01(QObject *parent = nullptr);

    void setMessage( const QString message );
    QString getMessage();

    void printMessage();

protected:
    QString message;

signals:

};

#endif // TEST01_H
