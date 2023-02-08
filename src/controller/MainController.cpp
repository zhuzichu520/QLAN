#include "MainController.h"


#include <Windows.h>

MainController::MainController(QObject *parent)
    : BaseController{parent}
{

}

MainController::~MainController() {}

void MainController::onRefresh(){
    DWORD bufferSize = MAX_PATH;
    wchar_t buffer[MAX_PATH];
    DWORD result = GetLogicalDriveStrings(bufferSize, buffer);
    QStringList usedDriveLetters;
    for (wchar_t* drive = buffer; *drive != '\0'; drive += wcslen(drive) + 1)
    {
         LOGI(QString::fromStdString("driver->%1").arg(drive).toStdString());
        if (GetDriveType(drive) != DRIVE_NO_ROOT_DIR)
        {
            usedDriveLetters.append(QString::fromWCharArray(drive));
        }
    }
    driverList(usedDriveLetters);
    LOGI(QString::fromStdString("driverList->%1").arg(usedDriveLetters.length()).toStdString());
}

void MainController::onConnect(const QString& remoteName,const QString& localName){
    LOGI(QString::fromStdString("remoteName->%1;localName->%2").arg(remoteName,localName).toStdString());
    rxs::create<int>([=](subscriber<int> subscriber){
        NETRESOURCE nr;
        memset(&nr, 0, sizeof(NETRESOURCE));
        nr.dwType = RESOURCETYPE_DISK;
        std::wstring wstrRemote = QString(remoteName).toStdWString();
        nr.lpRemoteName = (LPWSTR)wstrRemote.c_str();
        std::wstring wstrLocal = QString(localName).toStdWString();
        nr.lpLocalName = (LPWSTR)wstrLocal.c_str();
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
