#pragma once
#include "EnumReflect.h"
#include "CppReflect.h"

#ifdef SPM_EXPORT
#define SPM_DLLEXPORT __declspec(dllexport)
#else
#define SPM_DLLEXPORT __declspec(dllimport)
#endif


/// <summary>
/// Defines what needs to be done with given item. Not all project types support all enumerations - for example
/// packaging projects / C# projects does not support CustomBuild.
/// 
/// Order of ItemType must be the same as appear in .vcxproj (first comes first)
/// </summary>
DECLARE_ENUM(ItemType, "",

    //
    // C# references to .net assemblies
    //
    Reference,

    //
    // Header file (.h)
    //
    ClInclude,

    //
    // Source codes (.cpp) files
    //
    ClCompile,

    //
    // .rc / resource files.
    //
    ResourceCompile,

    //
    // Any custom file with custom build step
    //
    CustomBuild,

    //
    // .def / .bat
    //
    None,

    //
    // .ico files.
    //
    Image,

    //
    // .txt files.
    //
    Text,

    // Following enumerations are used in android packaging project (.androidproj)
    Content,
    AntBuildXml,
    AndroidManifest,
    AntProjectPropertiesFile,

    //
    // For Android package project: Reference to another project, which needs to be included into package.
    //
    ProjectReference,

    //
    // Intentionally not valid value, so can be replaced with correct one. (Visual studio does not supports one)
    //
    Invalid,

    //
    // C# - source codes to compile
    //
    Compile,

    //
    // Android / Gradle project, *.template files.
    //
    GradleTemplate,

    //
    // .java - source codes to compile
    //
    JavaCompile,

    //
    //  Native Visualization files (*.natvis)
    //
    Natvis
);

//
//  Visual Studio project tagging.
//
DECLARE_ENUM(EKeyword, "projecttype_",
    //
    // For sub-folders for example (Also default value). Also for utility projects.
    //
    projecttype_None = 0,

    //
    // Windows project (32 or 64 bit)
    //
    projecttype_Win32Proj,

    //
    // Same as Win32Proj, for some reason exists as separate value
    //
    projecttype_ManagedCProj,

    //
    // Android project
    //
    projecttype_Android,

    //
    // Windows application with MFC support
    //
    projecttype_MFCProj,

    //
    // Android packaging project (does not exists on file format level)
    //
    projecttype_AntPackage,

    /// <summary>
    /// Typically set for Android packaging project. (does not exists on file format level)
    /// </summary>
    projecttype_GradlePackage
);

class SPM_DLLEXPORT ProjectGlobalConf : ReflectClassT<ProjectGlobalConf>
{
public:
    REFLECTABLE(ProjectGlobalConf,
        // This is typically non-configurable by end-user.
        (CStringA)ProjectGuid,
        (EKeyword)Keyword,
        (CStringW)WindowsTargetPlatformVersion
    );
};


//
// Project type
//
DECLARE_ENUM(EConfigurationType, "conftype_",
    //
    // .exe
    //
    conftype_Application = 0,

    //
    // .dll
    //
    conftype_DynamicLibrary,

    //
    // .lib or .a
    //
    conftype_StaticLibrary,

    //
    // Android gradle project: Library (.aar/.jar)
    //
    conftype_Library,

    //
    // Utility project
    //
    conftype_Utility,

    //
    // This value does not physically exists in serialized form in .vcxproj, used only for generation of C# script.
    //
    conftype_ConsoleApplication
);



//
// Binary image format / target
//
DECLARE_ENUM(ESubSystem, "subsystem_",
    //
    // Not specified
    //
    subsystem_NotSet,

    //
    // <summary>
    //
    subsystem_Windows,

    //
    // Console application
    //
    subsystem_Console,
    subsystem_Native,
    subsystem_EFI_Application,
    subsystem_EFI_Boot_Service_Driver,
    subsystem_EFI_ROM,
    subsystem_EFI_Runtime,
    subsystem_POSIX
);


//
// Generate debug information
//
DECLARE_ENUM(EGenerateDebugInformation, "debuginfo_",
    //
    // No
    //
    debuginfo_false,

    //
    // Optimize for debugging
    //
    debuginfo_true,

    //
    // Use fast linking
    //
    debuginfo_DebugFastLink,

    //
    // Generate Debug Information optimized for sharing and publishing (/DEBUG:FULL)
    //
    debuginfo_DebugFull
);


class SPM_DLLEXPORT LinkerSystemConf: ReflectClassT<LinkerSystemConf>
{
public:
    REFLECTABLE(LinkerSystemConf,
        (ESubSystem)SubSystem
    );
};

class SPM_DLLEXPORT LinkerDebuggingConf : ReflectClassT<LinkerDebuggingConf>
{
public:
    REFLECTABLE(LinkerDebuggingConf,
        (EGenerateDebugInformation)GenerateDebugInformation
    );
};

//
// Character set - unicode MBCS.
//
DECLARE_ENUM(ECharacterSet, "charset_",
    //
    // Unicode
    //
    charset_Unicode = 0,

    //
    // Ansi
    //
    charset_MultiByte
);


//
// How to optimize code ?
//
DECLARE_ENUM(EOptimization, "optimization_",
    optimization_Custom,

    //
    // No optimizations
    //
    optimization_Disabled,

    //
    // Minimize Size, in Windows projects
    //
    optimization_MinSpace,

    //
    // Minimize Size, In Android projects
    //
    optimization_MinSize,

    //
    // Maximize Speed
    //
    optimization_MaxSpeed,

    //
    // Full Optimization
    //
    optimization_Full,

    //
    // Not available in project file, but this is something we indicate that we haven't set value
    //
    optimization_ProjectDefault
);

class SPM_DLLEXPORT CCppConf: public ReflectClassT<CCppConf>
{
public:
    REFLECTABLE(CCppConf,
        (EOptimization)Optimization
    );
};


class SPM_DLLEXPORT GeneralConf : public ReflectClassT<GeneralConf>
{
public:
    REFLECTABLE(GeneralConf,
        //
        // Output directory
        //
        (CStringW)OutDir,
        //
        // Intermediate Directory
        //
        (CStringW)IntDir,
        (CStringW)TargetName,
        (CStringW)TargetExt,

        (EConfigurationType)ConfigurationType,

        //
        // Mysterious flag, which cannot be set from Visual studio properties, but it affects to some parameter's default values.
        //
        (bool)UseDebugLibraries,

        //
        // For example:
        //     'Clang_3_8'     - Clang 3.8
        //     'v141'          - for Visual Studio 2017.
        //     'v140'          - for Visual Studio 2015.
        //     'v120'          - for Visual Studio 2013.
        //
        (CStringW)PlatformToolset,
        (ECharacterSet)CharacterSet
    );
};


class SPM_DLLEXPORT LinkerConf: public ReflectClassT<LinkerConf>
{
public:
    REFLECTABLE(LinkerConf,
        (LinkerSystemConf)System,
        (LinkerDebuggingConf)Debugging
    );
};

