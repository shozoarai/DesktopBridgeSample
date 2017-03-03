using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace WpfAppUsingWinRT
{

    static class NaitiveHelper
    {

        delegate void Callback([MarshalAs(UnmanagedType.LPWStr)] string name);
        [DllImport("WinRtHelper.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool OpenFilePicker(IntPtr hWnd, Callback callback);

        static Callback callback;

        static MainWindow window;

        internal static bool OpenPicker(MainWindow window)
        {
            try
            {
                NaitiveHelper.window = window;
                var hWnd = System.Diagnostics.Process.GetCurrentProcess().MainWindowHandle;
                callback = new Callback(GetFileName);
                var ret = OpenFilePicker(hWnd, callback);
                return ret;
            }
            catch (Exception ex)
            {
                return false;
            }
        }

        internal static void GetFileName(string name)
        {

            System.Diagnostics.Debug.WriteLine(name);
            window.Dispatcher.InvokeAsync(() =>
            {
                window.UpdateLog(name);
            });
            // デリゲートの解放
            var ds = callback.GetInvocationList();
            foreach (var d in ds)
            {
                callback -= (Callback)d;
            }

        }

    }
}
