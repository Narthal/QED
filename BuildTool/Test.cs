using System;
using System.Collections.Generic;
using System.Text;

using QED.BuildTool.Core;

namespace QED
{
    namespace BuildTool
    {
        [RegisterPath]
        public class TestDirectory : Directory
        {
            public TestDirectory()
            {
                FileGroup sources = new FileGroup(this, "HelloSrc");
                sources.AddFile("Main.cpp");

                FileGroup headers = new FileGroup(this, "HelloHeader");
                headers.AddFile("Main.h");
            }
        }

        [RegisterProject]
        public class TestProject : Project
        {
            public TestProject()
            {
                Name = "Hello";

                OutputType = OutputType.Application;
                OutputDirectory = BuildTool.GetDirectory("TestDirectory");
                SourceFileGroups.Add("HelloSrc");
                HeaderFileGroups.Add("HelloHeader");

                Targets = new Targets()
                {
                    Architecture = Architecture.x86 | Architecture.x64,
                    Platform = Platform.Windows,
                    Configuration = Configuration.Debug | Configuration.Release,
                };

            }
        }
    }
}
