#include "Func_TranslateFromDatabase.h"


/*数据库的创建，各属性名
 * CREATE TABLE words(
        [ID] [int] NULL,
        [Word] [nvarchar](100) NULL,        //单词
        [GQS] [nvarchar](100) NULL,         //过去式
        [GQFC] [nvarchar](100) NULL,        //过去分词
        [XZFC] [nvarchar](100) NULL,        //现在分词
        [FS] [nvarchar](100) NULL,          //单词的复数形式
        [meaning] [nvarchar](1000) NULL,    //单词的意思
        [lx] [nvarchar](1000) NULL          //单词的例句解释
);
*/

Func_TranslateFromDatabase::Func_TranslateFromDatabase(QObject *parent) : QObject(parent)
{
    //初始化数据库，在这里使用sqlite，轻量级数据库
    QSqlDatabase wordDb =  QSqlDatabase::addDatabase("QSQLITE", "wordDb");
    //相对路径读取单词的数据库
//    wordDb.setDatabaseName("./resource/word/wordData.db");
//    wordDb.setDatabaseName(":/word/resources/word/wordData.db");
    //用于debug，设置绝对路径，以免相对路径使用不了
    wordDb.setDatabaseName("C:/Users/51153/Documents/Translator/resources/word/wordData.db");
    wordDb.open();
    QSqlQuery query(wordDb);
    //查询语句
    query.exec("SELECT * FROM words;");
    query.first();
    //将数据写入容器
    do {
        wordInfomation.push_back({query.value(0).toInt(),
                                  query.value(1).toString(),
                                  query.value(2).toString(),
                                  query.value(3).toString(),
                                  query.value(4).toString(),
                                  query.value(5).toString(),
                                  query.value(6).toString(),
                                  query.value(7).toString()});
        wordList.push_back(query.value(1).toString());
    } while(query.next());
    wordDb.close();
}

Func_TranslateFromDatabase::~Func_TranslateFromDatabase()
{

}

/*英译中*/
QString Func_TranslateFromDatabase::getReplyFromEN(QString stringInput)
{
    QVector<wordType>::iterator iteratorWord;       //STL风格迭代器
    QString stringResult = "本地词库查询无结果";
    for (iteratorWord = wordInfomation.begin(); iteratorWord != wordInfomation.end(); iteratorWord++) {
        if ((*iteratorWord).word == stringInput) {
            //查询到该单词，则使用html的格式保存为结果返回
            stringResult = "<font size=7>" + (*iteratorWord).word + "</font><br><br>" +
                    (*iteratorWord).meaning + "</b><br><br>";
            //由于不是每个单词都有各种时态形式以及例句 故先判断是否存在 再写入文本
            if((*iteratorWord).gqs != "")
                stringResult += "<font color=#696969>过去式：</font>" + (*iteratorWord).gqs + "&nbsp;&nbsp;&nbsp;";
            if((*iteratorWord).gqfc != "")
                stringResult += "<font color=#696969>过去分词：</font>" + (*iteratorWord).gqfc + "&nbsp;&nbsp;&nbsp;";
            if((*iteratorWord).xzfc != "")
                stringResult +=  "<font color=#696969>现在分词：</font>" +  (*iteratorWord).xzfc + "&nbsp;&nbsp;&nbsp;";
            if((*iteratorWord).fs != "")
                stringResult += "<font color=#696969>复数形式：</font>" + (*iteratorWord).fs;
            if((*iteratorWord).lx != "")
                stringResult +=  "<br><font color=#696969>双语例句：</font>" + (*iteratorWord).lx;
            //替换数据库文本里原本包含的换行符
            stringResult.replace(QString("/r/n"), QString("<br>"));
            break;
        }
    }
    if(stringResult != "本地词库查询无结果") {
        stringResult += "<br><font color=#696969>-该查询结果来源于本地词库</font>";
    }

    return stringResult;
}

/*中译英*/
QString Func_TranslateFromDatabase::getReplyFromCN(QString stringInput)
{
    QVector<wordType>::iterator iteratorWord;
    QString stringResult = "";
    for (iteratorWord = wordInfomation.begin(); iteratorWord != wordInfomation.end(); iteratorWord++) {
        QString stringTemp = (*iteratorWord).meaning;
        //由于数据库中的中文释义难以指定某一个单词 故选择输出所有包含输入中文的英文单词
        if(stringTemp.contains(stringInput, Qt::CaseSensitive)) {
            stringResult += "<font size=7>" + (*iteratorWord).word + "</font><br><b>" +
                         (*iteratorWord).meaning + "</b><br><br>";
            if((*iteratorWord).gqs != "")
                stringResult += "<font color=#696969>过去式：</font>" + (*iteratorWord).gqs + "&nbsp;&nbsp;&nbsp;";
            if((*iteratorWord).gqfc != "")
                stringResult += "<font color=#696969>过去分词：</font>" + (*iteratorWord).gqfc + "&nbsp;&nbsp;&nbsp;";
            if((*iteratorWord).xzfc != "")
                stringResult +=  "<font color=#696969>现在分词：</font>" +  (*iteratorWord).xzfc + "&nbsp;&nbsp;&nbsp;";
            if((*iteratorWord).fs != "")
                stringResult += "<font color=#696969>复数形式：</font>" + (*iteratorWord).fs;
            if((*iteratorWord).lx != "")
                stringResult +=  "<br><font color=#696969>双语例句：</font>" + (*iteratorWord).lx;
            stringResult += "<br><br>";
            stringResult.replace(QString("/r/n"), QString("<br>"));
        }
    }
    if(stringResult == "")
        stringResult = "本地词库查询无结果";
    else
        stringResult += "<br><font color=#696969>-该查询结果来源于本地词库</font>";

    return stringResult;
}

/*获取所有单词的列表 用于自动补全*/
QStringList Func_TranslateFromDatabase::getWordList()
{
    return wordList;
}






