#include "juggleoptions.h"

#include<map>
#include<vector>


//----------------------------------------------------------------------------
namespace
{
template<typename T>
bool CompareVectors(const std::vector<T>& v1, const std::vector<T>& v2)
{
  if (v1.size() != v2.size())
  {
    return false;
  }

  for (size_t i = 0; i < v1.size(); i++)
  {
    if (v1[i] != v2[i])
    {
      return false;
    }
  }

  return true;
}
}  // namespace

class ConfigurationOptions
{
public:
    
    bool InitializeDictionaryFromConfigFile(const std::string& filePath);    

    
private:
    using Dictionnary = std::map<std::string, std::string>;
    Dictionnary ConfigDic;
    
};

//----------------------------------------------------------------------------
bool ConfigurationOptions::InitializeDictionaryFromConfigFile(const std::string& filePath)
{
//  this->ConfigDic.clear();

//  const std::string& configFilePath = this->GetSettingsFilePath();
//  if (configFilePath.empty())
//  {
//    return false;
//  }

//  std::ifstream file;
//  file.open(configFilePath.c_str());

//  if (!file.is_open())
//  {
//    F3DLog::Print(
//      F3DLog::Severity::Error, "Unable to open the configuration file ", configFilePath);
//    return false;
//  }

//  Json::Value root;
//  Json::CharReaderBuilder builder;
//  builder["collectComments"] = false;
//  std::string errs;
//  std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
//  bool success = Json::parseFromStream(builder, file, &root, &errs);
//  if (!success)
//  {
//    F3DLog::Print(
//      F3DLog::Severity::Error, "Unable to parse the configuration file ", configFilePath);
//    F3DLog::Print(F3DLog::Severity::Error, errs);
//    return false;
//  }

//  for (auto const& id : root.getMemberNames())
//  {
//    std::regex re(id);
//    std::smatch matches;
//    if (std::regex_match(filePath, matches, re))
//    {
//      const Json::Value node = root[id];

//      for (auto const& nl : node.getMemberNames())
//      {
//        const Json::Value v = node[nl];
//        this->ConfigDic[nl] = v.asString();
//      }
//    }
//  }

  return true;
}

//----------------------------------------------------------------------------
JuggleOptionsParser::JuggleOptionsParser() = default;

//----------------------------------------------------------------------------
JuggleOptionsParser::~JuggleOptionsParser() = default;

//----------------------------------------------------------------------------
JuggleOptions JuggleOptionsParser::GetOptionsFromConfigFile(const std::string& filePath)
{
    JuggleOptions res;
    
//  this->ConfigOptions->InitializeDictionaryFromConfigFile(filePath);
    
    return res;
}
