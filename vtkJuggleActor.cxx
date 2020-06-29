#include "vtkJuggleActor.h"

#include <vtkObjectFactory.h>

vtkStandardNewMacro(vtkJuggleActor);

void vtkJuggleActor::SetTag(const std::string &tag)
{
    this->Tag = tag;
}

std::string vtkJuggleActor::GetTag()
{
    return this->Tag;
}
