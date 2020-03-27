using System;
using System.Collections.Generic;
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
                    // Directories
                    SourceFileGroups = new List<string>();
                    HeaderFileGroups = new List<string>();

                    // Conditionals
                    Conditionals = new List<Conditional>();

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

                #endregion

                #region Target definitions

                public Targets Targets { get; protected set; }

                #endregion

                #region Conditionals

                public List<Conditional> Conditionals { get; protected set; }
                public List<Filter> Filters { get; set; }

                public ConditionalConfigurationData GetConditionalData(Conditional conditional)
                {
                    // Create return value with project's default values
                    ConditionalConfigurationData conditionalConfigurationData = new ConditionalConfigurationData()
                    {
                        // Basic configuration
                        EnableOptimizations = this.EnableOptimizations,
                        UseDebugStdLibrary = this.UseDebugStdLibrary,
                        StaticLinkStdLibrary = this.StaticLinkStdLibrary,

                        // Precompiled headers
                        EnablePrecompiledHeaders = this.EnablePrecompiledHeaders,
                        PrecompiledHeaderFileGroup = this.PrecompiledHeaderFileGroup,

                        // Compiler options
                        CompilerOptions = this.CompilerOptions,

                        // Preprocessor
                        PreprocessorDefinitions = this.PreprocessorDefinitions,
                    };

                    // Update fields if filter contains definition for it

                    // Basic configuration
                    if (conditional.EnableOptimizations     != null) conditionalConfigurationData.EnableOptimizations   = conditional.EnableOptimizations;
                    if (conditional.UseDebugStdLibrary      != null) conditionalConfigurationData.UseDebugStdLibrary    = conditional.UseDebugStdLibrary;
                    if (conditional.StaticLinkStdLibrary    != null) conditionalConfigurationData.StaticLinkStdLibrary  = conditional.StaticLinkStdLibrary;

                    // Precompiled headers
                    if (conditional.EnablePrecompiledHeaders    != null) conditionalConfigurationData.EnablePrecompiledHeaders      = conditional.EnablePrecompiledHeaders;
                    if (conditional.PrecompiledHeaderFileGroup  != null) conditionalConfigurationData.PrecompiledHeaderFileGroup    = conditional.PrecompiledHeaderFileGroup;

                    // Compiler options
                    if (conditional.CompilerOptions != null) conditionalConfigurationData.CompilerOptions = conditional.CompilerOptions;

                    // Preprocessor
                    if (conditional.PreprocessorDefinitions != null) conditionalConfigurationData.PreprocessorDefinitions = conditional.PreprocessorDefinitions;


                    return conditionalConfigurationData;
                }

                #endregion
            }
        }
    }
}
