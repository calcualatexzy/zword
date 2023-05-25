
#include "nodedata.h"

NodeData::NodeData()
{

}

QString NodeData::content() const{
    return z_content;
}

void NodeData::setContent(const QString &content)
{
    z_content = content;
}

