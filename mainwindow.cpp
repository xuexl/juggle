#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkPolyDataMapper.h>
#include<vtkActor.h>

#include <vtkNew.h>
#include <vtkNamedColors.h>

#include<vtkSphereSource.h>
#include<vtkCubeSource.h>
#include<vtkRendererCollection.h>
#include<vtkInteractorStyleTrackballActor.h>
#include<vtkInteractorStyleTrackballCamera.h>

#include <vtkPlane.h>

#include <vtkCommand.h>
#include <vtkImplicitPlaneWidget2.h>
#include <vtkImplicitPlaneRepresentation.h>
#include <vtkClipPolyData.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    initToolBar();
    
    initView();
    initPipelineBrower();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initToolBar()
{    
    //
    basicGeometriesToolBar = addToolBar(tr(u8"基本几何体"));
    
    createSphereAction = new QAction(QIcon("://images/toolbar/sphere.png"), tr(u8"创建球体"), this);
    connect(createSphereAction, &QAction::triggered, [this](){ createBasicGeometries(G_SPHERE); });
    basicGeometriesToolBar->addAction(createSphereAction);
    
    createCubeAction = new QAction(QIcon("://images/toolbar/cube.png"), tr(u8"创建立方体"), this);
    connect(createCubeAction, &QAction::triggered, [this](){ createBasicGeometries(G_CUBE); });        
    basicGeometriesToolBar->addAction(createCubeAction);
    
    //
    implicitFunctionsToolBar = addToolBar(tr(u8"切割工具"));
    
    createPlaneClippingAction = new QAction(QIcon("://images/toolbar/rect.png"), tr(u8"平面切割"), this);
    connect(createPlaneClippingAction, &QAction::triggered, [this](){ createClipping(C_PLANE); });
    implicitFunctionsToolBar->addAction(createPlaneClippingAction);
    
    //
    modelInteractorToolBar = addToolBar(tr(u8"模型交互"));
    
    shiftInteractorStyleAction = new QAction(QIcon("://images/toolbar/shift.png"), tr(u8"切换交互方式"), this);
    connect(shiftInteractorStyleAction, &QAction::triggered, [this](bool check){ shiftInteractorStyle(check); });
    modelInteractorToolBar->addAction(shiftInteractorStyleAction);
    shiftInteractorStyleAction->setCheckable(true);
    
}

void MainWindow::initView()
{
    vtkNew<vtkNamedColors> colors;
    
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    ui->wt_MainView->setRenderWindow(renderWindow);    
    
    vtkNew<vtkRenderer> renderer; 
    renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
    renderWindow->AddRenderer(renderer);

}

void MainWindow::createBasicGeometries(basicGeometries ge)
{
    auto renderFN = [this](vtkAlgorithmOutput* input){        
        vtkNew<vtkPolyDataMapper> mapper;
        mapper->SetInputConnection(input);
 
        vtkNew<vtkActor> actor;
        actor->SetMapper(mapper);
       
        ui->wt_MainView->renderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actor);
        ui->wt_MainView->renderWindow()->GetRenderers()->GetFirstRenderer()->ResetCamera();        
        ui->wt_MainView->renderWindow()->Render();               
    };
    
    switch (ge) 
    {
        case G_SPHERE:
        {
            vtkNew<vtkSphereSource> sphere;
            sphere->SetPhiResolution(30);
            sphere->SetThetaResolution(30);
            renderFN(sphere->GetOutputPort());
            break;
        }
        case G_CUBE:
        {
            vtkNew<vtkCubeSource> cube;
            renderFN(cube->GetOutputPort());
            break;
        }                         
    }     
}

void MainWindow::initPipelineBrower()
{
    
    
}

void MainWindow::createClipping(clippingTools ct)
{
    switch (ct) 
    {
        case C_PLANE:
        {
//            vtkNew<vtkPlane> plane;
//            vtkNew<vtkClipPolyData> clipper;
//            clipper->SetClipFunction(plane);
//            clipper->InsideOutOn();
//            clipper->SetInputConnection(sphereSource->GetOutputPort());
            
                        
        
            break;
        }
    }
    
}

void MainWindow::shiftInteractorStyle(bool check)
{
    if(check)
    {
        vtkNew<vtkInteractorStyleTrackballActor> interactor;
        ui->wt_MainView->renderWindow()->GetInteractor()->SetInteractorStyle(interactor);
    }
    else
    {
        vtkNew<vtkInteractorStyleTrackballCamera > interactor;
        ui->wt_MainView->renderWindow()->GetInteractor()->SetInteractorStyle(interactor);
    }
    
}
