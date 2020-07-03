#include "JuggleLoader.h"

#include "JuggleLog.h"
#include "JuggleOptions.h"
#include"vtkJuggleActor.h"

#include <vtk3DSImporter.h>
#include <vtkOBJImporter.h>
#include <vtkVRMLImporter.h>
#include <vtkGLTFImporter.h>

#include <vtkCallbackCommand.h>
#include <vtksys/Directory.hxx>
#include <vtksys/SystemTools.hxx>
#include<vtkRenderWindow.h>

#include<vtkPolyDataMapper.h>
#include<vtkSphereSource.h>
#include<vtkCubeSource.h>
#include<vtkPlaneSource.h>

#include<vtkLinearExtrusionFilter.h>
#include<vtkProperty.h>


//----------------------------------------------------------------------------
JuggleLoader::JuggleLoader() = default;

//----------------------------------------------------------------------------
JuggleLoader::~JuggleLoader() = default;

//----------------------------------------------------------------------------
void JuggleLoader::LoadFile(vtkSmartPointer<vtkJuggleRenderer> ren, const std::string& file)
{
    
    
}

//----------------------------------------------------------------------------
void JuggleLoader::createBasicGeometries(vtkJuggleRenderer* ren, BasicGeometries ge)
{ 
    switch (ge) 
    {
        case G_SPHERE:
        {
            this->createSphere(ren);           
            break;
        }
        case G_CUBE:
        {
            this->createCube(ren);                  
            break;
        }
        case G_PLANE:
        {
            this->createPlane(ren);                  
            break;
        }
    }
    
    ren->ResetCamera();
    ren->GetRenderWindow()->Render();
}

//----------------------------------------------------------------------------
vtkSmartPointer<vtkImporter> JuggleLoader::GetImporter(
  const JuggleOptions& options, const std::string& file)
{
  if (!vtksys::SystemTools::FileExists(file))
  {
    JuggleLog::Print(JuggleLog::Severity::Error, "Specified input file '", file, "' does not exist!");
    return nullptr;
  }

  if (!options.GeometryOnly)
  {
    std::string ext = vtksys::SystemTools::GetFilenameLastExtension(file);
    ext = vtksys::SystemTools::LowerCase(ext);

    if (ext == ".3ds")
    {
      vtkNew<vtk3DSImporter> importer;
      importer->SetFileName(file.c_str());
      importer->ComputeNormalsOn();
      return importer;
    }

    if (ext == ".obj")
    {
      vtkNew<vtkOBJImporter> importer;
      importer->SetFileName(file.c_str());

      std::string path = vtksys::SystemTools::GetFilenamePath(file);
      importer->SetTexturePath(path.c_str());

      // This logic is partially implemented in the OBJ importer itself
      // This complete version should be backported.
      std::string mtlFile = file + ".mtl";
      if (vtksys::SystemTools::FileExists(mtlFile))
      {
        importer->SetFileNameMTL(mtlFile.c_str());
      }
      else
      {
        mtlFile = path + "/" + vtksys::SystemTools::GetFilenameWithoutLastExtension(file) + ".mtl";
        if (vtksys::SystemTools::FileExists(mtlFile))
        {
          importer->SetFileNameMTL(mtlFile.c_str());
        }
      }

      return importer;
    }

    if (ext == ".wrl")
    {
      vtkNew<vtkVRMLImporter> importer;
      importer->SetFileName(file.c_str());
      return importer;
    }

    if (ext == ".gltf" || ext == ".glb")
    {
      vtkNew<vtkGLTFImporter> importer;
      importer->SetFileName(file.c_str());
      return importer;
    }
  }

//  vtkNew<vtkF3DGenericImporter> importer;
//  importer->SetFileName(file.c_str());
//  importer->SetOptions(options);

//  if (!importer->CanReadFile())
//  {
    return nullptr;
//  }

//  return importer;
}

//----------------------------------------------------------------------------
void JuggleLoader::createSphere(vtkJuggleRenderer* ren)
{
    vtkNew<vtkSphereSource> sphere;
    sphere->SetPhiResolution(30);
    sphere->SetThetaResolution(30);      
    
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(sphere->GetOutputPort());

    vtkNew<vtkJuggleActor> actor;
    actor->SetMapper(mapper);
    
    ren->AddActor(actor);
}

//----------------------------------------------------------------------------
void JuggleLoader::createCube(vtkJuggleRenderer* ren)
{
    vtkNew<vtkCubeSource> cube; 
    
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(cube->GetOutputPort());

    vtkNew<vtkJuggleActor> actor;
    actor->SetMapper(mapper);
//    actor->GetProperty()->SetInterpolationToGouraud();
//    actor->GetProperty()->SetRepresentationToSurface();
//    actor->GetProperty()->SetRepresentationToWireframe();
    
    ren->AddActor(actor);
}

//----------------------------------------------------------------------------
void JuggleLoader::createPlane(vtkJuggleRenderer* ren)
{
    vtkNew<vtkPlaneSource> plane; 
    
//    vtkNew<vtkLinearExtrusionFilter> extrude;
//    extrude->SetInputConnection(plane->GetOutputPort());
//    extrude->SetExtrusionType(VTK_VECTOR_EXTRUSION);
//    extrude->SetVector(.0,.0,1.0);
//    extrude->SetScaleFactor(2);
    
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(plane->GetOutputPort());

    vtkNew<vtkJuggleActor> actor;
    actor->SetMapper(mapper);
    
//    actor->GetProperty()->SetOpacity(.5);
//    actor->GetProperty()->SetColor(.1,.2,.3);
    
    ren->AddActor(actor);
}
