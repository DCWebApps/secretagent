#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAgentFinished(int exitCode);

protected:
    virtual void closeEvent(QCloseEvent *event);
    virtual void changeEvent(QEvent *event);

private:
    Ui::MainWindow *ui;

    QProcess *m_agentProcess;
    QSystemTrayIcon *m_trayIcon;
    QMenu *m_contextMenu;
    QAction *m_quitAction;
};
#endif // MAINWINDOW_H
