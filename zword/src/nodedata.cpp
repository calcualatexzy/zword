
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

vector<QString> NodeData::vcontent()
{
    return z_content;
}


