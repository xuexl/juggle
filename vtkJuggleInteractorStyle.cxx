#include "vtkJuggleInteractorStyle.h"

#include "vtkjugglerenderer.h"
#include"vtkJuggleActor.h"

#include<vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include<vtkRendererCollection.h>
#include<vtkCellPicker.h>

#include<vtkPoints.h>
#include<vtkCellArray.h>
#include<vtkPolyData.h>
#include<vtkPolyDataMapper.h>
#include<vtkProperty.h>
#include<vtkLinearExtrusionFilter.h>
#include<vtkTriangleFilter.h>

#include <vtkObjectFactory.h>

vtkStandardNewMacro(vtkJuggleInteractorStyle);

#include<iostream>

//------------------------------------------------------------------------
vtkJuggleInteractorStyle::vtkJuggleInteractorStyle() = default;

//------------------------------------------------------------------------
vtkJuggleInteractorStyle::~vtkJuggleInteractorStyle() = default;

//------------------------------------------------------------------------
void vtkJuggleInteractorStyle::OnLeftButtonDown()
{    
    vtkRenderWindowInteractor* rwi = this->GetInteractor();
    vtkRenderWindow* renWin = rwi->GetRenderWindow();
    vtkJuggleRenderer* ren = vtkJuggleRenderer::SafeDownCast(renWin->GetRenderers()->GetFirstRenderer());
        
//    if(this->Status == I_POLYGONREGION)
//    {
        auto position = this->GetInteractor()->GetEventPosition();        
        vtkNew<vtkCellPicker> picker;
        picker->Pick(position[0], position[1], .0, ren);
        
        double wPosition[3];
        picker->GetPickPosition(wPosition);
        
        this->PolygonVertexs.push_back({wPosition[0], wPosition[1], wPosition[2]});
//    }
    
    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

//------------------------------------------------------------------------
void vtkJuggleInteractorStyle::OnLeftButtonUp()
{

    
    vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
}

//------------------------------------------------------------------------
void vtkJuggleInteractorStyle::OnMouseMove()
{
    
    vtkInteractorStyleTrackballCamera::OnMouseMove();
}

//------------------------------------------------------------------------
void vtkJuggleInteractorStyle::OnRightButtonDown()
{
    vtkRenderWindowInteractor* rwi = this->GetInteractor();
    vtkRenderWindow* renWin = rwi->GetRenderWindow();
    vtkJuggleRenderer* ren = vtkJuggleRenderer::SafeDownCast(renWin->GetRenderers()->GetFirstRenderer());
   
    
    this->SetStatus(I_NONE);
    
    int num = this->PolygonVertexs.size();

    vtkNew<vtkPoints> points;    
    points->SetNumberOfPoints(num);    
    for(int i=0; i<num; ++i)
    {
        auto pos = this->PolygonVertexs[i].data();
        points->SetPoint(i, pos[0], pos[1], pos[2]);
    }
    
    vtkNew<vtkCellArray> lines;
    lines->InsertNextCell(num+1);
    for(int i=0; i<num; ++i)
    {
        lines->InsertCellPoint(i);
    }
    lines->InsertCellPoint(0);
    
    vtkNew<vtkPolyData> polygon;
    polygon->SetPoints(points);
    polygon->SetLines(lines);
    
    vtkNew<vtkTriangleFilter> triangleFilter;
    triangleFilter->SetInputData(polygon);
    triangleFilter->Update();
    
    vtkSmartPointer<vtkLinearExtrusionFilter> extruder =
        vtkSmartPointer<vtkLinearExtrusionFilter>::New();
    extruder->SetInputConnection(triangleFilter->GetOutputPort());
    extruder->SetScaleFactor(.4);
    extruder->SetExtrusionTypeToVectorExtrusion();
    extruder->CappingOn();
    extruder->SetVector(0, 0, 1);
    extruder->Update();
    
    vtkNew<vtkPolyDataMapper> polygonMapper ;    
    polygonMapper->SetInputConnection(extruder->GetOutputPort());
    polygonMapper->Update();
    
    vtkNew<vtkJuggleActor> polygonActor ;
    polygonActor->SetMapper(polygonMapper);
    polygonActor->GetProperty()->SetColor(.2,.4,.3);
    polygonActor->GetProperty()->SetOpacity(.6);
//    polygonActor->GetProperty()->SetRepresentationToWireframe();
    

    ren->AddActor(polygonActor);
    renWin->Render();
    
    vtkInteractorStyleTrackballCamera::OnRightButtonDown();    
}

