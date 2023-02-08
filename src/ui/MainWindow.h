﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QtQml>
#include <QQuickStyle>
#include <QIcon>
#include <QFont>
#include <QQuickWindow>
#include <infrastructure/tool/CommonTool.h>
#include <infrastructure/log/Logger.h>
#include <infrastructure/config/AppConfig.h>
#include <controller/MainController.h>
#include <application/di/ApplicationInjector.h>
#include <infrastructure/helper/UiHelper.h>
#include <infrastructure/helper/UserHelper.h>
#include <infrastructure/helper/SettingsHelper.h>

class Q_DECL_EXPORT MainWindow
{
public:
  explicit MainWindow(char* argv[]);

  ~MainWindow();

  void show();

protected:
  QQmlApplicationEngine m_engine;
};
#endif
