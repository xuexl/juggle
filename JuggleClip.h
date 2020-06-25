/**
 * @class   JuggleClip
 * @brief   clip class  
*/

#ifndef JUGGLECLIP_H
#define JUGGLECLIP_H

#include<vtkSmartPointer.h>
#include<vtkImplicitFunction.h>


class vtkJuggleRenderer;


class JuggleClip
{
public:
    
    enum ClipTools
    {         
        C_PLANE
    };
    
    /**
     *change current clip tool. 
    */
    void ChangeClipTool(ClipTools ct);
    
    /**
     * apply the clip
    */
    void Apply(vtkJuggleRenderer* ren);
    
    JuggleClip();
    ~JuggleClip();
        
protected:
//    ClipTools CurrentClipTool = C_PLANE;
    vtkSmartPointer<vtkImplicitFunction> ImplicitFunction;
    
    
    void CreatePlane();
    
    
private:
    JuggleClip(JuggleClip const&) = delete;
    void operator=(JuggleClip const&) = delete;
    
};

#endif // JUGGLECLIP_H
