#ifndef VTK_EXTENDACTOR_H
#define VTK_EXTENDACTOR_H

#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkObjectFactory.h>
#include <vtkRenderingCoreModule.h>
#include <vtkProperty.h>
#include<vtkActor.h>
#include<vtkTexture.h>


//class Node;

//class VTKRENDERINGCORE_EXPORT VTK_ExtendActor : public vtkActor {
//    public:
//        vtkTypeMacro(VTK_ExtendActor, vtkActor);

//    static VTK_ExtendActor *New();

//    //
//    virtual void ReleaseGraphicsResources(vtkWindow *window) {
//        this->Device->ReleaseGraphicsResources(window);
//        this->Superclass::ReleaseGraphicsResources(window);
//    }

//    virtual int RenderOpaqueGeometry(vtkViewport *viewport){
//        if ( ! this->Mapper ) {
//            return 0;
//        }
//        if (!this->Property) {
//            this->GetProperty();
//        }
//        if (this->GetIsOpaque()) {
//            vtkRenderer *ren = static_cast<vtkRenderer *>(viewport);
//            this->Render(ren);
//            return 1;
//        }
//        return 0;
//    }

//    virtual int RenderTranslucentPolygonalGeometry(vtkViewport *viewport){
//        if ( ! this->Mapper ) {
//          return 0;
//        }
//        if (!this->Property) {
//          this->GetProperty();
//        }
//        if (!this->GetIsOpaque()) {
//            vtkRenderer *ren = static_cast<vtkRenderer *>(viewport);
//            this->Render(ren);
//            return 1;
//        }
//        return 0;
//    }

//    virtual void Render(vtkRenderer *ren){
//        this->Property->Render(this, ren);
//        this->Device->SetProperty (this->Property);
//        this->Property->Render(this, ren);
//        if (this->BackfaceProperty) {
//            this->BackfaceProperty->BackfaceRender(this, ren);
//            this->Device->SetBackfaceProperty(this->BackfaceProperty);
//        }
//        if (this->Texture) {
//            this->Texture->Render(ren);
//        }
//        this->ComputeMatrix();
//        this->Device->SetUserMatrix(this->Matrix);
//        this->Device->Render(ren,this->Mapper);
//    }

//    void ShallowCopy(vtkProp *prop) {
//        VTK_ExtendActor *f = VTK_ExtendActor::SafeDownCast(prop);
//        this->vtkActor::ShallowCopy(prop);
//    }
    
//    //
////    Node*   node_i_represent{nullptr};

////    protected:
//        vtkActor* Device;

////        VTK_ExtendActor() {
////            this -> Device = vtkActor::New();
////        }

////        ~VTK_ExtendActor() {
////            this -> Device -> Delete();
////        }
//    private:
        
//};

//vtkStandardNewMacro(VTK_ExtendActor)

#endif // VTK_EXTENDACTOR_H
