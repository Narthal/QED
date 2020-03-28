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

                FileGroup sources = new FileGroup(this, "GLADSrc");
                sources.AddFiles("GLAD\\*.c", true);

                FileGroup headers = new FileGroup(this, "GLADHead");
                headers.AddFiles("GLAD\\*.h", true);
            }
        }
    }
}
