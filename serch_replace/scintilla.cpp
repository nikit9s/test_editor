#include "scintilla.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QFile>

Scintilla::Scintilla(QWidget *parent):QWidget(parent)
{
}
QWidget* Scintilla::CreateScintilla(QString dir)
{
    QWidget *wid=new QWidget;
    QHBoxLayout *layout_1 = new QHBoxLayout;


    QsciScintilla* textEdit = new QsciScintilla; // инитилизируем редактор
    textEdit->setUtf8(true);
    QsciLexerXML * lexxml = new QsciLexerXML(this);
    textEdit->setLexer(lexxml);



    QFile mFile(dir);
    mFile.open(QIODevice::ReadOnly);
    textEdit->append(mFile.readAll());
    mFile.close();

    layout_1->addWidget(textEdit);
    wid->setLayout(layout_1);


    textEdit->setMargins(4);

    textEdit->setMarginWidth(1, 40);

    textEdit->setMarginLineNumbers(1, true);
    textEdit->SCI_CLEARSELECTIONS;
    TextEdits.append(textEdit);

    return wid;
}

void Scintilla::FillIndRange(QsciScintilla* textEdit, QString word,bool cs,bool wo, int lineFrom)
{
    qDebug()<<lineFrom;

    textEdit->findFirst(word, false,cs,wo,false,true,lineFrom,true,false);
}
