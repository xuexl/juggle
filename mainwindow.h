#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QToolBar>

#include<memory>

#include<vtkSmartPointer.h>

#include"maintreewidget.h"
#include"vtkjugglerenderer.h"
#include"JuggleLoader.h"


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
    
    void createBasicGeometries(JuggleLoader::BasicGeometries ge);
        
    void createClipping(bool);     
    
    void shiftInteractorStyle(bool);
    
private:
    void initView();
    MainTreeWidget *mtw;
    void apply();
    
    vtkSmartPointer<vtkJuggleRenderer> Renderer;
    JuggleOptionsParser Parser;
    std::unique_ptr<JuggleLoader> loader;
    
private:
    MainWindow(MainWindow const&) = delete;
    void operator=(MainWindow const&) = delete;
    
};
#endif // MAINWINDOW_H
