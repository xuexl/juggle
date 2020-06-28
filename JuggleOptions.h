/**
 * @class JuggleOptions
 * @brief The class that holds and manages options
*/

#ifndef JUGGLEOPTIONS_H
#define JUGGLEOPTIONS_H

#include<string>
#include<vector>


class ConfigurationOptions;

struct JuggleOptions
{
    bool Axis = false;
    bool FullScreen = false;
    bool GeometryOnly = false;
    double CameraViewAngle;
    std::vector<double> BackgroundColor = { 0.5, 0.6, 0.7 };
    std::vector<double> CameraPosition;
    std::vector<double> CameraFocalPoint;
    std::vector<double> CameraViewUp;
};

class JuggleOptionsParser
{
public:
    
    /**
     * Parse the config file in different potential location
     * Returns the resulting options.
     */
    JuggleOptions GetOptionsFromConfigFile(const std::string& filePath);

    
    JuggleOptionsParser();
    ~JuggleOptionsParser();
    
private:
    JuggleOptionsParser(JuggleOptionsParser const&) = delete ;
    void operator=(JuggleOptionsParser const&) = delete ;
    
    std::unique_ptr<ConfigurationOptions> ConfigOptions;
};

#endif // JUGGLEOPTIONS_H
