#include "worker.h"
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QRegularExpression>
Worker::Worker(QObject *parent) : QObject(parent)
{
//     connect(this,SLOT(UpdateReplaceProgressBar(int)),this,SIGNAL(UpdateReplaceProgressBar(int)));
}


void Worker::GetBreakThreadVar(bool p_BreakThreadVar)
{
    // Установка флага прерывания потока
    g_BreakThreadVar = p_BreakThreadVar;

}


void Worker::replace_similarities(QString dir, QString sS, QString replaceText , bool cs,bool wo)
{
    qDebug() << dir;

    // Получение строки поиска
    QString searchString = sS;

    // Получение директории
    QDir directory(dir);

    // Получение списка файлов
    QStringList txt = directory.entryList(QStringList() << "*.xml" << "*.XML", QDir::Files);

    // Переменная для текущей проверяемой строки
    QString line;

    // Счетчик проверенных файлов
    QString filename = QDir::currentPath() + "/tmp/" + QFileInfo(dir).baseName() + "_tmp." + QFileInfo(dir).suffix();

    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "File error";
    }

    QFile data(dir);
    if (!data.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error - file cannot be opened";
    }

    QTextStream in(&data);
    QTextStream stream(&file);

    in.setCodec("UTF-8");
    stream.setCodec("UTF-8");

    // Проверка флага прерывания потока и остановка поиска при необходимости
    do
    {
        line = in.readLine();

        if (line.toLower().contains(searchString.toLower()))
        {
        qDebug() << "wo" << wo << "cs" << cs;

            // Проверка, чтобы замена выполнялась только если слова идентичны
            if( wo &&cs)
            {
                QString wordBoundaryRegex = "\\b" + QRegularExpression::escape(searchString) + "\\b";
                QRegularExpression regex(wordBoundaryRegex);

                if(regex.match(line).hasMatch())
                {
                    line.replace(searchString, replaceText);
                }
            }
            if(wo)
            {
                QString wordBoundaryRegex = "\\b" + QRegularExpression::escape(searchString.toLower()) + "\\b";
                QRegularExpression regex(wordBoundaryRegex);

                if(regex.match(line.toLower()).hasMatch())
                {
                    line.replace(searchString, replaceText,Qt::CaseInsensitive);
                }
            }
            if(cs)
            {
                    // Замена слова с учетом регистра
                    line.replace(searchString, replaceText, Qt::CaseSensitive);
            }
            if(!cs && !wo)
            {
                line.replace(searchString, replaceText, Qt::CaseInsensitive);

            }

        }

        if (g_BreakThreadVar == true)
        {
            break;
        }

        stream << line << "\n";
    } while (!line.isNull() && g_BreakThreadVar == false);
    file.close();
    // Выполнение задержки для сброса нагрузки на процессор
    QThread::msleep(100);

    // Обновление progress bar
    emit GiveReplaceFile(filename);

    file.close();
}

void Worker::searech_similarities(QString dir, QString sS,bool Re, bool Cw)
{
    // Получение строки поиска

    // Получение директории
    QDir directory = dir;

    // Получение списка файлов
    QStringList txt = directory.entryList(QStringList() << "*.xml" << "*.XML", QDir::Files);

    // Переменная для текущей проверяемой строки
    QString line;

    // Счетчик проверенных файлов
    int file_count = 0;
     QString searchString = sS;
    // Цикл поиска
    while(txt.count() > file_count)
    {
        // Формирование полного пути к файлу
        QString filePath = directory.absoluteFilePath(txt[file_count]);

        // Инициализация файла и потока чтения
        QFile data(filePath);
        QTextStream in(&data);
        in.setCodec("UTF-8");
        if(!data.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "error - file cannot be opened";
        }

        int counter = 0;

        // Цикл проверки строк файла на совпадение
        do
        {

            line = in.readLine();
            counter += 1;
            if(Re)
            {
                if(Cw)
                {
                    if (line.contains(searchString, Qt::CaseSensitive))
                    {
                        // Отправка результата поиска
                        QString find_text;

                        find_text = QString("\\b%1\\b").arg(searchString);
                        QRegExp reg_find_text(find_text);
                        int count_find = line.count(reg_find_text);
                        if(count_find)
                        {
//                            emit giveTextEditData(counter, data.fileName(), line.trimmed(), searchString);
                        }
                        QThread::msleep(1);
                    }
                }
                else
                {
                    if (line.contains(searchString, Qt::CaseSensitive))
                    {
                        // Отправка результата поиска

//                        emit giveTextEditData(counter, data.fileName(), line.trimmed(), searchString);
                        QThread::msleep(1);
                    }
                }
            }
            else
            {
                    if(Cw)
                    {
                        if (line.toLower().contains(searchString.toLower(), Qt::CaseSensitive))
                        {
                            // Отправка результата поиска
                             QRegularExpression regex(QString("\\b%1\\b").arg(searchString));
                             QRegularExpressionMatch match = regex.match(line.toLower());

                             bool count_find = match.hasMatch();
                            if(count_find)
                            {
//                                emit giveTextEditData(counter, data.fileName(), line.trimmed(), searchString);
                            }

                            QThread::msleep(1);
                        }
                    }
                    else
                    {

                        if (line.toLower().contains(searchString.toLower(), Qt::CaseSensitive))
                        {
                            // Отправка результата поиска
                            int searchIndex = line.indexOf(searchString, 0, Qt::CaseInsensitive);

                            QList<int> occurrenceIndexes;
                            while (searchIndex >= 0)
                            {
                                occurrenceIndexes.append(searchIndex);
                                emit giveTextEditData(counter, data.fileName(), line.trimmed(), searchString, searchIndex);

                                searchIndex = line.indexOf(searchString, searchIndex + 1, Qt::CaseInsensitive);

                            }
                            QThread::msleep(1);
                        }
                    }
                }
            if(g_BreakThreadVar == true)
            {
                break;
            }
            }


        while (!line.isNull() && g_BreakThreadVar==false);

        // Проверка флага прерывания потока и остановка поиска при необходимости

        if(g_BreakThreadVar == true)
        {
            break;

        }
        // Выполнение задержки для сброса нагрузки на процессор
        QThread::msleep(100);

        // Увеличение счетчика проверенных файлов
        file_count += 1;

        // Обновление progress bar
        emit GiveProgressBar(txt.count(), file_count);
    }

}


