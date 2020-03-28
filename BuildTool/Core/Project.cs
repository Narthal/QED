using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text;

namespace QED
{
    namespace BuildTool
    {
        namespace Core
        {
            public enum OutputType
            {
                Application,
                SharedLibrary,
                StaticLibrary,
                Utility
            }

            public enum CppVersion
            {
                cpp11,
                cpp14,
                cpp17
            }

            public abstract class Project : ConditionalConfigurationData
            {
                public Project()
                {
                    ProjectID = BuildTool.projects.Count;

                    // Directories
                    SourceFileGroups = new List<string>();
                    HeaderFileGroups = new List<string>();

                    // Conditionals
                    Conditionals = new List<Conditional>();

                    ReferencedProjectIDs = new List<int>();
                }

                public void RetieveProjectPath()
                {
                    object[] customAttributes = GetType().GetCustomAttributes(true);
                    foreach (Attribute attribute in customAttributes)
                    {
                        if (attribute.GetType() == typeof(RegisterPathAttribute))
                        {
                            var PathAttribute = (RegisterPathAttribute)attribute;
                            Path = System.IO.Directory.GetParent(PathAttribute.SourcePath).FullName + '\\' + Name + ".vcxproj";
                        }
                    }
                }

                #region Basic configuration

                public string Name { get; protected set; }
                public OutputType OutputType { get; protected set; }
                public CppVersion CppVersion { get; protected set; }

                #endregion

                #region Directories
                public Directory OutputDirectory { get; protected set; }
                public List<string> SourceFileGroups { get; protected set; }
                public List<string> HeaderFileGroups { get; protected set; }

                public string PreCompiledHeaderGroup { get; set; }

                #endregion

                #region Target definitions

                public Targets Targets { get; protected set; }

                #endregion

                #region Config

                public List<Conditional> Conditionals { get; protected set; }
                public List<Filter> Filters { get; set; }
                public List<int> ReferencedProjectIDs { get; set; }

                #endregion

                public int ProjectID { get; private set; }
                public string Path { get; private set; }

                #region Utility

                public void CreateFilters()
                {
                    // Create filters after conditionals are set
                    Filters = new List<Core.Filter>();
                    foreach (Core.Architecture architecture in Targets.GetArchitectureFlags())
                    {
                        foreach (Core.Platform platform in Targets.GetPlatformFlags())
                        {
                            foreach (Core.Configuration configuration in Targets.GetConfigurationFlags())
                            {
                                Filters.Add(new Core.Filter(architecture, platform, configuration));
                                foreach (var conditional in Conditionals)
                                {
                                    if
                                        (
                                            (conditional.ArchitectureFilters.HasValue == false || conditional.ArchitectureFilters.Value.HasFlag(architecture)) &&
                                            (conditional.PlatformFilters.HasValue == false || conditional.PlatformFilters.Value.HasFlag(platform)) &&
                                            (conditional.ConfigurationFilters.HasValue == false || conditional.ConfigurationFilters.Value.HasFlag(configuration))
                                        )
                                    {
                                        foreach (PropertyInfo filterPropertyInfo in Filters.GetType().GetGenericArguments()[0].GetProperties())
                                        {
                                            foreach (PropertyInfo conditionalPropertyInfo in conditional.GetType().GetProperties())
                                            {
                                                if (filterPropertyInfo.Name == conditionalPropertyInfo.Name)
                                                {
                                                    filterPropertyInfo.SetValue(Filters[Filters.Count - 1], conditionalPropertyInfo.GetValue(conditional));
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    return;
                }

                #endregion
            }
        }
    }
}
