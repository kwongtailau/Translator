#include "Func_TranslateFromNet.h"

/*
*       JSON数据格式举例：
*        {
*            "errorCode":0
*            "query":"good",
*            "translation":["好"],       // 有道翻译
*            "basic":{                  // 有道词典-基本词典
*                "phonetic":"gʊd"
*                "uk-phonetic":"gʊd"    //英式发音
*                "us-phonetic":"ɡʊd"    //美式发音
*                "explains":[
*                    "好处",
*                    "好的"
*                    "好"
*                ]
*            },
*            "web":[ // 有道词典-网络释义
*                {
*                    "key":"good",
*                    "value":["良好","善","美好"]
*                },
*                {...}
*            ]
*        }
*/

Func_TranslateFromNet::Func_TranslateFromNet(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
    //建立连接 当调用API获取数据完成后 就会触发finished信号
    connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replayFinished(QNetworkReply *)));
}

Func_TranslateFromNet::~Func_TranslateFromNet()
{

}

/*调用API获取报文*/
void Func_TranslateFromNet::getReply(QString stringInput, int replyCaseInput)
{
    replayCase = replyCaseInput;
    //调用有道翻译API
    networkManager->get(QNetworkRequest(QUrl(
        "http://fanyi.youdao.com/openapi.do?keyfrom=iktranslator&key=53427012&type=data&doctype=json&version=1.1&q="
        + stringInput)));
}

/*根据json解释单词*/
void Func_TranslateFromNet::replayFinished(QNetworkReply *translationReply)
{
    //解析JSON数据
    QJsonDocument jsonDoc = QJsonDocument::fromJson(translationReply->readAll());
    QJsonObject jsonObj = jsonDoc.object();
    //原文
    QString replayQuery = jsonObj.value("query").toString();
    //单词或者长句的译文
    QString replayTranslation = jsonObj.value("translation").toArray().at(0).toString();
    //单词的音标
    QString replayPhonetic = jsonObj.value("basic").toObject().value("phonetic").toString();
    //单词的意思
    QJsonArray jsonArrayTemp = jsonObj.value("basic").toObject().value("explains").toArray();
    QString replayExplains = "";
    for (int count = 0; count < jsonArrayTemp.size(); count++)
        replayExplains += jsonArrayTemp.at(count).toString() + "\n";
    //根据replayCase的值发射信号
    switch (replayCase) {
        case 0:
            emit signalValueQueryFinished(replayQuery); break;               //原文
        case 1:
            emit signalValueTranslationFinished(replayTranslation); break;   //单词或者长句译文
        case 2:
            emit signalValueExplainsFinished(replayExplains); break;         //单词意思
        case 3:
            emit signalValuePhoneticFinished(replayPhonetic); break;         //单词音标
    }
    translationReply->deleteLater();
}
