#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QProgressBar>
#include <QWidget>

class ProgressBar : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressBar(QWidget *parent = nullptr);
    QProgressBar* mProgressBar;
    void get_data(int,int);
    void setValue();

private:

    int m_nStep;
};

#endif // PROGRESSBAR_H
