#include "searchIterator.h"
#include <sstream>

SearchIterator::SearchIterator(){
    next = nullptr;
    text_pos=0;
    pattern_pos=-1;
    text_len=0;
    pattern_len=0;
    hit=0;
    pattern=QString();
    text=nullptr;
    cursor = QTextCursor();
}

SearchIterator::SearchIterator(QString& search, QTextDocument* doc, int pos){
    pattern = search;
    text = new QString(doc->toPlainText());
    text_len = text->length();
    pattern_len = pattern.length();
    next = new int[pattern_len];
    GetKMPNext();
    text_pos = pos-1;
    pattern_pos = -1;
    hit=0;
    cursor = QTextCursor(doc);
    cursor.setPosition(pos);
}

void SearchIterator::Init(){
    text_pos=-1;
    pattern_pos=-1;
    hit=0;
    cursor.setPosition(0);
}

SearchIterator::~SearchIterator(){
    delete[] next;
    // delete text;
}

bool SearchIterator::operator++(){
    for(; text_pos+1<text_len; text_pos++){
        while(pattern_pos>=0 && (*text)[text_pos+1]!=pattern[pattern_pos+1]) pattern_pos = next[pattern_pos];
        if((*text)[text_pos+1]==pattern[pattern_pos+1])pattern_pos++;
        if(pattern_pos==pattern_len-1){
            qDebug()<<"st_pos "<<GetPos();
            qDebug()<<"ed_pos "<<text_pos+1;
            cursor.setPosition(GetPos());
            cursor.setPosition(text_pos+2, QTextCursor::KeepAnchor);
            text_pos++;
            pattern_pos = next[pattern_pos];
            hit=1;
            return true;
        }
    }
    return false;
}

SearchIterator& SearchIterator::operator=(const SearchIterator& other){
    if(this==&other) return *this;
    delete[] next;
    pattern = other.pattern;
    text = other.text;
    text_len = other.text_len;
    pattern_len = other.pattern_len;
    next = new int[pattern_len];
    for(int i=0; i<pattern_len; i++) next[i] = other.next[i];
    text_pos = other.text_pos;
    pattern_pos = other.pattern_pos;
    cursor = other.cursor;
    return *this;
}

QTextCursor SearchIterator::operator*(){
    return cursor;
}

bool SearchIterator::operator==(const SearchIterator& other){
    return text_pos==other.text_pos;
}

bool SearchIterator::operator!=(const SearchIterator& other){
    return !(*this==other);
}

bool SearchIterator::operator==(const QString& other){
    return pattern==other;
}

bool SearchIterator::operator!=(const QString& other){
    return !(*this==other);
}

void SearchIterator::GetKMPNext(){
    next[0]=-1;
    for(int i=0, j=-1; i<pattern_len-1; i++){
        while(j>=0 && pattern[i+1]!=pattern[j+1]) j = next[j];
        if(pattern[i+1]==pattern[j+1])j++;
        next[i+1] = j;
    }
    // std::ostringstream oss;
    // for(int i=0;i<pattern_len;i++) oss<<next[i];
    // qDebug()<<oss.str().c_str();
}

bool SearchIterator::IsEnd(){
    return text_pos>=text_len-1;
}

bool SearchIterator::IsHit(){
    return hit;
}

int SearchIterator::GetPos(){
    return text_pos-pattern_len+2;
}

QString *SearchIterator::GetText(){
    return text;
}