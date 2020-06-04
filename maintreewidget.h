#ifndef MAINTREEWIDGET_H
#define MAINTREEWIDGET_H

#include<QTreeWidget>


class MainTreeWidget: public QTreeWidget
{
public:
    explicit MainTreeWidget(QWidget *parent = nullptr);
    ~MainTreeWidget();
    
    
};

#endif // MAINTREEWIDGET_H
