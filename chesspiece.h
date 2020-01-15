#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <QString>
#include <QPixmap>


class ChessPiece
{
public:
    ChessPiece();
public:
    int x;
    int y;
    int id;
    bool isRed;
    bool isAlive = true;
    QString name;
    QPixmap picture, selectedPic;
};

class Zu : public ChessPiece
{
public:
    Zu(int x, int y, bool isRed, int id)
    {
        this->x = x;
        this->y = y;
        this->isRed = isRed;
        this->id = id;
        name = "Zu";
        if (isRed)
        {
            picture = QPixmap(":/img/images/RP.GIF");
            selectedPic = QPixmap(":/img/images/RPS.GIF");
        }
        else
        {
            picture = QPixmap(":/img/images/BP.GIF");
            selectedPic = QPixmap(":/img/images/BPS.GIF");
        }
    }
};

class Pao : public ChessPiece
{
public:
    Pao(int x, int y, bool isRed, int id)
    {
        this->x = x;
        this->y = y;
        this->isRed = isRed;
        this->id = id;
        name = "Pao";
        if (isRed)
        {
            picture = QPixmap(":/img/images/RC.GIF");
            selectedPic = QPixmap(":/img/images/RCS.GIF");
        }
        else
        {
            picture = QPixmap(":/img/images/BC.GIF");
            selectedPic = QPixmap(":/img/images/BCS.GIF");
        }
    }
};

class Che : public ChessPiece
{
public:
    Che(int x, int y, bool isRed, int id)
    {
        this->x = x;
        this->y = y;
        this->isRed = isRed;
        this->id = id;
        name = "Che";
        if (isRed)
        {
            picture = QPixmap(":/img/images/RR.GIF");
            selectedPic = QPixmap(":/img/images/RRS.GIF");
        }
        else
        {
            picture = QPixmap(":/img/images/BR.GIF");
            selectedPic = QPixmap(":/img/images/BRS.GIF");
        }
    }
};

class Ma : public ChessPiece
{
public:
    Ma(int x, int y, bool isRed, int id)
    {
        this->x = x;
        this->y = y;
        this->isRed = isRed;
        this->id = id;
        name = "Ma";
        if (isRed)
        {
            picture = QPixmap(":/img/images/RN.GIF");
            selectedPic = QPixmap(":/img/images/RNS.GIF");
        }
        else
        {
            picture = QPixmap(":/img/images/BN.GIF");
            selectedPic = QPixmap(":/img/images/BNS.GIF");
        }
    }
};

class Xiang : public ChessPiece
{
public:
    Xiang(int x, int y, bool isRed, int id)
    {
        this->x = x;
        this->y = y;
        this->isRed = isRed;
        this->id = id;
        name = "Xiang";
        if (isRed)
        {
            picture = QPixmap(":/img/images/RB.GIF");
            selectedPic = QPixmap(":/img/images/RBS.GIF");
        }
        else
        {
            picture = QPixmap(":/img/images/BB.GIF");
            selectedPic = QPixmap(":/img/images/BBS.GIF");
        }
    }
};

class Shi : public ChessPiece
{
public:
    Shi(int x, int y, bool isRed, int id)
    {
        this->x = x;
        this->y = y;
        this->isRed = isRed;
        this->id = id;
        name = "Shi";
        if (isRed)
        {
            picture = QPixmap(":/img/images/RA.GIF");
            selectedPic = QPixmap(":/img/images/RAS.GIF");
        }
        else
        {
            picture = QPixmap(":/img/images/BA.GIF");
            selectedPic = QPixmap(":/img/images/BAS.GIF");
        }
    }
};

class Shuai : public ChessPiece
{
public:
    Shuai(int x, int y, bool isRed, int id)
    {
        this->x = x;
        this->y = y;
        this->isRed = isRed;
        this->id = id;
        name = "Shuai";
        if (isRed)
        {
            picture = QPixmap(":/img/images/RK.GIF");
            selectedPic = QPixmap(":/img/images/RKS.GIF");
        }
        else
        {
            picture = QPixmap(":/img/images/BK.GIF");
            selectedPic = QPixmap(":/img/images/BKS.GIF");
        }
    }
};

#endif // CHESSPIECE_H
