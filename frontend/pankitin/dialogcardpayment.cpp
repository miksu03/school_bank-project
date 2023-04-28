#include "dialogcardpayment.h"
#include "ui_dialogcardpayment.h"
#include <QGridLayout>
#include <QLabel>
#include <QDateTime>
#include <QLineEdit>
#include <QPushButton>


DialogCardPayment::DialogCardPayment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCardPayment)
{
    //creates a vertical layout and several QLabel widgets for displaying text
    ui->setupUi(this);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QLabel *creditLabel = new QLabel("Credit");
    QFont font("Arial", 16, QFont::Bold);
    creditLabel->setFont(font);
    QLabel *cardLabel = new QLabel("Card:");
    QLabel *amountLabel = new QLabel("Amount:");
    QLabel *pinLabel = new QLabel("PIN:");
    QLabel *wrongPinLabel = new QLabel("Wrong PIN");
    QLabel *notenoughamountLabel = new QLabel("Not enough value on account");

    // Create the spacer items
    QLabel *emptyLabel1 = new QLabel();
    QLabel *emptyLabel2 = new QLabel();
    QLineEdit *emptyLabel3 = new QLineEdit();
    emptyLabel3->setEchoMode(QLineEdit::Password);
    emptyLabel3->setReadOnly(true);

    // Create the layouts
    QHBoxLayout *row1Layout = new QHBoxLayout();
    QHBoxLayout *row2Layout = new QHBoxLayout();
    QHBoxLayout *row3Layout = new QHBoxLayout();
    row1Layout->addWidget(cardLabel);
    row1Layout->addWidget(emptyLabel1);
    row2Layout->addWidget(amountLabel);
    row2Layout->addWidget(emptyLabel2);
    row3Layout->addWidget(pinLabel);
    row3Layout->addWidget(emptyLabel3);
    emptyLabel1->setObjectName("Label1");
    QGridLayout *gridLayout = new QGridLayout();
    int counter = 1;

    // Add widgets to the grid layout
    // The grid consists of 5 rows and 3 columns.
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (counter == 14) {
            }else{
                // Creates a grid of buttons for a keypad interface.
                QPushButton *button = new QPushButton(QString("%1").arg(counter));

                if (counter == 10) {
                    button->setText("Cancel");

                    //The cancel button is connected to a function that either hides the PIN label or closes the application depending on whether the OK button has been clicked.
                    connect(button, &QPushButton::clicked, this, [=](){
                        if(okClikked==true){
                            okClikked=false;
                            pinLabel -> hide();
                            emptyLabel3->clear();
                            emptyLabel3->hide();
                        }else{
                            emptyLabel2->clear();
                            this->close();
                        }
                    });
                } else if (counter == 12) {
                    button->setText("OK");

                    //The OK button is connected to a function that validates the PIN entered and performs the transaction if the input values are valid.
                    connect(button, &QPushButton::clicked, this,[=](){
                        if(okClikked==true){
                            int id = dm.cardFindbyCardNumber(cardLabel->text());
                            if(du.passwordChecer(emptyLabel3->text(), dm.listOfCards[id].pinCode)){
                                //initialize EventObject and AccountObject properties with relevant values from the data model.
                                EventObject eve;
                                AccountObject acc;
                                eve.id = dm.listOfEvents.count();
                                eve.value = emptyLabel1->text().toDouble();
                                eve.idAccount = dm.listOfCards[id].Account_id;
                                eve.date = getCurrentDateTime();
                                acc.id = dm.listOfAccounts[dm.listOfCards[id].Account_id].id;
                                acc.idCard =dm.listOfAccounts[dm.listOfCards[id].Account_id].idCard;
                                acc.idCustomer = dm.listOfAccounts[dm.listOfCards[id].Account_id].idCustomer;

                                //determine how to update the account balance based on whether the transaction is a debit or credit
                                // and whether the account has sufficient funds or credit limit to cover the transaction amount.
                                if (credit == false && dm.listOfAccounts[dm.listOfCards[id].Account_id].value > emptyLabel1->text().toDouble()){
                                    dm.add(eve, dm.listOfEvents.count());
                                    acc.value = dm.listOfAccounts[dm.listOfCards[id].Account_id].value - emptyLabel1->text().toDouble();
                                    acc.maxCredit = dm.listOfAccounts[dm.listOfCards[id].Account_id].maxCredit;
                                    dm.update(acc);
                                    this->close();
                                }else if(dm.listOfAccounts[dm.listOfCards[id].Account_id].maxCredit > emptyLabel1->text().toDouble()){
                                    dm.add(eve, dm.listOfEvents.count());
                                    acc.value = dm.listOfAccounts[dm.listOfCards[id].Account_id].value;
                                    acc.maxCredit = dm.listOfAccounts[dm.listOfCards[id].Account_id].maxCredit - emptyLabel1->text().toDouble();
                                    dm.update(acc);
                                    this->close();

                                //shows error message
                                }else {
                                    notenoughamountLabel->show();
                                }
                            }else {
                                wrongPinLabel->show();
                            }
                        }else{
                            okClikked = true;
                            pinLabel -> show();
                            emptyLabel3->show();
                        }
                    });

                //The Credit and Debit buttons are used to toggle between credit and debit transaction modes.
                }else if (counter == 13) {
                    button->setText("Credit");
                    connect(button, &QPushButton::clicked, this, [=](){
                        // Handle OK button click here
                        credit = true;
                        creditLabel->setText("Credit");
                    });
                }else if (counter == 15) {
                    button->setText("Debit");
                    connect(button, &QPushButton::clicked, this, [=](){
                        // Handle OK button click here
                        credit = false;
                        creditLabel->setText("Debit");
                    });

                //The 0-9 buttons are connected to a function that updates the value of the input field
                }else if (counter == 11) {
                    button->setText("0");
                    connect(button, &QPushButton::clicked, this, [=](){
                        // Handle 0 button click here
                        if(okClikked==false){
                            emptyLabel2->setText(emptyLabel2->text() + QString("%1").arg(0));
                        }else{
                            if (emptyLabel3->text().count() < 4){
                                emptyLabel3->setText(emptyLabel3->text() +QString("%1").arg(0));
                            }else{
                                QString code = emptyLabel3->text();
                                code.remove(0,1);
                                emptyLabel3->setText(code + QString("%1").arg(0));
                            }
                        }
                    });
                }else {
                    connect(button, &QPushButton::clicked, this, [=](){
                        if(okClikked==false){
                            emptyLabel2->setText(emptyLabel2->text() + QString("%1").arg(counter));
                        }else{
                            if (emptyLabel3->text().count() < 4){
                                emptyLabel3->setText(emptyLabel3->text() +QString("%1").arg(counter));
                            }else{
                                QString code = emptyLabel3->text();
                                code.remove(0,1);
                                emptyLabel3->setText(code + QString("%1").arg(counter));
                            }
                        }
                    });
                }
                //add the button to grid
                gridLayout->addWidget(button, row, col);
            }
            counter++;
        }
    }

    //sets up the main layout with various labels, adds layouts and widgets to it, and hides some of them
    mainLayout->setAlignment(Qt::AlignCenter);
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    mainLayout->addWidget(creditLabel);
    mainLayout->addLayout(row1Layout);
    mainLayout->addLayout(row2Layout);
    mainLayout->addLayout(row3Layout);
    mainLayout->addWidget(wrongPinLabel);
    mainLayout->addLayout(gridLayout);
    pinLabel -> hide();
    emptyLabel3->hide();
    wrongPinLabel->hide();
    setLayout(mainLayout);
}

DialogCardPayment::~DialogCardPayment()
{
    delete ui;
}
