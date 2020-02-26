using System;
using System.Collections.Generic;
using System.Text;

namespace QED
{
    namespace BuildTool
    {
        namespace Core
        {
            [Flags]
            public enum Architecture
            {
                x86     = 1,
                x64     = 2,
            }

            [Flags]
            public enum Platform
            {
                Windows = 1,
                Linux   = 2,
            }

            [Flags]
            public enum Configuration
            {
                Debug           = 1,
                Release         = 2,
                Distribution    = 4,
            }
            public class Targets
            {
                public Architecture Architecture { get; set; }
                public Platform Platform { get; set; }
                public Configuration Configuration { get; set; }

                public IEnumerable<Architecture> GetArchitectureFlags()
                {
                    foreach (Enum value in Enum.GetValues(Architecture.GetType()))
                        if (Architecture.HasFlag(value))
                            yield return (Architecture)value;
                }

                public IEnumerable<Platform> GetPlatformFlags()
                {
                    foreach (Enum value in Enum.GetValues(Platform.GetType()))
                        if (Platform.HasFlag(value))
                            yield return (Platform)value;
                }

                public IEnumerable<Configuration> GetConfigurationFlags()
                {
                    foreach (Enum value in Enum.GetValues(Configuration.GetType()))
                        if (Configuration.HasFlag(value))
                            yield return (Configuration)value;
                }
            }
        }
    }
}
