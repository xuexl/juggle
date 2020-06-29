/**
 * @class   vtkJuggleActor
 * @brief   
*/


#ifndef VTKJUGGLEACTOR_H
#define VTKJUGGLEACTOR_H

#include<string>

#include<vtkOpenGLActor.h>


class vtkJuggleActor: public vtkOpenGLActor
{
public:
    static vtkJuggleActor* New();
    vtkTypeMacro(vtkJuggleActor, vtkOpenGLActor);
    
    /**
     * set/get  tag
     * tag is for 
    */
    void SetTag(const std::string &tag);
    std::string GetTag();

protected:
    vtkJuggleActor() = default;
    ~vtkJuggleActor() override = default;
    
private:
    std::string Tag;
    
};

#endif // VTKJUGGLEACTOR_H
