#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "BaseController.h"

class MainController : public BaseController
{
    Q_OBJECT
    Q_PROPERTY_AUTO(int,resultCode);
public:
    explicit MainController(QObject *parent = nullptr);
      ~MainController();

    Q_INVOKABLE void onConnect(const QString& remoteName,const QString& localName);

};

#endif // MAINCONTROLLER_H
