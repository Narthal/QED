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
                None    = 0,
                x86     = 1,
                x64     = 2,
            }

            [Flags]
            public enum Platform
            {
                None    = 0,
                Windows = 1,
                Linux   = 2,
            }
            public abstract class Targets
            {
                public Architecture Architecture { get; protected set; }
                public Platform Platform { get; protected set; }
            }
        }
    }
}
