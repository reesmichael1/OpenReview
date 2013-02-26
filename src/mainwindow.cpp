#include <QtGui>
#include <QFile>
#include "mainwindow.h"

MainWindow::MainWindow()
{
    QLabel *player1Label = new QLabel(tr("Player 1"));
    QLabel *player2Label = new QLabel(tr("Player 2"));

    player1Score = new QSpinBox;
    player1Score->setReadOnly(true);

    player2Score = new QSpinBox;
    player2Score->setReadOnly(true);

    questionText = new QTextEdit;
    questionText->setReadOnly(true);
    questionText->setMaximumWidth(200);
    questionText->setFixedWidth(240);

    answer1 = new QCheckBox;
    answer1->setAutoExclusive(true);

    answer2 = new QCheckBox;
    answer2->setAutoExclusive(true);

    answer3 = new QCheckBox;
    answer3->setAutoExclusive(true);

    answer4 = new QCheckBox;
    answer4->setAutoExclusive(true);

    submitButton = new QPushButton(tr("Submit"));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));

    QGridLayout *scoreLayout = new QGridLayout;
    scoreLayout->addWidget(player1Label, 0, 0);
    scoreLayout->addWidget(player1Score, 1, 0);
    scoreLayout->addWidget(player2Label, 0, 1);
    scoreLayout->addWidget(player2Score, 1, 1);

    QVBoxLayout *answerLayout = new QVBoxLayout;
    answerLayout->addWidget(questionText);
    answerLayout->addWidget(answer1);
    answerLayout->addWidget(answer2);
    answerLayout->addWidget(answer3);
    answerLayout->addWidget(answer4);
    answerLayout->addWidget(submitButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(scoreLayout);
    mainLayout->addLayout(answerLayout);

    centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);

    setWindowTitle(tr("Reconstruction"));

    enterGameplay();

}

QVector<int> MainWindow::returnQuestionIDVector()
{
    QVector<int> IDVector;

    QFile *questionBankFile = new QFile("questionbank.txt");
    dataStream = new QTextStream(questionBankFile);
    questionBankFile->open(QIODevice::Text | QIODevice::ReadOnly);

    QString dataString = dataStream->readLine();
    QStringList dataList;

    if (dataString != "")
    {
        while (dataString != "")
        {
            dataList = dataString.split(",");
            IDVector.append(dataList.at(0).toInt());
            dataString = dataStream->readLine();
        }
    }

    questionBankFile->close();
    return IDVector;
}

int MainWindow::returnRandomNumber(int nMax)
{
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);

    int nRandomNumber = rand() % nMax;
    nRandomNumber++;
    return nRandomNumber;
}

void MainWindow::setQuestionText(QVector<int> questionIDVector)
{

    int questionID = returnRandomNumber(questionIDVector.size());
    /*
    for (int i = 0; questionIDVector.at(i); i++)
    {
        if (questionIDVector.at(i) == questionID)
        {
            questionIDVector.remove(i);
        }
    }
    */

    QFile *questionBankFile = new QFile("questionbank.txt");
    dataStream = new QTextStream(questionBankFile);

    questionBankFile->open(QIODevice::Text | QIODevice::ReadOnly);

    QStringList dataList;
    QString dataString = dataStream->readLine();
    while (dataString != "")
    {
        dataList = dataString.split(',');
        if (dataList.at(0).toInt() == questionID)
        {
            questionText->setText(dataList.at(1));
            answer1->setText(dataList.at(2));
            answer2->setText(dataList.at(3));
            answer3->setText(dataList.at(4));
            answer4->setText(dataList.at(5));
            dataString = dataStream->readLine();
            dataList = dataString.split(',');
        }
        else
        {
            dataString = dataStream->readLine();
            dataList = dataString.split(',');
        }
    }

}

void MainWindow::enterGameplay()
{
    QVector<int> questionIDVector = returnQuestionIDVector();
    setQuestionText(questionIDVector);
}

void MainWindow::submit()
{
    QFile *questionBankFile = new QFile("questionbank.txt");
    dataStream = new QTextStream(questionBankFile);

    questionBankFile->open(QIODevice::ReadOnly | QIODevice::Text);

    QString dataString = dataStream->readLine();
    QStringList dataList = dataString.split(',');

    while (dataList.at(1) != questionText->toPlainText())
    {
        dataString = dataStream->readLine();
        dataList = dataString.split(',');
    }

    QMessageBox answerResult;

    switch (dataList.at(6).toInt())
    {

    case 1:
    {
        if (answer1->isChecked())
        {
            answerResult.setText("Correct!");
            answerResult.exec();
        }

        else
        {
            answerResult.setText(tr("Sorry, that's not correct. The correct answer is:\n%1")
                                 .arg(dataList.at(2)));
            answerResult.exec();
        }
    }
        break;

    case 2:
    {
        if (answer2->isChecked())
        {
            answerResult.setText("Correct!");
            answerResult.exec();
        }

        else
        {
            answerResult.setText(tr("Sorry, that's not correct. The correct answer is:\n%1")
                                 .arg(dataList.at(3)));
            answerResult.exec();
        }
    }
        break;


    case 3:
    {
        if (answer3->isChecked())
        {
            answerResult.setText("Correct!");
            answerResult.exec();
        }

        else
        {
            answerResult.setText(tr("Sorry, that's not correct. The correct answer is:\n%1")
                                 .arg(dataList.at(4)));
            answerResult.exec();
        }
    }
        break;

    case 4:
    {
        if (answer4->isChecked())
        {
            answerResult.setText("Correct!");
            answerResult.exec();
        }

        else
        {
            answerResult.setText(tr("Sorry, that's not correct. The correct answer is:\n%1")
                                 .arg(dataList.at(5)));
            answerResult.exec();
        }
    }
        break;

    }

    questionBankFile->close();
}
