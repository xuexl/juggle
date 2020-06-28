#include "JuggleClip.h"

#include"vtkjugglerenderer.h"

#include<vtkPlane.h>
#include<vtkClipPolyData.h>
#include<vtkDataSetMapper.h>
#include<vtkNew.h>
#include<vtkActor.h>
#include<vtkProperty.h>
#include<vtkRenderWindow.h>


//-----------------------------------------------------
JuggleClip::JuggleClip() = default;

//-----------------------------------------------------
JuggleClip::~JuggleClip() = default;

//-----------------------------------------------------
void JuggleClip::ChangeClipTool(ClipTools ct)
{    
//    CurrentClipTool = ct;
    
    switch (ct) 
    {
        case C_PLANE:
        {    
            vtkNew<vtkPlane> plane;
        
            double origin[] = {.0,.0,.0};
            double normal[] = {1.0, -1.0, -1.0};
            
            plane->SetOrigin(origin);
            plane->SetNormal(normal);
            
            ImplicitFunction = plane;            
            break;
        }
        
    }
    
}

//-----------------------------------------------------
void JuggleClip::Clip(vtkJuggleRenderer* ren)
{
    auto actors = ren->GetActors();
    actors->InitTraversal();
    
    for(int i=0; i<actors->GetNumberOfItems(); ++i)
    {
        auto actor = actors->GetNextActor();
        
        vtkNew<vtkClipPolyData> clipper;    
        clipper->SetInputData(actor->GetMapper()->GetInput());
        clipper->SetClipFunction(this->ImplicitFunction);
        clipper->SetValue(0);
        clipper->Update();
        
        vtkNew<vtkDataSetMapper> clipMapper;    
        clipMapper->SetInputData(clipper->GetOutput());
//        clipMapper->SetScalarVisibility(false);
        
        vtkNew<vtkActor> clipActor;
        clipActor->SetMapper(clipMapper); 
        clipActor->GetProperty()->SetOpacity(.6);
        
        ren->AddActor(clipActor);
        
        actor->SetVisibility(false);
    }
    
    ren->GetRenderWindow()->Render();
}

//-----------------------------------------------------
void Restore(vtkJuggleRenderer* ren)
{
    
}

//-----------------------------------------------------
void JuggleClip::CreatePlane()
{
    
}
