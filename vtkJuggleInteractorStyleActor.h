/**
 * @class vtkJuggleInteractorStyleActor
 * @brief 
*/

#ifndef VTKJUGGLEINTERACTORSTYLEACTOR_H
#define VTKJUGGLEINTERACTORSTYLEACTOR_H

#include <vtkInteractorStyleTrackballActor.h>


class vtkJuggleInteractorStyleActor: public vtkInteractorStyleTrackballActor
{
public:
    static vtkJuggleInteractorStyleActor* New();
    vtkTypeMacro(vtkJuggleInteractorStyleActor, vtkInteractorStyleTrackballActor);
    
    void OnLeftButtonUp() override;
    
protected:    
    vtkJuggleInteractorStyleActor();
    ~vtkJuggleInteractorStyleActor() override;
    
private:
    vtkJuggleInteractorStyleActor(const vtkJuggleInteractorStyleActor&) = delete;
    void operator=(const vtkJuggleInteractorStyleActor&) = delete;    
};

#endif // VTKJUGGLEINTERACTORSTYLEACTOR_H
