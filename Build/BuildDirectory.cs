using QED.BuildTool.Core;
using System;
using System.Collections.Generic;
using System.Text;

namespace QED
{
    namespace BuildTool
    {
        [RegisterPath]
        public class BuildDirectory : Directory
        {
            public BuildDirectory() {}
        }

        [RegisterPath]
        public class BuildGLFWDirectory : Directory
        {
            public BuildGLFWDirectory()
            {
                SubDirectory = "GLFW";
            }
        }

        [RegisterPath]
        public class BuildGLADDirectory : Directory
        {
            public BuildGLADDirectory()
            {
                SubDirectory = "GLAD";
            }
        }

        [RegisterPath]
        public class BuildImGuiDirectory : Directory
        {
            public BuildImGuiDirectory()
            {
                SubDirectory = "ImGui";
            }
        }

        [RegisterPath]
        public class BuildEngineDirectory : Directory
        {
            public BuildEngineDirectory()
            {
                SubDirectory = "Engine";
            }
        }

        [RegisterPath]
        public class BuildSandboxDirectory : Directory
        {
            public BuildSandboxDirectory()
            {
                SubDirectory = "Sandbox";
            }
        }
    }
}