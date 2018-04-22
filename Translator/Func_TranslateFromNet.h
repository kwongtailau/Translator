#ifndef FUNC_TRANSLATEFROMNET_H
#define FUNC_TRANSLATEFROMNET_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QUrl>

class Func_TranslateFromNet : public QObject
{
    Q_OBJECT
public:
    explicit Func_TranslateFromNet(QObject *parent = nullptr);
    ~Func_TranslateFromNet();
public:
    //调用API获取报文
    void getReply(QString stringInput, int replyCaseInput);
signals:
    //各种信号的定义
    void signalValueTranslationFinished(QString stringTranslation);
    void signalValuePhoneticFinished(QString stringPhonetic);
    void signalValueExplainsFinished(QString stringExplain);
    void signalValueQueryFinished(QString stringQuery);
private slots:
    void replayFinished(QNetworkReply * translationReply);
private:
    QNetworkAccessManager * networkManager;
    int replayCase;
};

#endif // FUNC_TRANSLATEFROMNET_H
