#include "vtkjugglerenderer.h"

#include <vtkObjectFactory.h>
#include <vtkAbstractArray.h>
#include <vtkAxesActor.h>
#include<vtkDataSet.h>
#include<vtkFieldData.h>
#include<vtkMapper.h>
#include<vtkCamera.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNamedColors.h>


#include"JuggleLog.h"


vtkStandardNewMacro(vtkJuggleRenderer);

//----------------------------------------------------------------------------
void vtkJuggleRenderer::ReleaseGraphicsResources(vtkWindow* w)
{
    
    
  this->Superclass::ReleaseGraphicsResources(w);
}

//----------------------------------------------------------------------------
void vtkJuggleRenderer::Initialize(const JuggleOptions& options)
{
    if (!this->RenderWindow)
    {
      JuggleLog::Print(JuggleLog::Severity::Error, "No render window linked");
      return;
    }    
    
    this->RemoveAllViewProps();
    this->RemoveAllLights();
    
    this->Options = options;        
    this->AxisVisible = this->Options.Axis;
    
    
    this->SetBackground(options.BackgroundColor.data());
    
    this->InitializeCamera();    
    
    this->ShowAxis(true);
}

//----------------------------------------------------------------------------
std::string vtkJuggleRenderer::GenerateMetaDataDescription()
{
  std::string description;
  description += " \n";
  if (this->PolyDataMapper)
  {
    vtkDataSet* dataset = this->PolyDataMapper->GetInput();
    if (dataset)
    {
      description += " Number of points: ";
      description += std::to_string(dataset->GetNumberOfPoints());
      description += " \n Number of cells: ";
      description += std::to_string(dataset->GetNumberOfCells());
      description += " \n";

      // Field Data
      vtkFieldData* fieldData = dataset->GetFieldData();
      int nbArrays = fieldData->GetNumberOfArrays();
      for (vtkIdType i = 0; i < nbArrays; i++)
      {
        vtkAbstractArray* array = fieldData->GetAbstractArray(i);
        if (array)
        {
          vtkIdType nbTuples = array->GetNumberOfTuples();
          if (nbTuples == 1)
          {
            description += " ";
            description += array->GetName();
            description += " = ";
            description += array->GetVariantValue(0).ToString();
            description += " \n";
          }
        }
      }
    }
    else
    {
      description += " Unavailable\n";
    }
  }
  else
  {
    description += " Unavailable\n";
  }

  return description;
}

//----------------------------------------------------------------------------
void vtkJuggleRenderer::ShowAxis(bool show)
{
  if (show)
  {
    vtkNew<vtkAxesActor> axes;
    this->AxisWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    this->AxisWidget->SetOrientationMarker(axes);
    this->AxisWidget->SetInteractor(this->RenderWindow->GetInteractor());
    this->AxisWidget->SetViewport(0.85, 0.0, 1.0, 0.15);
    this->AxisWidget->On();
    this->AxisWidget->InteractiveOff();
    this->AxisWidget->SetKeyPressActivation(false);
  }
  else
  {
    this->AxisWidget = nullptr;
  }

  this->AxisVisible = show;
}

//----------------------------------------------------------------------------
bool vtkJuggleRenderer::IsAxisVisible()
{
  return this->AxisVisible;
}

//----------------------------------------------------------------------------
void vtkJuggleRenderer::Render()
{
 
  this->Superclass::Render();

}

//----------------------------------------------------------------------------
void vtkJuggleRenderer::InitializeCamera()
{
    this->Superclass::ResetCamera();
    vtkCamera* cam = this->GetActiveCamera();
    if (this->Options.CameraPosition.size() == 3)
    {
        cam->SetPosition(this->Options.CameraPosition.data());
    }
    if (this->Options.CameraFocalPoint.size() == 3)
    {
        cam->SetFocalPoint(this->Options.CameraFocalPoint.data());
    }
    if (this->Options.CameraViewUp.size() == 3)
    {
        cam->SetViewUp(this->Options.CameraViewUp.data());
    }
    if (this->Options.CameraViewAngle != 0)
    {
        cam->SetViewAngle(this->Options.CameraViewAngle);
    }
    cam->OrthogonalizeViewUp();
}

//----------------------------------------------------------------------------
void vtkJuggleRenderer::ResetCamera()
{
    vtkCamera* cam = this->GetActiveCamera();
    cam->DeepCopy(this->InitialCamera);
    cam->Modified();
}
