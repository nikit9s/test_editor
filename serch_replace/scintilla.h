    #ifndef SCINTILLA_H
    #define SCINTILLA_H

    #include <QObject>
    #include <QWidget>
    #include <Qsci/qsciscintilla.h>
    #include <Qsci/qscilexerxml.h>


    class Scintilla: public QWidget
    {
        Q_OBJECT

    public:
        QWidget* CreateScintilla(QString dir);
        Scintilla(QWidget *parent=0);
        QVector<QsciScintilla*> TextEdits;


        void FillIndRange(QsciScintilla* textEdit, QString word,bool cs,bool wo, int lineFrom);



    };

    #endif // SCINTILLA_H
