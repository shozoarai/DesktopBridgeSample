using System;
using System.Text;
using System.Runtime.InteropServices;

namespace UwpProcessHelper
{
    static class UwpHelper
    {
        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        static extern int GetCurrentPackageFullName(ref int packageFullNameLength, ref StringBuilder packageFullName);

        const int APPMODEL_ERROR_NO_PACKAGE = 15700;
        const int ERROR_INSUFFICIENT_BUFFER = 122;
        const int ERROR_SUCCESS = 0;


        internal static bool IsRunningAsUwp()
        {
            if (isWindows7OrLower())
            {
                return false;
            }
            try
            {
                StringBuilder sb = new StringBuilder(1024);
                int length = 0;
                // Get buffer size.
                int result = GetCurrentPackageFullName(ref length, ref sb);
                if (result == APPMODEL_ERROR_NO_PACKAGE)
                {
                    return false;
                }
                return true;
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Windows 7 or Lower Version
        /// </summary>
        /// <returns></returns>
        private static bool isWindows7OrLower()
        {
            int versionMajor = Environment.OSVersion.Version.Major;
            int versionMinor = Environment.OSVersion.Version.Minor;
            double version = versionMajor + (double)versionMinor / 10;
            return version <= 6.1;
        }
    }
}
