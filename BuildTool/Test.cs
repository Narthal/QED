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
                Console.WriteLine("test");

                File file = new File(this, "Engine", FileType.Source);
                file.AddFile("Program.cs");
            }
        }

        [TargetConfig]
        public class TargetConfig : Targets
        {
            public TargetConfig()
            {
                Architecture = Architecture.x64;
                Platform = Platform.Windows | Platform.Linux;
            }
        }
    }
}
