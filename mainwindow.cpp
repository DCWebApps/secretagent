#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QCloseEvent>
#include <QDebug>
#include <windows.h>
#include <QIcon>
#include <QPixmap>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QStringList arguments;

    ui->setupUi(this);

    m_trayIcon = new QSystemTrayIcon();
    m_trayIcon->setIcon(QIcon(":/AppIcon.ico"));

    m_agentProcess = new QProcess;
    m_agentProcess->setWorkingDirectory("C:\\BuildAgent\\bin");

    arguments.append("-ea");
    arguments.append("-Xmx384m");
    arguments.append("-Dlog4j.configuration=file:../conf/teamcity-agent-log4j.xml");
    arguments.append("-Dteamcity_logs=../logs/");
    arguments.append("-classpath");
    arguments.append("C:\\BuildAgent\\lib\\agent-configurator.jar;C:\\BuildAgent\\lib\\agent-installer-ui.jar;C:\\BuildAgent\\lib\\agent-launcher.jar;C:\\BuildAgent\\lib\\agent-openapi.jar;C:\\BuildAgent\\lib\\agent-upgrade.jar;C:\\BuildAgent\\lib\\agent.jar;C:\\BuildAgent\\lib\\annotations.jar;C:\\BuildAgent\\lib\\app-wrapper.jar;C:\\BuildAgent\\lib\\buildAgent-updates-applying.jar;C:\\BuildAgent\\lib\\cloud-shared.jar;C:\\BuildAgent\\lib\\common-impl.jar;C:\\BuildAgent\\lib\\common-runtime.jar;C:\\BuildAgent\\lib\\common.jar;C:\\BuildAgent\\lib\\commons-beanutils-core.jar;C:\\BuildAgent\\lib\\commons-codec.jar;C:\\BuildAgent\\lib\\commons-collections-3.2.2.jar;C:\\BuildAgent\\lib\\commons-compress-1.9.jar;C:\\BuildAgent\\lib\\commons-httpclient-3.1.jar;C:\\BuildAgent\\lib\\commons-io-1.3.2.jar;C:\\BuildAgent\\lib\\commons-logging.jar;C:\\BuildAgent\\lib\\coverage-agent-common.jar;C:\\BuildAgent\\lib\\coverage-report.jar;C:\\BuildAgent\\lib\\duplicator-util.jar;C:\\BuildAgent\\lib\\ehcache-1.6.0-patch.jar;C:\\BuildAgent\\lib\\ehcache-1.7.2.jar;C:\\BuildAgent\\lib\\freemarker.jar;C:\\BuildAgent\\lib\\gson.jar;C:\\BuildAgent\\lib\\idea-settings.jar;C:\\BuildAgent\\lib\\inspections-util.jar;C:\\BuildAgent\\lib\\jaxen-1.1.1.jar;C:\\BuildAgent\\lib\\jdk-searcher.jar;C:\\BuildAgent\\lib\\jdom.jar;C:\\BuildAgent\\lib\\joda-time.jar;C:\\BuildAgent\\lib\\launcher-api.jar;C:\\BuildAgent\\lib\\launcher.jar;C:\\BuildAgent\\lib\\log4j-1.2.12-json-layout.jar;C:\\BuildAgent\\lib\\log4j-1.2.12.jar;C:\\BuildAgent\\lib\\messages.jar;C:\\BuildAgent\\lib\\nuget-utils.jar;C:\\BuildAgent\\lib\\openapi.jar;C:\\BuildAgent\\lib\\patches-impl.jar;C:\\BuildAgent\\lib\\patches.jar;C:\\BuildAgent\\lib\\processesTerminator.jar;C:\\BuildAgent\\lib\\resources_en.jar;C:\\BuildAgent\\lib\\runtime-util.jar;C:\\BuildAgent\\lib\\server-logging.jar;C:\\BuildAgent\\lib\\serviceMessages.jar;C:\\BuildAgent\\lib\\slf4j-api-1.7.5.jar;C:\\BuildAgent\\lib\\slf4j-log4j12-1.7.5.jar;C:\\BuildAgent\\lib\\spring-scripting\\spring-scripting-bsh.jar;C:\\BuildAgent\\lib\\spring-scripting\\spring-scripting-groovy.jar;C:\\BuildAgent\\lib\\spring-scripting\\spring-scripting-jruby.jar;C:\\BuildAgent\\lib\\spring.jar;C:\\BuildAgent\\lib\\trove-3.0.3.jar;C:\\BuildAgent\\lib\\trove4j.jar;C:\\BuildAgent\\lib\\util.jar;C:\\BuildAgent\\lib\\xercesImpl.jar;C:\\BuildAgent\\lib\\xml-rpc-wrapper.jar;C:\\BuildAgent\\lib\\xmlrpc-2.0.1.jar;C:\\BuildAgent\\lib\\xpp3-1.1.4c.jar;C:\\BuildAgent\\lib\\xstream-1.4.11.1-custom.jar;C:\\BuildAgent\\lib\\xz-1.5.jar");
    arguments.append("jetbrains.buildServer.agent.AgentMain");
    arguments.append("-file");
    arguments.append("..\\conf\\buildAgent.properties");
    arguments.append("-launcher.version");
    arguments.append("72031");

    connect(m_agentProcess, &QProcess::readyReadStandardOutput, [=]() {
        ui->textEdit->append(QString::fromUtf8(m_agentProcess->readAllStandardOutput()));
    });

    connect(m_agentProcess, &QProcess::errorOccurred, [=](QProcess::ProcessError) {
        if (m_agentProcess) {
            QMessageBox::critical(this, "SecretAgent Error", "Unable to start BuildAgent.\r\n\r\n"+m_agentProcess->errorString());
        }

        m_agentProcess = nullptr;

        this->close();
    });

    m_agentProcess->start("C:\\BuildAgent\\jre\\bin\\java.exe", arguments);

    connect(m_agentProcess, SIGNAL(finished(int)), this, SLOT(onAgentFinished(int)));

    m_contextMenu = new QMenu();

    m_quitAction = new QAction("Quit");

    connect(m_quitAction, &QAction::triggered, [this]() {
        QProcess *process = m_agentProcess;

        m_agentProcess = nullptr;

        process->kill();
    });

    m_contextMenu->addAction(m_quitAction);

    m_trayIcon->setContextMenu(m_contextMenu);
    m_trayIcon->setVisible(true);

    connect(m_trayIcon, &QSystemTrayIcon::activated, [this](QSystemTrayIcon::ActivationReason reason) {
        if (reason==QSystemTrayIcon::Trigger) {
            this->show();

            return;
        }
    });
}

void MainWindow::onAgentFinished(int exitCode)
{
    Q_UNUSED(exitCode)

    m_agentProcess = NULL;

    this->close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_agentProcess) {
        event->ignore();

        this->hide();

        return;
    }

    m_trayIcon->hide();

    event->accept();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange) {
        QWindowStateChangeEvent *changeEvent = (QWindowStateChangeEvent *) event;

        if ((changeEvent->oldState() != Qt::WindowMinimized) && isMinimized()) {
            this->setWindowState(changeEvent->oldState());
            this->hide();

            return;
        }
    }

    QWidget::changeEvent(event);
}
