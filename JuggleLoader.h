/**
 * @class   JuggleLoader
 * @brief   The loader class
 *
 */

#ifndef JUGGLELOADER_H
#define JUGGLELOADER_H

#include <vtkNew.h>
#include <vtkSmartPointer.h>
#include<vtkCommand.h>

#include "vtkJuggleRenderer.h"

class vtkJuggleRenderer;
class vtkImporter;
struct JuggleOptions;

class JuggleLoader
{
public:    
    enum vtkCustomEvents
    {
        NewFilesEvent = vtkCommand::UserEvent + 100,
        LoadFileEvent
    };
    
    enum BasicGeometries
    {
        G_SPHERE, 
        G_CUBE
    };
    
    /**
     * Load a file if any have been added     
     */
    void LoadFile(vtkSmartPointer<vtkJuggleRenderer> ren, const std::string& file);
    
    /**
     * create box, sphere, cylinder and so on.
    */
    void createBasicGeometries(vtkJuggleRenderer* ren, BasicGeometries ge);      
    
    JuggleLoader();
    ~JuggleLoader();
    
protected:
    static vtkSmartPointer<vtkImporter> GetImporter(
      const JuggleOptions& options, const std::string& file);
    
    JuggleOptionsParser Parser;    
    
    void createSphere(vtkJuggleRenderer* ren);
    void createCube(vtkJuggleRenderer* ren);
    
private:
    JuggleLoader(JuggleLoader const&) = delete;
    void operator=(JuggleLoader const&) = delete;
    
};

#endif // JUGGLELOADER_H
