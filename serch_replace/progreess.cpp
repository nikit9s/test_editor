#include "progreess.h"
#include <QtWidgets>
ProgressBar::ProgressBar(QWidget *parent)
    : QWidget(parent)
{
    mProgressBar = new QProgressBar();
    QHBoxLayout* hLayout = new QHBoxLayout;
    mProgressBar->setMinimumWidth(200);
    mProgressBar->setAlignment(Qt::AlignCenter);
    hLayout->addWidget(mProgressBar);
    setLayout(hLayout);
    setValue();
}
void ProgressBar::setValue()
{
    mProgressBar->show();

}
