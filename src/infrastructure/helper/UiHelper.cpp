#include "UiHelper.h"
#include <windows.h>
#include <dwmapi.h>
#include <QSurfaceFormat>
#include <QOpenGLContext>

Q_GLOBAL_STATIC(UiHelper, uiHelper)

UiHelper* UiHelper::instance()
{
    return uiHelper;
}

UiHelper::UiHelper(QObject* parent) : QObject{ parent }
{
    QOpenGLContext ctx;
    ctx.create();
    QSurfaceFormat format = ctx.format();
    if (format.majorVersion()>3) {
        isAeroEnabled = true;
     }else{
        isAeroEnabled = false;
    }
}

QString UiHelper::getRenderVersion(){
    QOpenGLContext ctx;
    ctx.create();
    QSurfaceFormat format = ctx.format();
    return  QString("%1.%2").arg(format.majorVersion()).arg(format.minorVersion());
}

QPoint UiHelper::mousePos()
{
    return QCursor::pos();
}

int UiHelper::getWH(bool isWidth, int width, int height, int ref)
{
    int realW;
    int realH;
    bool flag = width > height;
    if (flag)
    {
        if (width > ref)
        {
            qreal proportion = (qreal)ref / width;
            realW = width * proportion;
            realH = height * proportion;
        }
        else
        {
            realW = width;
            realH = height;
        }
    }
    else
    {
        if (height > ref)
        {
            qreal proportion = (qreal)ref / height;
            realW = width * proportion;
            realH = height * proportion;
        }
        else
        {
            realW = width;
            realH = height;
        }
    }
    if (isWidth)
    {
        return realW;
    }
    else
    {
        return realH;
    }
}

QString UiHelper::uuid(){
    QUuid id = QUuid::createUuid();
    QString strId = id.toString();
    qDebug() << strId;
    //输出结果："{b5eddbaf-984f-418e-88eb-cf0b8ff3e775}"
    strId.remove("{").remove("}").remove("-");
    return strId;
}

void UiHelper::checkUpdate(){
    QString path = QCoreApplication::applicationDirPath()+QDir::separator()+"maintenancetool.exe";
    bool isSuccess = QProcess::startDetached(path,QStringList());
    if(!isSuccess){
        LOGI(QString::fromStdString("打开maintenancetool.exe失败:%1").arg(QCoreApplication::applicationVersion()).toStdString());
    }
}

// 获取当前屏幕索引
int UiHelper::getScreenIndex()
{
    // 需要对多个屏幕进行处理
    int screenIndex = 0;
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    int screenCount = qApp->screens().count();
#else
    int screenCount = qApp->desktop()->screenCount();
#endif

    if (screenCount > 1)
    {
        // 找到当前鼠标所在屏幕
        QPoint pos = QCursor::pos();
        for (int i = 0; i < screenCount; ++i)
        {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
            if (qApp->screens().at(i)->geometry().contains(pos))
            {
#else
            if (qApp->desktop()->screenGeometry(i).contains(pos))
            {
#endif
                screenIndex = i;
                break;
            }
        }
    }
    return screenIndex;
}

void UiHelper::restart(){
    qApp->exit(931);
}

bool UiHelper::aeroEnabled(){
    return isAeroEnabled;
}
