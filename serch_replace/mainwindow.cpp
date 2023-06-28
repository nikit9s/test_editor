#include "mainwindow.h"
#include "scintilla.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scintilla = new Scintilla();
    CreateWidgets();
    CreateMenu();
    SetupWidgets();

    setCentralWidget(WindowWidget);
    connect(FindTreeView, &QTreeView::clicked, this, &MainWindow::TreeVievAddFindItem);
    connect(this,SIGNAL(ReplaceAllTab(QString,QString)),this,SLOT(ReplaceAllTabs(QString,QString)));
}

MainWindow::~MainWindow()
{
}








void MainWindow::onAccept(int LineNumber,QString FileName,QString LineContent, QString sS, int index) //
{
    if(PreviousLineIndex != LineNumber)
    {
        popao.clear();
    }
    popao.append(index);
    PreviousLineIndex = LineNumber;
    QMap <int,  QList <int>> tmp;
    QMap<QString, QMap<int,  QList <int>>> filePath;
    tmp.insert(LineNumber,{popao});
    filePath.insert(FileName,tmp);

        // Пример использования данных

    //начало функцонал добавления всех найденных элементов
    if (!AddFileContainer.contains(FileName)) // Проверяем, содержит ли контейнер AddFileContainer файл с именем FileName
    {
        FindStandartItem = new QStandardItem(FileName); // Создаем новый элемент QStandardItem с именем FileName
        FindStandardItems.append(FindStandartItem); // Добавляем созданный элемент в список FindStandardItems
        QStandardItem* child = new QStandardItem(("Line " +QString::number(LineNumber)+":       " + LineContent)); // Создаем новый элемент QStandardItem с информацией о строке
        child->setData(sS, Qt::UserRole+1);child->setData("Line " +QString::number(LineNumber)+":       " + LineContent,Qt::UserRole);

        FindStandardItems.last()->appendRow(child); // Добавляем созданный элемент как дочерний к последнему элементу списка FindStandardItems
        FindTreeModel->appendRow(FindStandardItems.last()); // Добавляем последний элемент списка FindStandardItems в модель FindTreeModel
    }
    else
    {
        QStandardItem* child = new QStandardItem( ("Line " +QString::number(LineNumber)+":       " + LineContent)); // Создаем новый элемент QStandardItem с информацией о строке
        child->setData("Line " +QString::number(LineNumber)+":       " + LineContent,Qt::UserRole);
        child->setData(sS, Qt::UserRole+1);

        FindStandardItems.last()->appendRow(child); // Добавляем созданный элемент как дочерний к последнему элементу списка FindStandardItems
    }

    AddFileContainer.append(FileName); // Добавляем имя файла в контейнер AddFileContainer

    ; // Устанавливаем модель FindTreeModel для отображения в FindTreeView

    if (sS != FindTreeSearchWord) // Проверяем, изменилось ли значение переменной sS относительно FindTreeSearchWord
    {
        FindTreeSearchWord = sS; // Обновляем значение FindTreeSearchWord
    }

    AddFileContainer.append(FileName);
    FindTreeView->setModel(FindTreeModel);

    //конец функцонал добавления всех найденных элементов

}

void MainWindow::CreateWidgets()
{
    tab = new QTabWidget;
    WindowWidget = new QWidget;
    MainLayout = new QGridLayout(WindowWidget);
    FileSysModel = new QFileSystemModel;
    LeftTreeView = new QTreeView(); // QTreeView для отображения дериктории
    FindTreeView = new QTreeView(); // QTreeView для отображения найденных совпадений в файлах
    FindTreeModel = new QStandardItemModel();
    tab->setTabsClosable(true);
    FindTreeView->setItemDelegate(new HighlightDelegate(FindTreeView));
    FindTreeView->setModel(FindTreeModel);

}

void MainWindow::CreateMenu()
{
    QMenu * OpenMenu = new QMenu("&Открыть");
    QMenu * SearchReplaceMenu = new QMenu("&Поиск/Замена");
    QMenuBar * mainMenu = new QMenuBar;

    OpenMenu->addAction("&OpenFile",this,SLOT(OpenFile()));
    SearchReplaceMenu->addAction("Find/Replace",this,SLOT(FindOrReplaceActionClicked()));
    mainMenu->addMenu(OpenMenu);
    mainMenu->addMenu(SearchReplaceMenu);
    MainLayout->setMenuBar(mainMenu);
}
void MainWindow::SetupWidgets()
{
    LeftTreeView->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
    LeftTreeView->setMaximumSize(400,1200);
    FindTreeView->setMaximumSize(2000,200);
    FindTreeView->setHeaderHidden(true);
    FindTreeView->setIndentation(25);
    FindTreeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    MainLayout->addWidget(LeftTreeView,0,0);
    MainLayout->addWidget(tab,0,1);
    MainLayout->addWidget(FindTreeView,1,1);



}
void MainWindow::OpenFile()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/nikitakireev");

    FileSysModel->setRootPath(path);
    LeftTreeView->setModel(FileSysModel);
    LeftTreeView->setRootIndex(FileSysModel->index(path));
    connect(LeftTreeView, &QTreeView::clicked, this, &MainWindow::onTreeViewClicked);
}


