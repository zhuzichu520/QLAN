#include <ui/MainWindow.h>

#include <QApplication>
#include <QGuiApplication>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QProcess>
#include <QQmlApplicationEngine>


int main(int argc, char* argv[]) {
//    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
//    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
//    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
#endif
    QApplication app(argc, argv);
    QTranslator translator;
    auto success = translator.load(":/translations/qtwebengine_zh_CN.qm");
    if(success){
        app.installTranslator(&translator);
    }
    QSharedMemory singleton(app.applicationName());
    if (!singleton.create(1)) {  // 已经存在的
        QMessageBox::critical(nullptr, QObject::tr("错误"), QObject::tr("程序已经在运行，请先关闭！"));
        return -1;
    }
    //    QHotkey hotkey(QKeySequence("Ctrl+Alt+Q"), true, &app);
    //    QObject::connect(&hotkey, &QHotkey::activated, qApp, [&](){
    //        qApp->quit();
    //    });
    MainWindow window(argv);
    QApplication::setOrganizationName("ZHUZICHU.COM");
    QApplication::setApplicationName("QLAN");
    window.show();
    const int exec = QApplication::exec();
    if (exec == 931) {
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }
    return exec;
}
