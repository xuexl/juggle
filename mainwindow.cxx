#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include"maincommon.h"
#include"JuggleClip.h"

#include<string>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkNew.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCommand.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , loader(std::unique_ptr<JuggleLoader>(new JuggleLoader))
{
    ui->setupUi(this);
    
    initToolBar();
    
    initView();

    //
    connect(ui->pb_apply, SIGNAL(clicked()), this, SLOT(apply()));
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
    connect(createSphereAction, &QAction::triggered, [this](){ createBasicGeometries(JuggleLoader::G_SPHERE); });
    basicGeometriesToolBar->addAction(createSphereAction);
    
    createCubeAction = new QAction(QIcon("://images/toolbar/cube.png"), tr(u8"创建立方体"), this);
    connect(createCubeAction, &QAction::triggered, [this](){ createBasicGeometries(JuggleLoader::G_CUBE); });        
    basicGeometriesToolBar->addAction(createCubeAction);
    
    createPlaneAction = new QAction(QIcon("://images/toolbar/plane.png"), tr(u8"创建平面"), this);
    connect(createPlaneAction, &QAction::triggered, [this](){ createBasicGeometries(JuggleLoader::G_PLANE); });        
    basicGeometriesToolBar->addAction(createPlaneAction);
    
    //
    implicitFunctionsToolBar = addToolBar(tr(u8"切割工具"));
    
    createPlaneClippingAction = new QAction(QIcon("://images/toolbar/rect.png"), tr(u8"平面切割"), this);
    connect(createPlaneClippingAction, &QAction::triggered, [this](bool check){ createClipping(check); });
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
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    ui->wt_MainView->setRenderWindow(renderWindow);    
    
    this->Renderer = vtkSmartPointer<vtkJuggleRenderer>::New();    
    //The AddRenderer method of  RenderWindow must be in front of  setting propreties of Renderer.
    renderWindow->AddRenderer(this->Renderer);    
        
    std::string configFile = "";
    JuggleOptions options = Parser.GetOptionsFromConfigFile(configFile);
    options.Axis = true;
    this->Renderer->Initialize(options);            
}

void MainWindow::createBasicGeometries(JuggleLoader::BasicGeometries ge)
{
    loader->createBasicGeometries(this->Renderer, ge);
}

void MainWindow::apply()
{    
//    auto actors = this->Renderer->GetActors();
//    actors->InitTraversal();
    
//    for(int i=0; i<actors->GetNumberOfItems(); ++i)
//    {        
//        auto actor = actors->GetNextActor();
        
          
//    }
        
}

void MainWindow::createClipping(bool check)
{        
    if(check)
    {
        JuggleClip clip;
        clip.ChangeClipTool(JuggleClip::C_PLANE);        
        clip.Clip(this->Renderer);
        
        {
        
//        if(ct & C_PLANE)
//        {
//            auto colors =
//               vtkSmartPointer<vtkNamedColors>::New();
//             vtkColor3d actorColor = colors->GetColor3d("AliceBlue");
//             vtkColor3d  EdgeColour = colors->GetColor3d("SteelBlue");
////             vtkColor3d BackgroundColour = colors->GetColor3d("Silver");
            
//            vtkNew<vtkPlane> plane;
//            plane->SetOrigin(.0,.0,.0);
//            plane->SetNormal(.0,.0,1.0);
            
//            vtkNew<vtkSampleFunction> sample;
//            sample->SetImplicitFunction(plane);
//            sample->SetModelBounds(-1.5, 1.5, -1.5, 1.5, -1.5, 1.5);
//            sample->SetSampleDimensions(20, 20, 20);
//            sample->ComputeNormalsOff();
            
//            vtkNew<vtkContourFilter> surface;
//            surface->SetInputConnection(sample->GetOutputPort());
//            surface->SetValue(0, 0.0);
              
//            vtkNew<vtkPolyDataMapper> mapper;
//            mapper->SetInputConnection(surface->GetOutputPort());
//            mapper->ScalarVisibilityOff();
              
//            vtkNew<vtkActor> actor;
//            actor->SetMapper(mapper);
//            actor->GetProperty()->EdgeVisibilityOn();
//            actor->GetProperty()->SetColor(actorColor.GetData());
//            actor->GetProperty()->SetEdgeColor(EdgeColour.GetData());
            
//            ui->wt_MainView->renderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actor);
            
//        }
        }
    }
    else
    {
        JuggleClip clip;
        clip.Restore(this->Renderer);
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

