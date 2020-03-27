using System;
using System.Collections.Generic;
using System.Text;

namespace QED
{
    namespace BuildTool
    {
        namespace Core
        {
            public class ConditionalConfigurationData
            {
                public ConditionalConfigurationData()
                {
                    CompilerOptions = new List<string>();
                    PreprocessorDefinitions = new List<string>();
                }

                // Basic configuration
                public bool? EnableOptimizations { get; set; }
                public bool? UseDebugStdLibrary { get; set; }
                public bool? StaticLinkStdLibrary { get; set; }

                // Precompiled headers
                public bool? EnablePrecompiledHeaders { get; set; }
                public string? PrecompiledHeaderFileGroup { get; set; }

                // Compiler options
                public List<string> CompilerOptions { get; set; }
                public bool? EnableIncrementalLinking { get; set; }

                // Preprocessor
                public List<string> PreprocessorDefinitions { get; set; }
            }
        }
    }
}
