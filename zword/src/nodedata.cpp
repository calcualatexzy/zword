
#include "nodedata.h"

QString NodeData::content() const{
    QString str;
    for(auto elem : z_content){
        str += elem;
        str += QString::fromStdString("\n");
    }
    return str;
}

void NodeData::setContent(const QString &content)
{
    std::istringstream iss(content.toStdString());
    std::string str;
    int cntline = 0;
    int size = z_content.size();
    while(std::getline(iss, str)){
        if(cntline < size){
            if(z_content[cntline].toStdString() == str){
                cntline++;
                continue;
            }
            else z_content[cntline] = QString::fromStdString(str);
        }
        z_content.push_back(QString::fromStdString(str));
        cntline++;
    }
}

QString NodeData::primate() const{
    return z_primate;
}

void NodeData::setPrimate(const QString &primate)
{
    z_primate = primate;
}

void NodeData::PrimateToContent()
{
    z_content.clear();
    int index = 0;
    bool isBold = false;
    pair<int, QString> pairBold;
    QString strBold;

    bool isItalic = false;
    pair<int, QString> pairItalic;
    QString strItalic;

    int isStyle = 0;
    QString styleStr;

    QString content;
    for(auto elem : z_primate){
        if(elem == '`' && !isStyle){
            isStyle++;
            continue;
        }
        if(isStyle == 1){
            if(elem == '`'){
                setStyle(styleStr);
                isStyle++;
                continue;
            }
            styleStr += elem;
            continue;
        }

        if(elem == '#' && !isBold){
            isBold = true;
            pairBold.first = index;
        }
        else if(elem == '#' && isBold){
            isBold = false;
            pairBold.second = strBold;
            z_bold.push_back(pairBold);
            strBold.clear();
        }
        if(elem != '#' && isBold) strBold += elem;

        if(elem == '~' && !isItalic){
            isItalic = true;
            pairItalic.first = index;
        }
        else if(elem == '~' && isItalic){
            isItalic = false;
            pairItalic.second = strItalic;
            z_italic.push_back(pairItalic);
            strItalic.clear();
        }
        if(elem != '~' && isItalic) strItalic += elem;

        if(elem != '#' && elem != '~'){
            index++;
            content += elem;
        }
    }
    setContent(content);
}

void NodeData::TextEditToPrimate(CustomDocument *textEdit)
{
    z_primate.clear();
    z_bold.clear();
    z_italic.clear();
    z_primate += '`';
    for(auto elem : z_styleMap){
        z_primate += elem.first + "," + elem.second + "/";
    }
    z_primate += '`';
    QTextCursor cursor = textEdit->textCursor();
    cursor.setCharFormat(textEdit->currentCharFormat());
    cursor.movePosition(QTextCursor::Start);
    bool isBold = false;
    bool isItalic = false;
    do{
        textEdit->setTextCursor(cursor);
        if(textEdit->currentCharFormat().fontWeight() == QFont::Bold){
            if(!isBold){
                isBold = true;
                cursor.movePosition(QTextCursor::Left);
                textEdit->setTextCursor(cursor);
                textEdit->insertPlainText("#");
                cursor.movePosition(QTextCursor::Right);
                textEdit->setTextCursor(cursor);
            }
        }
        if(textEdit->currentCharFormat().fontWeight() != QFont::Bold && isBold){
            cursor.movePosition(QTextCursor::Left);
            textEdit->setTextCursor(cursor);
            textEdit->insertPlainText("#");
            cursor.movePosition(QTextCursor::Right);
            textEdit->setTextCursor(cursor);
            isBold = false;
        }

        if(textEdit->currentCharFormat().fontItalic() == true){
            if(!isItalic){
                isItalic = true;
                cursor.movePosition(QTextCursor::Left);
                textEdit->setTextCursor(cursor);
                textEdit->insertPlainText("~");
                cursor.movePosition(QTextCursor::Right);
                textEdit->setTextCursor(cursor);
            }
        }
        if(!textEdit->currentCharFormat().fontItalic() && isItalic){
            cursor.movePosition(QTextCursor::Left);
            textEdit->setTextCursor(cursor);
            textEdit->insertPlainText("~");
            cursor.movePosition(QTextCursor::Right);
            textEdit->setTextCursor(cursor);
            isItalic = false;
        }
    }while(cursor.movePosition(QTextCursor::Right));
    z_primate += textEdit->toPlainText();
    textEdit->selectAll();
    textEdit->setFontWeight(QFont::Normal);
    textEdit->setFontItalic(false);
}

QString NodeData::filename() const{
    return z_filename;
}

void NodeData::setFilename(const QString &filename)
{
    z_filename = filename;
}

int NodeData::listrow() const
{
    return z_listrow;
}

void NodeData::setListrow(const int& row)
{
    z_listrow = row;
}

std::pair<int, int> NodeData::IndexToCoor(int index)
{
    int indexCnt = 0;
    int rowCnt = 0;
    std::pair<int, int> coor;
    for(auto elem : z_content){
        if(indexCnt + elem.length() > index){
            coor.first = rowCnt;
            coor.second = index - indexCnt;
            return coor;
        }
        indexCnt += elem.length() + 1;
        rowCnt++;
    }
    coor.first = rowCnt;
    coor.second = index - indexCnt;
    return coor;
}

QString NodeData::rowContent(int row)
{
    return z_content[row];
}

void NodeData::setRowContent(int row, const QString &content)
{
    if(row >= z_content.size()){
        z_content.push_back(content);
        return;
    }
    z_content[row] = content;
}

vector<QString> NodeData::vcontent()
{
    return z_content;
}

const vector<pair<int, QString> > &NodeData::getBold()
{
    return z_bold;
}

const vector<pair<int, QString> > &NodeData::getItalic()
{
    return z_italic;
}

void NodeData::resetFormat()
{
    z_italic.clear();
    z_bold.clear();
    z_primate = content();
}

void NodeData::setStyle(QString styleStr)
{
    std::string line = styleStr.toStdString();
    std::istringstream iss(line);
    std::string key, value;
    while(std::getline(iss, key, ',')){
        std::getline(iss, value, '/');
        z_styleMap[key] = value;
    }
}

void NodeData::setStyle_Key(std::string key, std::string value)
{
    z_styleMap[key] = value;
}

std::string NodeData::getStyle(std::string key)
{
    qDebug() << key << z_styleMap[key];
    return z_styleMap[key];
}


