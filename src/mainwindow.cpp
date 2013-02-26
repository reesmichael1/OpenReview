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

    answer1 = new QCheckBox;
    //answer1->setText("This is the first answer.");
    answer1->setAutoExclusive(true);

    answer2 = new QCheckBox;
    //answer2->setText("This is the second answer.");
    answer2->setAutoExclusive(true);

    answer3 = new QCheckBox;
    //answer3->setText("This is the third answer.");
    answer3->setAutoExclusive(true);

    answer4 = new QCheckBox;
    //answer4->setText("This is the fourth answer.");
    answer4->setAutoExclusive(true);

    submitButton = new QPushButton(tr("Submit"));

    QGridLayout *scoreLayout = new QGridLayout;
    scoreLayout->addWidget(player1Label, 0, 0);
    scoreLayout->addWidget(player1Score, 1, 0);
    scoreLayout->addWidget(player2Label, 0, 1);
    scoreLayout->addWidget(player2Score, 1, 1);

    QVBoxLayout *answerLayout = new QVBoxLayout;
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

    setWindowTitle(tr("Reconstruction Revealed"));

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
