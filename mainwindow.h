#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QToolBar>

#include<vtkSmartPointer.h>


#include"maintreewidget.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    
//toolbar    
private:
    QToolBar *basicGeometriesToolBar;
    QAction *createSphereAction;
    QAction *createCubeAction;
    
    QToolBar *implicitFunctionsToolBar;
    QAction *createPlaneClippingAction;
        
    QToolBar *modelInteractorToolBar;
    QAction *shiftInteractorStyleAction;    
    
    void initToolBar();
    
    enum basicGeometries{G_SPHERE, G_CUBE};
    void createBasicGeometries(basicGeometries);
    
    enum clippingTools{C_NONE, C_PLANE};
    void createClipping(bool, clippingTools);
    clippingTools currentClippingTool;    
    
    void shiftInteractorStyle(bool);
    
private:
    void initView();
    MainTreeWidget *mtw;
    void apply();
    
};
#endif // MAINWINDOW_H
