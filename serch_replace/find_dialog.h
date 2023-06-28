#ifndef FIND_DIALOG_H
#define FIND_DIALOG_H

#include <QMainWindow>
#include <QDialog>
#include <QThread>
#include "ui_find_dialog.h"
#include <QMessageBox>
#include <Qsci/qsciscintilla.h>
#include "worker.h"
#include <QStandardItemModel>

class FindDialog : public QDialog, public Ui::Dialog {
    Q_OBJECT

public:
    FindDialog(QWidget* parent = nullptr);
    ~FindDialog();
    virtual void closeEvent(QCloseEvent* event) override;

public slots:
    void getTextEditSlots(int, QString, QString,QString,int);
    void getTextReplaceSlots(QString, QString, bool, bool);
    void ProgressBarUpdate(int, int);

private:
    Worker *searchg_worker = nullptr;
    QStatusBar* bar = nullptr;
    QThread* thread;
    QStandardItemModel *FindTreeModel_tmp = nullptr;
    void InitSearchWorker();
    bool FirstEntryInto = false;
    bool SearchDirection = false;


private slots:
    // Кнопки
    void on_ChanelSearchButton_clicked();

    void on_FindNextButton_clicked();

    void on_FindAllButton_clicked();

    void on_FindButton_clicked();

    void on_ReplaceButton_clicked();

    void on_ReplaceAllButton_clicked();

    void on_ChanelReplaceButton_clicked();

    void get_FindTreeModelItem_tmp(QStandardItemModel*);

    void DeleteThread();
    void ShowReplaceFile(QString);

signals:
    void ReplaceAllButtonSignal(bool,QString,QString);
    void accepted(int, QString, QString ,QString,int);
    void give_find_word(Qt::KeyboardModifiers, QString, bool, bool, bool);
    void give_replace_word(Qt::KeyboardModifiers, QString, QString, bool, bool);
    void s_start_operatioin(QString, QString,bool,bool);
    void r_start_operatioin(QString, QString, QString,bool,bool);
    void give_replace_words(Qt::KeyboardModifiers, QString, QString, bool, bool);
    void GiveBreakThreadVar(bool);
    void g_ClearTreeFindView();
    void DeleteFindDialog();
    void give_FindTreeModel();
    void ShowAllReplaceFile(QString);

};

#endif // FIND_DIALOG_H
