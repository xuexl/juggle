#include "vtkjugglerenderer.h"

#include <vtkObjectFactory.h>
#include <vtkAbstractArray.h>
#include <vtkAxesActor.h>
#include<vtkDataSet.h>
#include<vtkFieldData.h>
#include<vtkMapper.h>
#include<vtkCamera.h>


vtkStandardNewMacro(vtkJuggleRenderer);

//----------------------------------------------------------------------------
void vtkJuggleRenderer::ReleaseGraphicsResources(vtkWindow* w)
{
    
    
  this->Superclass::ReleaseGraphicsResources(w);
}

//----------------------------------------------------------------------------
void vtkJuggleRenderer::Initialize()
{
    
    this->RemoveAllViewProps();
    this->RemoveAllLights();
    
    
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
void vtkJuggleRenderer::Render()
{
 
  this->Superclass::Render();

}

//----------------------------------------------------------------------------
void vtkJuggleRenderer::ResetCamera()
{
  vtkCamera* cam = this->GetActiveCamera();
  cam->DeepCopy(this->InitialCamera);
  cam->Modified();
}