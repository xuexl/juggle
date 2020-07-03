#include "vtkJuggleInteractorStyleActor.h"

#include<iostream>

#include<vtkProp3D.h>
#include <vtkObjectFactory.h>
#include<vtkOBJWriter.h>


vtkStandardNewMacro(vtkJuggleInteractorStyleActor);

//--------------------------------------------------------------------------------
vtkJuggleInteractorStyleActor::vtkJuggleInteractorStyleActor() = default;

//--------------------------------------------------------------------------------
vtkJuggleInteractorStyleActor::~vtkJuggleInteractorStyleActor() = default;

//--------------------------------------------------------------------------------
void vtkJuggleInteractorStyleActor::OnLeftButtonUp()
{
    auto prop = this->InteractionProp;
    if(prop)
    {
//        auto pos = prop->GetPosition();
//        auto className = prop->GetClassName();
        
//        std::cout<<"**************************************************************"<<std::endl;
//        std::cout<<"className:: "<<className<<std::endl;
//        std::cout<<"position:: "<<pos[0]<<","<<pos[1]<<","<<pos[2]<<","<<std::endl;
        
        
        
    }
    
    vtkInteractorStyleTrackballActor::OnLeftButtonUp();
}

//查看移动actor 后的 位置

