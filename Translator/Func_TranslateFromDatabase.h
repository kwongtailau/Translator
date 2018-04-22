#ifndef FUNC_TRANSLATEFROMDATABASE_H
#define FUNC_TRANSLATEFROMDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QVariant>
#include <QVector>
#include <QString>

class Func_TranslateFromDatabase : public QObject
{
    Q_OBJECT
public:
    explicit Func_TranslateFromDatabase(QObject *parent = nullptr);
    ~Func_TranslateFromDatabase();

public:
    QString getReplyFromEN(QString stringInput);//中译英
    QString getReplyFromCN(QString stringInput);//英译中
    QStringList getWordList();                  //获取单词的列表，用于自动补全

private:
    struct wordType {
        int id;
        QString word;   //单词
        QString gqs;    //过去式
        QString gqfc;   //过去分词
        QString xzfc;   //现在分词
        QString fs;     //单词的复数形式
        QString meaning;//单词的意思
        QString lx;     //该单词的例句
    };
    QVector<wordType> wordInfomation; //定义vector存储单词信息
    QStringList wordList;//获取查询单词的列表，用于自动补全单词
};

#endif // FUNC_TRANSLATEFROMDATABASE_H
