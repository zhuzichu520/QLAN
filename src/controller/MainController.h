#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "BaseController.h"

class MainController : public BaseController
{
    Q_OBJECT
    Q_PROPERTY_AUTO(int,resultCode);
    Q_PROPERTY_AUTO(QStringList,driverList);
public:
    explicit MainController(QObject *parent = nullptr);
      ~MainController();

    Q_INVOKABLE void onConnect(const QString& remoteName,const QString& localName);

    Q_INVOKABLE void onRefresh();
};

#endif // MAINCONTROLLER_H
