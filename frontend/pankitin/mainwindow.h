#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "databasemanager.h"
#include <QMainWindow>
#include <../pankitinDLL/databaseurl.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLineEdit;
class QLabel;
class QStackedWidget;
class QGridLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void loginClicked();
private:
    void gridPopulater(int customerID);
    QLineEdit *m_usernameField{nullptr};
    QLineEdit *m_passwordField{nullptr};
    QLabel *m_wrongpasswordLabel{nullptr};
    QStackedWidget* m_stackedWidget{nullptr};
    DatabaseManager dm;
    Ui::MainWindow *ui;
    databaseUrl du;
};
#endif // MAINWINDOW_H
