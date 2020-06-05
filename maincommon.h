#ifndef MAINCOMMON_H
#define MAINCOMMON_H

#include<vtkCommand.h>
#include <vtkRenderer.h>


class MainCommon: public vtkCommand
{
public:
    vtkTypeMacro(MainCommon, vtkCommand);
    static MainCommon *New()
    {
      return new MainCommon;
    }
    void Execute(vtkObject *vtkNotUsed(caller), unsigned long vtkNotUsed(eventId), void *vtkNotUsed(callData));
    
    vtkRenderer *renderer;
};

#endif // MAINCOMMON_H
