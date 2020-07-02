/**
 * @class   vtkJuggleInteractorStyle
 * @brief   custom interactor style based on default trackball camera
*/

#ifndef VTKJUGGLEINTERACTORSTYLE_H
#define VTKJUGGLEINTERACTORSTYLE_H

#include<vector>
#include<array>

#include <vtkInteractorStyleTrackballCamera.h>


class vtkJuggleInteractorStyle: public vtkInteractorStyleTrackballCamera
{
public:
    static vtkJuggleInteractorStyle* New();
    vtkTypeMacro(vtkJuggleInteractorStyle, vtkInteractorStyleTrackballCamera);
    
    void OnLeftButtonDown() override;
    void OnLeftButtonUp() override;
    void OnMouseMove() override;
    void OnRightButtonDown() override;
        
    enum InteractorStatus
    {
        I_NONE,
        I_POLYGONREGION        
    };
    
    /**
     * set/get property of status.
    */
    vtkSetMacro(Status, InteractorStatus);
    vtkGetMacro(Status, InteractorStatus);
    
protected:    
    vtkJuggleInteractorStyle();
    ~vtkJuggleInteractorStyle() override;
    
    InteractorStatus Status;
    
    std::vector<std::array<double, 3>> PolygonVertexs;
    
private:
    vtkJuggleInteractorStyle(const vtkJuggleInteractorStyle&) = delete;
    void operator=(const vtkJuggleInteractorStyle&) = delete;
    
};

#endif // VTKJUGGLEINTERACTORSTYLE_H
