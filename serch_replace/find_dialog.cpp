#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include "progreess.h"
#include <QCloseEvent>
#include <QTextCodec>
#include "ui_find_dialog.h"
#include "find_dialog.h"

FindDialog::FindDialog(QWidget *parent) : QDialog(parent)
{
    // Установка UI
    setupUi(this);
    setWindowFlags(windowFlags() & (~Qt::WindowContextHelpButtonHint));
    setFixedSize(289, 180);
    setAttribute(Qt::WA_DeleteOnClose);

    // Инициализация progress bar
    progressBar->hide();
    progressBar->setStyleSheet("QprogressBarWork:horizontal {border: 1px solid gray; border-radius: 10px; background: white; padding: 1px;} QprogressBarWork::chunk:horizontal {background: qlineargradient(x1: 0, y1: 0.5, x2: 1, y2: 0.5, stop: 0 green, stop: 1 lightgreen); border-radius: 10px;}");

}

void FindDialog::getTextEditSlots(int counter, QString data, QString line,QString sS,int index)
{
    // Отправление данных родительскому окну
    emit accepted(counter, data, line, sS , index);
}

void FindDialog::getTextReplaceSlots(QString replaceText, QString sS, bool oi, bool io)
{
    // Отправление данных родительскому окну
    emit give_replace_word(Qt::KeyboardModifiers(), replaceText, sS, oi, io);
}

void FindDialog::ProgressBarUpdate(int all_file, int count)
{
    progressBar->setMaximum(all_file);
    progressBar->setValue(count);

    if(progressBar->value() == all_file)
    {
        progressBar->hide();
        ReplaceAllButton->setEnabled(true);
        FindAllButton->setEnabled(true);
        DeleteThread();


    }
}



FindDialog::~FindDialog()
{
    emit DeleteFindDialog();

}


void FindDialog::closeEvent(QCloseEvent *e)
{
    // Запрос подтверждения закрытия окна
    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Поиск/Вставка",
                                        tr("Вы хотите закрыть окно?\n"),
                                        QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                        QMessageBox::Yes);


    if (resBtn != QMessageBox::Yes)
    {
       e->ignore();
    }
    else
    {
         // optional, if you want to wait for the thread to finish before continuing
        if(searchg_worker != nullptr && thread != nullptr)
        {
             DeleteThread();

//            delete searchg_worker; // make sure to delete the worker object after the thread has finished
        }
        progressBar->hide();
        progressBar->setValue(0);
        FindAllButton->setEnabled(true);
        ReplaceAllButton->setEnabled(true);
        this->~FindDialog();

    }
}

void FindDialog::on_ChanelSearchButton_clicked()
{
    if(searchg_worker != nullptr && thread != nullptr)
    {
        DeleteThread();
    }
    progressBar->hide();
    progressBar->setValue(0);
    FindAllButton->setEnabled(true);
    ReplaceAllButton->setEnabled(true);


}


void FindDialog::on_FindNextButton_clicked()
{
    bool forwardState;

    if(radioButton_2->isChecked())
    {
        forwardState = true;
    }
    else
    {
        forwardState = false;
    }

    // Отправка сигнала родительскому окну о начале поиска
    emit give_find_word(Qt::KeyboardModifier(), lineEdit->text(), CaseCheckBox->checkState(), WordCheckBox->checkState(), forwardState);
}

void FindDialog::InitSearchWorker()
{
    searchg_worker = new Worker();

    connect(searchg_worker, SIGNAL(giveTextEditData(int,QString,QString,QString,int)),
            this, SLOT(getTextEditSlots(int,QString,QString,QString,int)));
    connect(searchg_worker, SIGNAL(GiveProgressBar(int,int)),
            this, SLOT(ProgressBarUpdate(int,int)));
    connect(searchg_worker, SIGNAL(GiveReplaceCommandStrart(QString,QString,bool,bool)),
            this, SLOT(getTextReplaceSlots(QString,QString,bool,bool)));
    connect(this, SIGNAL(s_start_operatioin(QString,QString,bool,bool)),
            searchg_worker, SLOT(searech_similarities(QString,QString,bool,bool)));
    connect(this, SIGNAL(r_start_operatioin(QString,QString,QString,bool,bool)),
            searchg_worker, SLOT(replace_similarities(QString,QString,QString,bool,bool)));
    connect(this, SIGNAL(GiveBreakThreadVar(bool)),
            searchg_worker, SLOT(GetBreakThreadVar(bool)));
}

