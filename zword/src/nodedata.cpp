
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


