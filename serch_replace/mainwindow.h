#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <QMainWindow>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerxml.h>
#include <Qsci/qscimacro.h>
#include "find_dialog.h"
#include <QTreeView>
#include <QFileSystemModel>
#include <QLayout>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QProgressBar>
#include <QTime>
#include "scintilla.h"
#include <QKeyEvent>

#include "styledeligate.cpp"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Scintilla *scintilla;
    QList<int> popao;

    QTreeView *QTreeVFindTreeView;
    QTreeView *FindTreeView;
    QStandardItemModel* FindTreeModel;
    QStandardItem * FindStandartItem = nullptr;
    HighlightDelegate highlightDelegate;

    QGridLayout *MainLayout;
    QWidget *WindowWidget;

    QFileSystemModel* FileSysModel;
    QTreeView* LeftTreeView;
    QTabWidget* tab;

    QStringList tabname = {};
    QStringList AddFileContainer = {};
    QList<QStandardItem *> FindStandardItems = {};


    FindDialog *find = nullptr;

    int PreviousLineIndex = 0;
    int PreviousTabIndex = 0;
    QString FindTreeSearchWord;
    QMap <int,  QList <int>> tmp;
    QMap<QString, QMap<int,  QList <int>>> filePath;


    void onTreeViewClicked();
    void SetupWidgets();
    void CreateMenu();
    void CreateWidgets();
    void tree_find_cliked();

    bool FirstEntryInto = false;
    bool SearchDirection = true;

signals:
    void ReplaceAllTab(QString,QString);
    void r_start_operatioin(QString, QString, QString);
    void giveTreeModel(QStandardItemModel*);

private slots:
    void OpenFile();
    void DeleteFindDialog();
    void TreeVievAddFindItem();
    void FindOrReplaceActionClicked();
    void onAccept(int LineNumber,QString FileName,QString LineContent, QString, int);
    void Find_Next_Word(Qt::KeyboardModifiers,QString, bool, bool ,bool);
    void Replace_Next_Word(Qt::KeyboardModifiers, QString, QString, bool, bool);
    void e_ClearTreeFindView();
    void ReplaceDefinition(bool,QString,QString);
    void ReplaceAllTabs(QString, QString);
    void ShowReplaceFile(QString);
    void give_FindStandartItemModel();
protected:
    void keyPressEvent(QKeyEvent *event) override;


};
#endif // MAINWINDOW_H

