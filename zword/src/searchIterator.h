#ifndef SEARCHITERATOR_H
#define SEARCHITERATOR_H

#include <QDebug>
#include <qtextcursor.h>


class SearchIterator{
public:
    SearchIterator();

    SearchIterator(QString& search, QTextDocument* doc, int pos);

    void Init();

    ~SearchIterator();

    SearchIterator&operator=(const SearchIterator& other);

    bool operator++();

    QTextCursor operator*();

    bool operator==(const SearchIterator& other);

    bool operator!=(const SearchIterator& other);

    bool operator==(const QString& other);

    bool operator!=(const QString& other);

    int GetPos();

    bool IsEnd();

    bool IsHit();

    QString *GetText();

private:
    void GetKMPNext();

    bool hit;
    int* next;
    int text_pos, pattern_pos;
    int text_len, pattern_len;
    QTextCursor cursor;
    QString pattern;
    QString *text;
};


#endif // SEARCHITERATOR_H