void MainWindow::onTreeViewClicked()
{
    QModelIndexList indexes = LeftTreeView->selectionModel()->selectedIndexes();
    if (indexes.size() > 0)
    {
        QModelIndex selectedIndex = indexes.at(0);
        QString path = FileSysModel->filePath(selectedIndex);
        QFileSystemModel *model_tmp = new QFileSystemModel;
        QFile file(path);

        if(!(model_tmp->isDir(selectedIndex)))
        {
           QString path;
           path = model_tmp->filePath(selectedIndex);
           tab->addTab(scintilla->CreateScintilla(path),path);
        }
        delete model_tmp;
     }
}
void MainWindow::TreeVievAddFindItem()
{
    QModelIndex index = FindTreeView->currentIndex();
    QStandardItem* l_itemClicked = FindTreeModel->itemFromIndex(index);
    if(!l_itemClicked->hasChildren())
    {

    QString path =  l_itemClicked->parent()->text();
    QString new_str;
    int pos = path.lastIndexOf(QChar('/'));

    FileSysModel->setRootPath(path.left(pos));
    LeftTreeView->setModel(FileSysModel);
    LeftTreeView->setRootIndex(FileSysModel->index(path.left(pos)));
    connect(LeftTreeView, &QTreeView::clicked, this, &MainWindow::onTreeViewClicked);

    QString line_number = l_itemClicked->text().split(":")[0];
    bool test;
    int count =  tab->count();
    for(int i=0;i<count;i++)
    {

        QString currentTabText = tab->tabText(i);
        tabname.append(currentTabText);
    }
    test = tabname.indexOf(path) < 0;
    if(test)
    {
        int line_number_index = line_number.split(" ")[1].toInt();
        int tab_count = tab->count();
        tab->addTab(scintilla->CreateScintilla(path),path);
        scintilla->FillIndRange(scintilla->TextEdits[count],FindTreeSearchWord,false,false,line_number_index-1);
        tab->setCurrentIndex(tab_count);

    }
    else
    {
        int counter = 0;
        QString currentTabName;

        while(currentTabName!=path)
        {
            currentTabName = tab->tabText(counter);
            counter+=1;
        }
        int line_number_index = line_number.split(" ")[1].toInt();

        counter = counter - 1;
        scintilla->TextEdits[counter]->clearIndicatorRange(0,0,0,scintilla->TextEdits[counter]->length(),2);
        tab->setCurrentIndex(counter);


        bool IsInLine = l_itemClicked->text().split(":       ")[1].toLower() == scintilla->TextEdits[counter]->text(line_number_index-1).toLower().split("\n")[0].trimmed();;
        if(IsInLine)
        {
            int comPos = scintilla->TextEdits[counter]->text(line_number_index-1).toLower().indexOf(FindTreeSearchWord.toLower());
            int comEndPos = FindTreeSearchWord.count()-1;
            QString subStr = scintilla->TextEdits[counter]->text(line_number_index-1).mid(comPos, comEndPos+1);
            QString subStr1 = scintilla->TextEdits[counter]->text(line_number_index-1);

            scintilla->TextEdits[counter]->findFirst(subStr, false,false,false,false,true,line_number_index-1,true,false);

        }
        else
        {
        scintilla->TextEdits[counter]->setCursorPosition(line_number_index-1,0);
        }
    }
  }
}

