/**
 * @class JugglePolygonRegion
 * @brief   
*/

#ifndef JUGGLEPOLYGONREGION_H
#define JUGGLEPOLYGONREGION_H



class JugglePolygonRegion
{
public:
    
    /**
     * create a polygon region via mouse.
     *  create one point at the clicked position.
     *  link the points one by one to create one polygon.
     *  if the position of clicking has existed one point then create none.
    */
    
    void AddPosition(int *pos);
    
    
    /**
     * create extraction via vtkLinearExtrusionFilter
    */
    
    
    JugglePolygonRegion();
    ~JugglePolygonRegion();
     
protected:
    
    
private:
    JugglePolygonRegion(JugglePolygonRegion const&) = delete;
    void operator=(JugglePolygonRegion const&) = delete;   
    
};

#endif // JUGGLEPOLYGONREGION_H