void FindDialog::DeleteThread()
{
    if(searchg_worker != nullptr && thread != nullptr)
    {
        searchg_worker->g_BreakThreadVar = true;

        thread->quit();
        thread->wait();
        delete thread;

        delete searchg_worker;
        searchg_worker = nullptr;
        thread = nullptr;

        ChanelSearchButton->setEnabled(false);// make sure to delete the worker object after the thread has finished
    }
    progressBar->hide();
    progressBar->setValue(0);
    FindAllButton->setEnabled(true);
    ReplaceAllButton->setEnabled(true);
}

void FindDialog::ShowReplaceFile(QString file)
{
    emit ShowAllReplaceFile(file);
}

void FindDialog::on_FindAllButton_clicked()
{
    QString searchString = lineEdit->text();

    //potok cyda
    if(searchString!="")
    {
        InitSearchWorker();
        thread = new QThread();
        searchg_worker->moveToThread(thread);
        thread->start();
        // Показ progress bar
        progressBar->show();

        // Очистка отображения результатов поиска

        emit g_ClearTreeFindView();

        // Выбор директории
        QString directory = QFileDialog::getExistingDirectory(this, tr("Select directory"));


        // Запуск функции поиска
        emit s_start_operatioin(directory, searchString, CaseCheckBox->isChecked(),WordCheckBox->isChecked());
        ReplaceAllButton->setEnabled(false);
        FindAllButton->setEnabled(false);
        ChanelSearchButton->setEnabled(true);
    }
}


void FindDialog::on_FindButton_clicked()
{
    bool forwardState;

    if(radioButton_2->isChecked())
    {
        forwardState = true;
    }
    else
    {
        forwardState = false;
    }

    // Отправка сигнала родительскому окну о начале поиска
    emit give_find_word(Qt::KeyboardModifier(), lineEdit_4->text(), checkBox_4->checkState(), checkBox_5->checkState(), forwardState);

}
void FindDialog::on_ReplaceButton_clicked()
{
    bool forwardState;
    if(radioButton->isChecked())
    {
        forwardState = true;
    }
    else
        forwardState = false;

    emit give_replace_word(Qt::KeyboardModifier(),replaceLine->text(),lineEdit_4->text(),WordCheckBox->checkState(),forwardState);
}


void FindDialog::on_ReplaceAllButton_clicked()
{
    QString folderPath = QDir::currentPath() + "/tmp/" ; // Укажите путь к папке, из которой нужно удалить файлы

        QDir directory(folderPath);

        // Проверяем, что папка существует
        if (!directory.exists())
        {
            qDebug() << "Папка не существует!";
        }

        // Получаем список файлов в папке
        QStringList files = directory.entryList(QDir::Files);

        // Удаляем каждый файл из списка
        foreach (QString file, files)
        {
            if (directory.remove(file))
            {
                qDebug() << "Файл удален: " << file;
            }
            else
            {
                qDebug() << "Ошибка при удалении файла: " << file;
            }
        }

    InitSearchWorker();
    thread = new QThread();

    searchg_worker->moveToThread(thread);
    thread->start();
    bool FileOrTabs;

    if(radioButton_5->isChecked())
    {
        FileOrTabs = true;

    }
    else{
        emit give_FindTreeModel();
        FileOrTabs = false;
        thread->start();
        connect(this, SIGNAL(r_start_operatioin(QString,QString,QString,bool,bool)), searchg_worker, SLOT(replace_similarities(QString,QString,QString,bool,bool)));
        connect(searchg_worker,SIGNAL(GiveReplaceFile(QString)),this,SLOT(ShowReplaceFile(QString)));
        int FindFileTitle = FindTreeModel_tmp->rowCount();


        for(int i = 0; i < FindFileTitle;i++)
        {
                  QStandardItem* l_itemClicked = FindTreeModel_tmp->item(i);
                  QString path =  l_itemClicked->text();
                  emit  r_start_operatioin(path,lineEdit_4->text(),replaceLine->text(),checkBox_4->checkState(), checkBox_5->checkState());
                  if(searchg_worker->g_BreakThreadVar==true)
                  {
                      DeleteThread();
                      break;

                  }
                  if(i == FindFileTitle)
                  {
                      DeleteThread();
                  }


        }
    }
    emit ReplaceAllButtonSignal(FileOrTabs,replaceLine->text(),lineEdit_4->text()); //  true - по вкладкам, false - по файлам lineEdit_4 - на что заменить, lineEDit_3 - что заменить
}
void FindDialog::get_FindTreeModelItem_tmp(QStandardItemModel* model)
{
    FindTreeModel_tmp = model;
}
void FindDialog::on_ChanelReplaceButton_clicked()
{


    if(searchg_worker != nullptr && thread != nullptr)
    {
        DeleteThread();
    }
    progressBar->hide();
    progressBar->setValue(0);
    FindAllButton->setEnabled(true);
    ReplaceAllButton->setEnabled(true);
}
