﻿#pragma once
#include "VCConfiguration.h"                //VCConfiguration
#include <list>
#include <initializer_list>
#include <functional>                       //std::functional
#include <guiddef.h>                        //GUID

//---------------------------------------------------------
//  Project
//---------------------------------------------------------
class SPM_DLLEXPORT Project :
    ReflectClassT<Project>,
    pugi::xml_document
{
public:
    Project();
    Project(const wchar_t* _name);

    //
    //  It's good to set save directory before adding files to project, as all paths will be relative to project.
    //
    void SetSaveDirectory(const wchar_t* dir);

    //
    //  Gets project save directory.
    //
    std::wstring GetSaveDirectory();

    //
    // Clears existing project
    //
    void New();

    //
    // Loads .vcxproj file.
    //
    bool Load(const wchar_t* file);

    //
    // Saves project file
    //
    bool Save(const wchar_t* file = nullptr);

    virtual void OnAfterSetProperty(ReflectPath& path);

    REFLECTABLE(Project,
        (ProjectGlobalConf)Globals
    );

    //
    //  Sets visual studio version, in year. e.g. 2017, 2019, ...
    //
    void SetVsVersion(int vsVersion);

    //
    // Gets project guid, initialized if it's not initialized yet
    //
    std::wstring GetGuid(void);

    //
    // Add support for platform or configuration, if not yet added.
    //
    void AddPlatform(const char* platform);
    void AddPlatforms(std::initializer_list<std::string> _platforms);

    void AddConfiguration(const char* configuration);
    void AddConfigurations(std::initializer_list<std::string> _configuration);

    //
    // Queries for currently selected toolset, if none is selected, tries to determine from visual studio format version
    //
    std::string GetToolset();

    //
    //  Adds files to the project.
    //
    void AddFiles(std::initializer_list<std::wstring> fileList);
    void AddFile(const wchar_t* file);

    //
    // Visits each project configuration, if configurationName & platformName - uses additional filtering, otherwise visits all configurations.
    //
    void VisitConfigurations( std::function<void (VCConfiguration&)> visitConf, const char* configurationName = nullptr, const char* platformName = nullptr );


protected:
    // Project name, typically used to identify project within solution or specify saved filename if file is not specified during save.
    std::wstring name;

    // Directory where project shall be saved.
    std::wstring saveDir;

    //  "Win32", "х64", ...
    std::vector<std::string> platforms;

    //  "Debug", "Release", user defined
    std::vector<std::string> configurationNames;

    //
    //  Gets current configuration names, if not initialized yet, returns default "Debug" / "Release" set.
    //
    std::vector<std::string>& GetConfigurationNames();

    // Project settings
    std::vector< std::shared_ptr<VCConfiguration> > configurations;

    //  List of files within a project.
    std::list<ProjectFile>  files;

    // Project guid
    GUID guid;

    //
    //  Visual studio version, in year. e.g. 2017, 2019, ...
    //
    int vsVersion;

    // Platform Toolset, e.g. "v141" (for vs2017), "142" (for vs2019), "Clang_5_0" ...
    std::string toolset;

    pugi::xml_node project( );
    pugi::xml_node projectGlobals;
    pugi::xml_node markForPropertyGroup;

public:
    //
    // Selects project node with specific name / label, of specific confName/platform, creates if does not exists
    //
    pugi::xml_node selectProjectNodes(const wchar_t* name, const wchar_t* label, const wchar_t* confName, const wchar_t* platform);

protected:
    //
    // Platforms or Configurations arrays updated, bPlatforms == true - platforms false = configurations, bAdd = true - added, bAdd = false - removed.
    //
    void PlatformConfigurationsUpdated(std::initializer_list<std::string> items, bool bPlatforms, bool bAdd);
};

