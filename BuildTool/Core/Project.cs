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
            public abstract class Project
            {
                public Project()
                {
                    SourceFileGroups = new List<string>();
                    HeaderFileGroups = new List<string>();
                }
                public string Name { get; protected set; }

                public Directory OutputDirectory { get; protected set; }
                public OutputType OutputType { get; protected set; }
                public List<string> SourceFileGroups { get; protected set; }
                public List<string> HeaderFileGroups { get; protected set; }

                public Targets Targets { get; protected set; }
            }
        }
    }
}
