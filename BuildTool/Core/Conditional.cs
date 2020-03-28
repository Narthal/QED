using System;
using System.Collections.Generic;
using System.Text;

namespace QED
{
    namespace BuildTool
    {
        namespace Core
        {
            public class Conditional : ProjectConfigurationData
            {
                public Conditional(Architecture? architecture, Platform? platform, Configuration? configuration)
                {
                    ArchitectureFilters = architecture;
                    PlatformFilters = platform;
                    ConfigurationFilters = configuration;
                }

                #region Filter settings

                public Architecture? ArchitectureFilters { get; private set; }
                public Platform? PlatformFilters { get; private set; }
                public Configuration? ConfigurationFilters { get; private set; }

                #endregion
        }
        }
    }
}
