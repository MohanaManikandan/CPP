using System.Runtime.InteropServices;

[InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
[Guid("4A476008-30A0-4CBA-9003-882EF4FCF68C")]
interface IHen
{
    [PreserveSig]
    void Cluck();

    [PreserveSig]
    void Roost();
}

[InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
[Guid("96F71D92-A188-4D29-8A92-C7FDF167C115")]
interface IOnlineChicken
{
    // IHen
    [PreserveSig]
    void Cluck();

    [PreserveSig]
    void Roost();

    // IOnlineChicken
    [PreserveSig]
    void Forage();
}

[InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
[Guid("630FDA7E-15E4-43B4-81E4-B0EB2B70D1C7")]
interface IOfflineChicken
{
    [PreserveSig]
    void Load();

    [PreserveSig]
    void Save();
}

namespace UsingCOMWithCSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            // Using IHen Methods
            IHen pHen = CreateHen();
            pHen.Cluck();
            pHen.Roost();

            // QueryInterface Is Achieved Through Something Like A C-Style Cast
            IOnlineChicken pOnlineChicken = (IOnlineChicken)pHen;
            pOnlineChicken.Forage();
        }

        [DllImport("ImplementingIUnkown.dll", PreserveSig = false)]
        static extern IHen CreateHen();
    }
}
