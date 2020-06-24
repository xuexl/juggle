#ifndef VTKJUGGLERENDERER_H
#define VTKJUGGLERENDERER_H

#include "JuggleOptions.h"

#include <vtkOpenGLRenderer.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkOrientationMarkerWidget.h>


class vtkJuggleRenderer : public vtkOpenGLRenderer
{
public:
    static vtkJuggleRenderer* New();
    vtkTypeMacro(vtkJuggleRenderer, vtkOpenGLRenderer);
        
    void ShowAxis(bool show);
    
    bool IsAxisVisible();
    
    
    void Render() override;
    
    /**
     * Should be called after being added to a vtkRenderWindow
     */
    void Initialize(const JuggleOptions& options);
    
    vtkGetSmartPointerMacro(AxisWidget, vtkOrientationMarkerWidget);
    vtkSetSmartPointerMacro(AxisWidget, vtkOrientationMarkerWidget);
    
    //@{
    /**
     * Set/Get the polydata mapper, used for hotkey purposes
     */
//    vtkGetSmartPointerMacro(PolyDataMapper, vtkMapper);
//    vtkSetSmartPointerMacro(PolyDataMapper, vtkMapper);
    //@}
    
    /**
     * Initialize the camera position, focal point,
     * view up and view angle according to the options if any
     */
    void InitializeCamera();
  
    /**
     * Reset the camera to its initial parameters
     */
    void ResetCamera() override;
    
protected:
    vtkJuggleRenderer() = default;
    ~vtkJuggleRenderer() override = default;
    
    void ReleaseGraphicsResources(vtkWindow* w) override;
    
    std::string GenerateMetaDataDescription();
    
    vtkSmartPointer<vtkOrientationMarkerWidget> AxisWidget;
    vtkSmartPointer<vtkMapper> PolyDataMapper;
    vtkNew<vtkCamera> InitialCamera;
     
    JuggleOptions Options;
    
    bool AxisVisible;
    
};

#endif // VTKJUGGLERENDERER_H
