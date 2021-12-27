#include "test01.h"
//#include <QDebug>

Test01::Test01(QObject *parent)
    : QObject{parent}
{

}

void Test01::setMessage(const QString message)
{
  this->message = message;
}

QString Test01::getMessage()
{
  return this->message;

}

void Test01::printMessage()
{
  qInfo() << message;
}
