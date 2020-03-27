using System;
using System.Collections.Generic;
using System.Text;

namespace QED
{
    namespace BuildTool
    {
        namespace Core
        {
            public class Filter : ConditionalConfigurationData
            {
                public Filter(Architecture architecture, Platform platform, Configuration configuration)
                {
                    ArchitectureFilter = architecture;
                    PlatformFilter = platform;
                    ConfigurationFilter = configuration;
                }

                public Architecture ArchitectureFilter { get; private set; }
                public Platform PlatformFilter { get; private set; }
                public Configuration ConfigurationFilter { get; private set; }


            }
        }
    }
}
