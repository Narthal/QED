using System;
using System.Collections.Generic;
using System.Text;

namespace QED
{
    namespace BuildTool
    {
        namespace VisualStudio
        {
            static class GUID
            {
                public static string ProjectGUID = "8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942";
                public static string VirtualFolderGUID = "2150E333-8FDC-42A3-9474-1A3956D46DE8";

                public static string[] predefinedGUIDs =
                {
                    /*00*/   "E41E9B4A-D374-4D95-BA0C-FB1EAB657186",
                    /*01*/   "8A1F3C3C-0137-4F1B-9152-FE757AB61486",
                    /*02*/   "26D526BB-4D26-45D3-98D9-D20CD37F1DE8",
                    /*03*/   "0BC71D75-C9D8-415A-9BBF-421E7C505D36",
                    /*04*/   "1A366C3B-705D-43A0-B09F-74ED5241B5DE",
                    /*05*/   "65ACC16E-3E39-4959-9F34-EC23A200F02F",
                    /*06*/   "26C63251-FE83-47FD-B7CA-08846A0C679F",
                    /*07*/   "65D2A84B-2CC6-4BCA-86BA-E63C8325098C",
                    /*08*/   "6EB9E433-0EEF-4F41-8C23-5B2355152177",
                    /*09*/   "259B29D5-B4A0-41D9-BE1D-8D182E9522D5",
                    /*10*/   "4C0D48A0-3B7D-429B-9B0F-D7102A716989",
                    /*11*/   "8F128FC9-99B7-48C4-8008-4E6739BA957F",
                    /*12*/   "D394D4A1-81C6-4135-9BB1-E389A2930252",
                    /*13*/   "DA5422EE-C5E4-4D05-8590-D71C94507941",
                    /*14*/   "29072D53-58DE-458E-87D5-4A01C85BF0F4",
                    /*15*/   "FB782A46-405E-4571-92B5-8376341610F9",
                    /*16*/   "B7C4DB05-2F2E-4CBB-9F46-39142E83A192",
                    /*17*/   "61939E6A-56E4-4C64-B8F8-2A59D5A4BBDB",
                    /*18*/   "F8E8F25A-FA85-49CF-B28C-88AA8D79777D",
                    /*19*/   "9E867A66-3E40-4983-BE9C-D47A8650B186",
                };

                static int counter = 0;
                public static string GetGUID()
                {
                    return predefinedGUIDs[counter++];
                }
            }
        }
    }
}