void MainWindow::FindOrReplaceActionClicked()
{

    if (!find) {
        find = new FindDialog(this);  // create new window
      }
    connect(find,SIGNAL(accepted(int,QString,QString,QString,int)),this,SLOT(onAccept(int,QString,QString,QString,int)));


    connect(find,SIGNAL(give_find_word(Qt::KeyboardModifiers,QString,bool,bool,bool)),this,SLOT(Find_Next_Word(Qt::KeyboardModifiers,QString,bool,bool,bool)));
    connect(find,SIGNAL(give_replace_word(Qt::KeyboardModifiers,QString,QString,bool,bool)),this,SLOT(Replace_Next_Word(Qt::KeyboardModifiers,QString,QString,bool,bool)));


    connect(find,SIGNAL(ReplaceAllButtonSignal(bool,QString,QString)),this,SLOT(ReplaceDefinition(bool,QString,QString)));

    connect(find,SIGNAL(g_ClearTreeFindView()),this,SLOT(e_ClearTreeFindView()));
    connect(find,SIGNAL(DeleteFindDialog()),
            this,SLOT(DeleteFindDialog()));
    connect(find,SIGNAL(give_FindTreeModel()),this,SLOT(give_FindStandartItemModel()));
    connect(this,SIGNAL(giveTreeModel(QStandardItemModel*)),find,SLOT(get_FindTreeModelItem_tmp(QStandardItemModel*)));
    connect(find,SIGNAL(ShowAllReplaceFile(QString)),this,SLOT(ShowReplaceFile(QString)));



    find->show();

}
void MainWindow::DeleteFindDialog()
{
    find=nullptr;
}
void MainWindow::Find_Next_Word(Qt::KeyboardModifiers,QString Word, bool cs,bool wo,bool forward )
{
    QString searchText = Word; // Получаем введенный текст для поиска

        if (!searchText.isEmpty())
        {
            // Выполняем поиск в объекте QScintilla
            QsciScintilla* currentEditor = scintilla->TextEdits[tab->currentIndex()];
            if (currentEditor)
            {
                // Устанавливаем флаги поиска в зависимости от настроек
                int flags = 0;

                // Выполняем поиск и выделение совпадений
               bool is_next;
               if(!forward)
               {
                    is_next =   currentEditor->findFirst(searchText, false,cs,wo,false,forward,flags);
                    currentEditor->findNext();
               }
              else
               {
                    is_next =   currentEditor->findFirst(searchText, false,cs,wo,false,forward,flags);
                    currentEditor->SendScintilla(QsciScintillaBase::SCI_SETTARGETSTART, currentEditor->SendScintilla(QsciScintillaBase::SCI_GETSELECTIONSTART));
                    currentEditor->SendScintilla(QsciScintillaBase::SCI_SETTARGETEND, currentEditor->SendScintilla(QsciScintillaBase::SCI_GETSELECTIONEND));
                    currentEditor->SendScintilla(QsciScintillaBase::SCI_TARGETFROMSELECTION);
                    currentEditor->SendScintilla(QsciScintillaBase::SCI_SETSEARCHFLAGS, flags);
                    currentEditor->SendScintilla(QsciScintillaBase::SCI_SEARCHINTARGET, searchText.length(), reinterpret_cast<intptr_t>(searchText.toUtf8().constData()));
               }
                qDebug() << is_next;
                if(!is_next && tab->count() > tab->currentIndex())
                {
                    tab->setCurrentIndex(tab->currentIndex()+1);
                }
            }
        }
}




void MainWindow::Replace_Next_Word(Qt::KeyboardModifiers, QString ReplaceWord, QString FindWord,bool wo,bool forward )
{
    QString searchText = FindWord; // Получаем введенный текст для поиска

        if (!searchText.isEmpty())
        {
            QsciScintilla* currentEditor = scintilla->TextEdits[tab->currentIndex()];
            if (currentEditor)
            {
                    currentEditor->SendScintilla(QsciScintillaBase::SCI_BEGINUNDOACTION);
                    currentEditor->SendScintilla(QsciScintillaBase::SCI_REPLACESEL, 0, reinterpret_cast<intptr_t>(ReplaceWord.toUtf8().constData()));
                    currentEditor->SendScintilla(QsciScintillaBase::SCI_ENDUNDOACTION);
            }
       }
}

void MainWindow::ReplaceDefinition(bool Definition,QString ReplaceString,QString SearchString)
{
 if(Definition == true)
 {
     emit ReplaceAllTab(ReplaceString,SearchString);


//     заменяем все найденные по вкладкам
 }
 else
 {
     QThread *thread = new QThread();
     connect(this, SIGNAL(destroyed()), thread, SLOT(quit()));     


//замена всех файлов в одном потокe

 }
}


void MainWindow::ReplaceAllTabs(QString ReplaceWord, QString FindWord)
{

    int count = tab->count();

    int CompleteCount = 0;
    bool IsFindInFile = false;
    while(count > CompleteCount)
    {
        do
        {
        if(scintilla->TextEdits[CompleteCount]->hasSelectedText())
        {
            scintilla->TextEdits[CompleteCount]->replaceSelectedText(ReplaceWord);
        }
        else
        {
            scintilla->TextEdits[CompleteCount]->findFirst(FindWord,false,false,true,false,true,-1,true,false);
            scintilla->TextEdits[CompleteCount]->replaceSelectedText(ReplaceWord);
        }
        bool is_next = scintilla->TextEdits[CompleteCount]->findFirst(FindWord,false,false,true,false,true,-1,true,false);
        IsFindInFile = is_next;
        if(!is_next){
            tab->setCurrentIndex(tab->currentIndex()+1);
        }
        }

        while(IsFindInFile);
        scintilla->TextEdits[CompleteCount]->SendScintilla(QsciScintilla::SCI_SETFIRSTVISIBLELINE,0);
        scintilla->TextEdits[CompleteCount]->SendScintilla(QsciScintilla::SCI_GOTOPOS,0);

        CompleteCount+=1;
    }
}
void MainWindow::ShowReplaceFile(QString path)
{
    if(tab->tabText(tab->count()-1) != path)
    tab->addTab(scintilla->CreateScintilla(path),path);
}

void MainWindow::give_FindStandartItemModel()
{
    emit giveTreeModel(FindTreeModel);
}


void MainWindow::e_ClearTreeFindView()
{
    FindTreeModel->clear();
    FindStandardItems.clear();
    AddFileContainer.clear();
    FindTreeView->setModel(nullptr);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // Проверка на нажатие комбинации клавиш Ctrl+F
    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_F) {
        // Создание и открытие диалогового окна поиска
        FindDialog *findDialog = new FindDialog(this);
        findDialog->show();
    }

    // Вызов базовой реализации функции keyPressEvent
    QMainWindow::keyPressEvent(event);
}

