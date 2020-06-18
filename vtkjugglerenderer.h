#ifndef VTKJUGGLERENDERER_H
#define VTKJUGGLERENDERER_H


#include <vtkOpenGLRenderer.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkOrientationMarkerWidget.h>


class vtkJuggleRenderer : public vtkOpenGLRenderer
{
public:
    static vtkJuggleRenderer* New();
    vtkTypeMacro(vtkJuggleRenderer, vtkOpenGLRenderer);
        
    void Render() override;
    
    void Initialize();
    
    vtkGetSmartPointerMacro(AxisWidget, vtkOrientationMarkerWidget);
    vtkSetSmartPointerMacro(AxisWidget, vtkOrientationMarkerWidget);
    
    //@{
    /**
     * Set/Get the polydata mapper, used for hotkey purposes
     */
    vtkGetSmartPointerMacro(PolyDataMapper, vtkMapper);
    vtkSetSmartPointerMacro(PolyDataMapper, vtkMapper);
    //@}
    
    
    void ResetCamera() override;
    
protected:
    vtkJuggleRenderer() = default;
    ~vtkJuggleRenderer() override = default;
    
    void ReleaseGraphicsResources(vtkWindow* w) override;
    
    std::string GenerateMetaDataDescription();
    
    vtkSmartPointer<vtkOrientationMarkerWidget> AxisWidget;
    vtkSmartPointer<vtkMapper> PolyDataMapper;
    vtkNew<vtkCamera> InitialCamera;
     
     
};

#endif // VTKJUGGLERENDERER_H
