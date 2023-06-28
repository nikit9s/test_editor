#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QTreeView>

class HighlightDelegate : public QStyledItemDelegate
{
private:
    mutable QString previousLine;

public:
    explicit HighlightDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QString text = index.data(Qt::UserRole).toString();
        QString searchText = index.data(Qt::UserRole + 1).toString();

        if (!searchText.isEmpty())
        {
            // Получаем список всех вхождений подстроки в строке
            QList<int> searchIndexes;
            int searchIndex = text.indexOf(searchText, 0, Qt::CaseInsensitive);
            while (searchIndex >= 0)
            {
                searchIndexes.append(searchIndex);
                searchIndex = text.indexOf(searchText, searchIndex + 1, Qt::CaseInsensitive);
            }

            // Определяем индекс текущего элемента
            int itemIndex = index.row();

            // Вычисляем индекс текущего выделенного вхождения подстроки
            int currentSearchIndex = itemIndex % searchIndexes.count();

            if (currentSearchIndex >= 0 && currentSearchIndex < searchIndexes.count())
            {
                // Получаем индексы начала и конца текущего вхождения
                int startIndex = searchIndexes.at(currentSearchIndex);
                int endIndex = startIndex + searchText.length();

                // Определяем прямоугольник для подсветки
                QRect highlightRect = option.rect;
                highlightRect.setLeft(option.rect.left() + option.fontMetrics.horizontalAdvance(text.left(startIndex)));
                highlightRect.setWidth(option.fontMetrics.horizontalAdvance(text.mid(startIndex, endIndex - startIndex)));

                // Рисуем подсветку
                painter->save();
                painter->setRenderHint(QPainter::Antialiasing);
                painter->setPen(Qt::NoPen);
                painter->setBrush(Qt::yellow);
                painter->drawRect(highlightRect);
                painter->restore();
            }
        }
        else
        {
            // Если searchText пустой, отрисовываем текст без подсветки
            QStyledItemDelegate::paint(painter, option, index);
        }
    }

};
