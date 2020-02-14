using System;
using System.Collections.Generic;
using System.Text;

namespace QED
{
    namespace BuildTool
    {
        namespace Core
        {
            public enum BinaryType
            {
                Application,
                SharedLibrary,
                StaticLibrary,
            }
            public abstract class Project
            {
                public BinaryType BinaryType { get; protected set; }
                public FileGroup SourceFileGroup { get; protected set; }
                public FileGroup HeaderFileGroup { get; protected set; }
            }
        }
    }
}
