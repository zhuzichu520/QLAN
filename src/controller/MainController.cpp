#include "MainController.h"


#include <Windows.h>

MainController::MainController(QObject *parent)
    : BaseController{parent}
{

}

MainController::~MainController() {}


void MainController::onConnect(const QString& remoteName,const QString& localName){
    LOGI(QString::fromStdString("remoteName->%1，localName->%2").arg(remoteName,localName).toStdString());
    rxs::create<int>([=](subscriber<int> subscriber){
        NETRESOURCE nr;
        memset(&nr, 0, sizeof(NETRESOURCE));
        nr.dwType = RESOURCETYPE_DISK;
        nr.lpRemoteName = (LPWSTR)QString("%1").arg(remoteName).toStdWString().c_str();
        nr.lpLocalName = (LPWSTR)QString("%1").arg(localName).toStdWString().c_str();
        DWORD result = WNetAddConnection2(&nr, NULL, NULL, 0);
        if (result == NO_ERROR) {
            qDebug() << "Mapping successful";
        } else {
            qDebug() << "Mapping failed with error code" << result;
        }
        subscriber.on_next(result);
        subscriber.on_completed();
    }).subscribe_on(Rx->IO()).observe_on(Rx->mainThread()).subscribe([=](int data){
        resultCode(data);
    },
    [this](const rxu::error_ptr& error){
        handleError(error,[](const BizException& e){

        });
    });
}
