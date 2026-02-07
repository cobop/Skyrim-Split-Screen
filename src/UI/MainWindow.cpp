#include "UI/MainWindow.h"
#include <QMessageBox>
#include <QFile>
#include <QDateTime>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <iostream>

/*
 * SPDX-FileCopyrightText: 2026 Jane Doe
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), m_config(loadConfig("config.json")), m_launcher(m_config)
{
    // Load configuration (default path)

    // Central widget and layout
    QWidget* central = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    // Buttons
    QHBoxLayout* btnLayout = new QHBoxLayout();
    m_startLeftBtn  = new QPushButton(tr("Start Left"), this);
    m_startRightBtn = new QPushButton(tr("Start Right"), this);
    m_stopAllBtn    = new QPushButton(tr("Stop All"), this);
    btnLayout->addWidget(m_startLeftBtn);
    btnLayout->addWidget(m_startRightBtn);
    btnLayout->addWidget(m_stopAllBtn);
    mainLayout->addLayout(btnLayout);

    // Log view
    m_logEdit = new QTextEdit(this);
    m_logEdit->setReadOnly(true);
    mainLayout->addWidget(m_logEdit);

    setCentralWidget(central);
    setWindowTitle(tr("Skyrim Split‑Screen Launcher"));

    // Connect signals
    connect(m_startLeftBtn,  &QPushButton::clicked, this, &MainWindow::startLeft);
    connect(m_startRightBtn, &QPushButton::clicked, this, &MainWindow::startRight);
    connect(m_stopAllBtn,    &QPushButton::clicked, this, &MainWindow::stopAll);
}
 

void MainWindow::log(const QString& msg)
{
    m_logEdit->append(msg);
    std::cout << "[UI] " << msg.toStdString() << std::endl;
}

void MainWindow::startLeft()
{
    log(tr("Starting left instance..."));
    if (m_leftInstance.launch(m_config, ScreenPlacement::LEFT)) {
        log(tr("Left instance launched, PID %1").arg(m_leftInstance.getPid()));
        if (m_windowManager.placeWindow(m_leftInstance, m_config, ScreenPlacement::LEFT)) {
            log(tr("Left window positioned on monitor %1").arg(m_config.monitor_left));
        } else {
            log(tr("Failed to position left window."));
            QMessageBox::warning(this, tr("Window Placement"),
                                 tr("Could not place left window on the monitor."));
        }
    } else {
        log(tr("Failed to launch left instance."));
        QMessageBox::critical(this, tr("Launch Error"),
                              tr("Failed to launch the left Skyrim instance."));
    }
}

void MainWindow::startRight()
{
    log(tr("Starting right instance..."));
    if (m_rightInstance.launch(m_config, ScreenPlacement::RIGHT)) {
        log(tr("Right instance launched, PID %1").arg(m_rightInstance.getPid()));
        if (m_windowManager.placeWindow(m_rightInstance, m_config, ScreenPlacement::RIGHT)) {
            log(tr("Right window positioned on monitor %1").arg(m_config.monitor_right));
        } else {
            log(tr("Failed to position right window."));
            QMessageBox::warning(this, tr("Window Placement"),
                                 tr("Could not place right window on the monitor."));
        }
    } else {
        log(tr("Failed to launch right instance."));
        QMessageBox::critical(this, tr("Launch Error"),
                              tr("Failed to launch the right Skyrim instance."));
    }
}

void MainWindow::stopAll()
{
    log(tr("Stopping all instances..."));
    // Stop via Launcher (which manages its own instances)
    m_launcher.stopAll();

    // Also ensure UI‑owned instances are terminated
    if (m_leftInstance.getPid() > 0) {
        m_leftInstance.terminate();
        log(tr("Left instance terminated."));
    }
    if (m_rightInstance.getPid() > 0) {
        m_rightInstance.terminate();
        log(tr("Right instance terminated."));
    }
}
