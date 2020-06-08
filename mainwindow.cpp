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
#include<vtkSampleFunction.h>
#include<vtkContourFilter.h>
#include<vtkProperty.h>

#include <vtkCommand.h>
#include <vtkClipPolyData.h>

#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>

#include"maincommon.h"


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
    connect(createPlaneClippingAction, &QAction::triggered, [this](bool check){ createClipping(check, C_PLANE); });
    implicitFunctionsToolBar->addAction(createPlaneClippingAction);
    createPlaneClippingAction->setCheckable(true);
    
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
    
    vtkNew<vtkAxesActor> axes;
    vtkNew<vtkOrientationMarkerWidget> widget ;
    double rgba[4]{0.0, 0.0, 0.0, 0.0};
    colors->GetColor("Carrot",rgba);
    widget->SetOutlineColor(rgba[0], rgba[1], rgba[2]);
    widget->SetOrientationMarker( axes );
    widget->SetInteractor(renderWindow->GetInteractor());
//    widget->SetViewport( 0.0, 0.0, 0.6, 0.6 );
    widget->SetEnabled(1);
    widget->InteractiveOn();
    
    renderer->ResetCamera();
//    renderer->AddActor(axes);
    

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

void MainWindow::createClipping(bool check, clippingTools ct)
{        
    if(check)
    {
        currentClippingTool = ct;

        
        if(ct & C_PLANE)
        {
            auto colors =
               vtkSmartPointer<vtkNamedColors>::New();
             vtkColor3d actorColor = colors->GetColor3d("AliceBlue");
             vtkColor3d  EdgeColour = colors->GetColor3d("SteelBlue");
//             vtkColor3d BackgroundColour = colors->GetColor3d("Silver");
            
            vtkNew<vtkPlane> plane;
            plane->SetOrigin(.0,.0,.0);
            plane->SetNormal(.0,.0,1.0);
            
            vtkNew<vtkSampleFunction> sample;
            sample->SetImplicitFunction(plane);
            sample->SetModelBounds(-1.5, 1.5, -1.5, 1.5, -1.5, 1.5);
            sample->SetSampleDimensions(20, 20, 20);
            sample->ComputeNormalsOff();
            
            vtkNew<vtkContourFilter> surface;
            surface->SetInputConnection(sample->GetOutputPort());
            surface->SetValue(0, 0.0);
              
            vtkNew<vtkPolyDataMapper> mapper;
            mapper->SetInputConnection(surface->GetOutputPort());
            mapper->ScalarVisibilityOff();
              
            vtkNew<vtkActor> actor;
            actor->SetMapper(mapper);
            actor->GetProperty()->EdgeVisibilityOn();
            actor->GetProperty()->SetColor(actorColor.GetData());
            actor->GetProperty()->SetEdgeColor(EdgeColour.GetData());
            
            ui->wt_MainView->renderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actor);
            
        }
        
    }
    else
    {
        currentClippingTool = C_NONE;

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

