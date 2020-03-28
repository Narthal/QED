using QED.BuildTool.Core;
using System;
using System.Collections.Generic;
using System.Text;


namespace BuildTool
{
    namespace QED
    {
        [RegisterPath]
        public class QEDRootDirectory : Directory
        {
            public QEDRootDirectory()
            {

            }
        }

        [RegisterPath]
        [RegisterProjectGroup]
        public class QED : ProjectGroup
        {
            public QED()
            {
                AddProject("GLFW");
                AddProject("GLAD");
                AddProject("ImGui");
                AddProject("Engine");
                AddProject("Sandbox");
            }
        }
    }
}
