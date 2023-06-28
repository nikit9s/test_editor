#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QThread>

class Worker : public QObject {
    Q_OBJECT

public:
    explicit Worker(QObject* parent = nullptr);
    bool g_BreakThreadVar = false;

public slots:
    void searech_similarities(QString, QString, bool, bool);
    void replace_similarities(QString, QString, QString,bool,bool);
    void GetBreakThreadVar(bool);

signals:
    void giveTextEditData(int, QString, QString,QString,int);
    void GiveProgressBar(int, int);
    void GiveReplaceCommandStrart(QString, QString, bool, bool);
    void GiveReplaceFile(QString);
    void GiveProgressUpdateReplace(int,int);







private:
};
#endif // WORKER_H
