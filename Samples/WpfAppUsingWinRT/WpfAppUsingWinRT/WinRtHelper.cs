using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace WpfAppUsingWinRT
{
    [ComImport]
    [Guid("3E68D4BD-7135-4D10-8018-9FB6D9F33FA1")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    interface IInitializeWithWindow
    {
        void Initialize(IntPtr hwnd);
    }

    static class WinRtHelper
    {
        /// <summary>
        /// WinRT オブジェクトのスレッド モデルとの親和性を設定します
        /// Initialize Windows Runtime Object.
        /// </summary>
        /// <param name="winRT"></param>
        internal static void InitializeWithWindow(object winRT)
        {
            IInitializeWithWindow initWindow = (IInitializeWithWindow)(object)winRT;
            initWindow.Initialize(System.Diagnostics.Process.GetCurrentProcess().MainWindowHandle);
        }
    }
}
