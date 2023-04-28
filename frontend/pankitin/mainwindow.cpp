#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "databasemanager.h"
#include <QStackedWidget>
#include <QScrollArea>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //initializes the user interface, creates a stacked widget to switch between different screens
    ui->setupUi(this);
    m_stackedWidget = new QStackedWidget(this);
    QWidget* window = new QWidget(this);
    QScrollArea* scrollArea = new QScrollArea(this);
    QScrollBar* scrollBar = new QScrollBar(this);
    scrollArea->setHorizontalScrollBar(scrollBar);

    //sets up the login screen with username and password fields, a login button, and a scroll area
    QLabel *usernameLabel = new QLabel("Username:", this);
    m_usernameField = new QLineEdit(this);
    QLabel *passwordLabel = new QLabel("Password:", this);
    m_passwordField = new QLineEdit(this);
    m_passwordField->setEchoMode(QLineEdit::Password);
    QPushButton *loginButton = new QPushButton("Login", this);

    // Create a grid layout
    QGridLayout *gridLayout = new QGridLayout(window);
    gridLayout->addWidget(usernameLabel, 0, 0);
    gridLayout->addWidget(m_usernameField, 0, 1);
    gridLayout->addWidget(passwordLabel, 1, 0);
    gridLayout->addWidget(m_passwordField, 1, 1);

    // Add the layouts to a central widget
    // Set the central widget of the main window
    window->setLayout(gridLayout);
    window->layout()->addWidget(loginButton);
    window->layout()->setAlignment(loginButton, Qt::AlignHCenter);
    m_wrongpasswordLabel = new QLabel("Wrong password or username", this);
    window->layout()->addWidget(m_wrongpasswordLabel);
    window->layout()->setAlignment(m_wrongpasswordLabel, Qt::AlignHCenter);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::loginClicked);
    m_wrongpasswordLabel->hide();

    // create stacked widget and add login and grid widgets
    m_stackedWidget->addWidget(window);
    m_stackedWidget->addWidget(scrollArea);
    setCentralWidget(m_stackedWidget);
    m_stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Handles the login button clicks, verifies the username and password, and displays an error message if the password is incorrect
void MainWindow::loginClicked()
{
    if(m_usernameField->text() != "" || m_passwordField->text() != ""){
        for (int i = 0; dm.listOfCards.count() > i; i++){
            if(dm.listOfCards[i].CardNumber == m_usernameField->text()){
                if(du.passwordChecer(m_passwordField->text(), dm.listOfCards[i].password)){
                    gridPopulater(dm.listOfCards[i].Account_id);
                    // Switch to the grid page
                    m_stackedWidget->setCurrentIndex(1);
                    return;
                }
            }
        }
    }
    m_wrongpasswordLabel->show();
}

//creates and populates the grid
void MainWindow::gridPopulater(int customerID)
{
    //delete prewious stacked grid so next can be shown
    QWidget* widgetToRemove = m_stackedWidget->widget(1); // Get the widget at index 1
    m_stackedWidget->removeWidget(widgetToRemove); // Remove the widget from the stacked widget
    delete widgetToRemove;

    //make the grid scrollable
    QScrollArea* scrollArea = new QScrollArea(this);
    QScrollBar* scrollBar = new QScrollBar(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBar(scrollBar);

    //create the grid of events
    QGridLayout *eventLayout = new QGridLayout(this);
    int count = 0;
    for(int i=0; i < dm.listOfEvents.count(); i++) {
        if(dm.listOfEvents[i].idAccount == customerID){
            QLabel *label = new QLabel(dm.listOfEvents[i].date);
            eventLayout->addWidget(label, count, 0);
            QLabel *label2 = new QLabel(QString::number(dm.listOfEvents[i].value));
            eventLayout->addWidget(label2, count, 1);
            count++;
        }
    }

    //create close button
    QPushButton *button = new QPushButton(QString("Back"));
    connect(button, &QPushButton::clicked, this, [=](){
        // Handle Back button click here
        m_stackedWidget->setCurrentIndex(0);
    });
    QLabel *label = new QLabel("value: " + QString::number(dm.listOfAccounts[customerID].value));
    eventLayout->addWidget(label, count, 1);
    eventLayout->addWidget(button, count, 0);

    //create grid widget and connect it to scroll area and add to stack
    QWidget *gridWidget = new QWidget(this);
    gridWidget->setLayout(eventLayout);
    scrollArea->setWidget(gridWidget);
    m_stackedWidget->addWidget(scrollArea);
}

