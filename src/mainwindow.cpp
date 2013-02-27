#include <QtGui>
#include <QFile>
#include <time.h>
#include "mainwindow.h"

MainWindow::MainWindow()
{
    player1Turn = true;
    correctAnswer = false;
    gameOver = false;
    questionIDVector = returnQuestionIDVector();

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

    setQuestionText();

}

QVector<int> MainWindow::returnQuestionIDVector()
{
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
            questionIDVector.append(dataList.at(0).toInt());
            dataString = dataStream->readLine();
        }
    }

    questionBankFile->close();
    return questionIDVector;
}

int MainWindow::returnRandomNumber(int nMax)
{

    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);

    int nRandomNumber = rand() % nMax;
    nRandomNumber;

    return nRandomNumber;

}

void MainWindow::setQuestionText()
{
    QMessageBox playerWins;

    if (player2Score->value() >= 10 && player1Score->value() < player2Score->value() - 1)
    {
        playerWins.setText("Congratulations, Player 2! You win!");
        playerWins.exec();
        gameOver = true;
    }

    else if (player1Score->value() >= 10 && player2Score->value() < player1Score->value() - 1)
    {
        playerWins.setText("Congratulations, Player 1! You win!");
        playerWins.exec();
        gameOver = true;
    }


    if (!questionIDVector.isEmpty())
    {

        int questionLocationID = returnRandomNumber(questionIDVector.size());
        int questionID = questionIDVector.at(questionLocationID);

        int i = 0;
        while (questionIDVector.at(i) != questionID)
        {
            i++;
        }
        questionIDVector.remove(i);

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
    else
    {
        QMessageBox endBankError;
        endBankError.setText(tr("Error: You have reached the end of the question bank."));
        endBankError.exec();

        gameOver = true;
    }

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
            correctAnswer = true;
        }

        else
        {
            answerResult.setText(tr("Sorry, that's not correct. The correct answer is:\n%1")
                                 .arg(dataList.at(2)));
            answerResult.exec();
            correctAnswer = false;
        }

        answer1->setChecked(false);
    }
        break;

    case 2:
    {
        if (answer2->isChecked())
        {
            answerResult.setText("Correct!");
            answerResult.exec();
            correctAnswer = true;
        }

        else
        {
            answerResult.setText(tr("Sorry, that's not correct. The correct answer is:\n%1")
                                 .arg(dataList.at(3)));
            answerResult.exec();
            correctAnswer = false;
        }
        answer2->setChecked(false);
    }
        break;


    case 3:
    {
        if (answer3->isChecked())
        {
            answerResult.setText("Correct!");
            answerResult.exec();
            correctAnswer = true;
        }

        else
        {
            answerResult.setText(tr("Sorry, that's not correct. The correct answer is:\n%1")
                                 .arg(dataList.at(4)));
            answerResult.exec();
            correctAnswer = false;
        }
        answer3->setChecked(false);
    }
        break;

    case 4:
    {
        if (answer4->isChecked())
        {
            answerResult.setText("Correct!");
            answerResult.exec();
            correctAnswer = true;
        }

        else
        {
            answerResult.setText(tr("Sorry, that's not correct. The correct answer is:\n%1")
                                 .arg(dataList.at(5)));
            answerResult.exec();
            correctAnswer = false;
        }
        answer4->setChecked(false);
    }
        break;

    }

    questionBankFile->close();
    updateTurns();
}

void MainWindow::updateTurns()
{
    if (player1Turn)
    {
        player1Turn = false;
        player2Turn = true;
        if (correctAnswer)
        {
            int player1CurrentScore = player1Score->value();
            player1CurrentScore++;
            player1Score->setValue(player1CurrentScore);
        }
    }
    else
    {
        player1Turn = true;
        player2Turn = false;
        if (correctAnswer)
        {
            int player2CurrentScore = player2Score->value();
            player2CurrentScore++;
            player2Score->setValue(player2CurrentScore);
        }
    }

    setQuestionText();
}
