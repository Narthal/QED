using QED.BuildTool.Core;
using System;
using System.Collections.Generic;
using System.Text;

namespace QED
{
    namespace BuildTool
    {
        [RegisterPath]
        public class VendorDirectory : Directory
        {
            public VendorDirectory()
            {

            }
        }

        [RegisterPath]
        public class VendorGLFWDirectory : Directory
        {
            public VendorGLFWDirectory()
            {
                SubDirectory = "GLFW";
            }
        }

        [RegisterPath]
        public class VendorGLADDirectory : Directory
        {
            public VendorGLADDirectory()
            {
                SubDirectory = "GLAD";
            }
        }

        [RegisterPath]
        public class VendorImGuiDirectory : Directory
        {
            public VendorImGuiDirectory()
            {
                SubDirectory = "ImGui";

                FileGroup sources = new FileGroup(this, "ImGuiSrc");
                sources.AddFiles("ImGui\\*.cpp", false);

                FileGroup headers = new FileGroup(this, "ImGuiHead");
                headers.AddFiles("ImGui\\*.h", false);
            }
        }

        [RegisterPath]
        public class VendorGLMDirectory : Directory
        {
            public VendorGLMDirectory()
            {
                SubDirectory = "GLM";
            }
        }

        [RegisterPath]
        public class VendorStbDirectory : Directory
        {
            public VendorStbDirectory()
            {
                SubDirectory = "stb";
            }
        }

        [RegisterPath]
        public class VendorSPDLogDirectory : Directory
        {
            public VendorSPDLogDirectory()
            {
                SubDirectory = "spdlog";
            }
        }

        [RegisterPath]
        public class VendorSQLiteDirectory : Directory
        {
            public VendorSQLiteDirectory()
            {
                SubDirectory = "SQLiteAmalgamation";
            }
        }

        [RegisterPath]
        public class VendorCPythonDirectory : Directory
        {
            public VendorCPythonDirectory()
            {
                SubDirectory = "cpython";
            }
        }
    }
}
