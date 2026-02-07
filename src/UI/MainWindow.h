#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include "Launcher.h"
#include "Config.h"
#include "GameInstance.h"
#include "WindowManager.h"

/*
 * SPDX-FileCopyrightText: 2026 Jane Doe
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void startLeft();
    void startRight();
    void stopAll();

private:
    void log(const QString& msg);

    QPushButton* m_startLeftBtn{nullptr};
    QPushButton* m_startRightBtn{nullptr};
    QPushButton* m_stopAllBtn{nullptr};
    QTextEdit*   m_logEdit{nullptr};

    Config        m_config;
    Launcher      m_launcher;
    GameInstance  m_leftInstance;
    GameInstance  m_rightInstance;
    WindowManager m_windowManager;
};
