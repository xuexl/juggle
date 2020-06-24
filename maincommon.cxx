#include "maincommon.h"

#include<vtkNew.h>
#include<vtkPropPicker.h>
#include<vtkRenderWindow.h>
#include<vtkRenderWindowInteractor.h>

#include<vtkActor.h>
#include<vtkPlane.h>
#include<vtkClipPolyData.h>
#include<vtkPolyDataMapper.h>
#include<vtkProperty.h>



void MainCommon::Execute(vtkObject *vtkNotUsed(caller), unsigned long vtkNotUsed(eventId), void *vtkNotUsed(callData))
{
    
    int* pos = renderer->GetRenderWindow()->GetInteractor()->GetEventPosition();
    
    vtkNew<vtkPropPicker> picker;        
    picker->Pick(pos[0], pos[1], 0, renderer);
    
    auto actor = picker->GetActor();
    
    
}