using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Runtime.InteropServices;
using System.IO;

namespace StoreTestHelper
{
    static class StoreHelper
    {
        static MainWindow main;
        //delegate void AppLicenseCallback([MarshalAs(UnmanagedType.LPWStr)] string name);
        delegate void AppLicenseCallback(bool isActive, bool isTrial, bool isInactive, bool isFull);
        [DllImport("StoreCppHelper.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool GetAppLicense(AppLicenseCallback callback);
        static AppLicenseCallback appLicenseCallback;

        delegate void FileNameCallback([MarshalAs(UnmanagedType.LPWStr)] string name);
        [DllImport("StoreCppHelper.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool GetDurableAddonLicense(FileNameCallback callback);
        static FileNameCallback fileNameCallback;

        delegate void PurchaseCallback(bool result, [MarshalAs(UnmanagedType.LPWStr)] string msg);
        [DllImport("StoreCppHelper.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool RequestPurchaseApp(IntPtr hwnd, PurchaseCallback callback);
        static PurchaseCallback purchaseCallback;

        [DllImport("StoreCppHelper.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool GetAddonList(FileNameCallback callback);

        [DllImport("StoreCppHelper.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool RequestPurchaseAddon(IntPtr hwnd, [MarshalAs(UnmanagedType.LPWStr)] string itemId, PurchaseCallback callback);

        delegate void ConsumableBalanceCallback(bool resut, uint quantity, [MarshalAs(UnmanagedType.LPWStr)] string msg);
        [DllImport("StoreCppHelper.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool GetConsumableBalanceRemaining([MarshalAs(UnmanagedType.LPWStr)] string itemId, ConsumableBalanceCallback callback);
        static ConsumableBalanceCallback consumableBalanceCallback;

        [DllImport("StoreCppHelper.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool ReportConsumableFulfillment([MarshalAs(UnmanagedType.LPWStr)] string itemId, uint quantity, PurchaseCallback callback);

        [DllImport("StoreCppHelper.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool GetAddonLicense(FileNameCallback callback);


        internal static bool GetAppLicenseInformation(MainWindow window)
        {
            main = window;
            appLicenseCallback = new AppLicenseCallback(GetAppLicenseCallback);
            var ret = GetAppLicense(appLicenseCallback); 
            return ret;
        }

        static void GetAppLicenseCallback(bool isActive, bool isTrial, bool isInactive, bool isFull)
        {
            main.Dispatcher.Invoke(() =>
            {
                main.Logs("=====Get License Information=========");
                main.Logs("Active=" + isActive.ToString());
                main.Logs("Trial=" + isTrial.ToString());
                main.Logs("InActive=" + isInactive.ToString());
                main.Logs("Full=" + isFull.ToString());
            });

            // Release delegate.
            // デリゲートの解放
            var ds = appLicenseCallback.GetInvocationList();
            foreach (var d in ds)
            {
                appLicenseCallback -= (AppLicenseCallback)d;
            }

        }

        internal static bool GetDurableAddonLincenseInformation(MainWindow window)
        {
            main = window;
            fileNameCallback = new FileNameCallback(GetAddonDurableLicenseCallback);            
            var ret = GetDurableAddonLicense(fileNameCallback);
            return ret;
        }

        static void GetAddonDurableLicenseCallback(string name)
        {
            var lines = File.ReadAllLines(name);
            main.Dispatcher.Invoke(() =>
            {
                main.Logs("=====Get Durable Addon License Information=========");
                if (lines.Length == 0)
                {
                    main.Logs("Nothing Addon license");
                    return;
                }
                foreach (var line in lines)
                {
                    var items = line.Split('\t');
                    main.Logs("=====Key=" + items[0]);
                    main.Logs("SkuStoreId=" + items[1]);
                }
            });
            File.Delete(name);
            // Release delegate.
            // デリゲートの解放
            var ds = fileNameCallback.GetInvocationList();
            foreach (var d in ds)
            {
                fileNameCallback -= (FileNameCallback)d;
            }
        }

        internal static bool AppPurchase(MainWindow window)
        {
            main = window;
            
            purchaseCallback = new PurchaseCallback(AppPurchaseCallback);
            var ret = RequestPurchaseApp(System.Diagnostics.Process.GetCurrentProcess().MainWindowHandle, purchaseCallback);
            return ret;
        }

        static void AppPurchaseCallback(bool result, string msg)
        {
            main.Dispatcher.Invoke(() =>
            {
                main.Logs("=====Purchase  App==================");
                if (!result)
                    main.Logs("Error");
                main.Logs(msg);
            });
            // Release delegate.
            // デリゲートの解放
            var ds = purchaseCallback.GetInvocationList();
            foreach (var d in ds)
            {
                purchaseCallback -= (PurchaseCallback)d;
            }
        }

        internal static bool GetAddonListInformation(MainWindow window)
        {
            main = window;
            fileNameCallback = new FileNameCallback(GetAddonListCallback);
            var ret = GetAddonList(fileNameCallback);
            return ret;
        }

        static void GetAddonListCallback(string name)
        {
            var lines = File.ReadAllLines(name);
            main.Dispatcher.Invoke(() =>
            {
                main.Logs("=====Get Add-On List================");
                if (lines.Length == 0)
                {
                    main.Logs("Nothing Addon list");
                    return;
                }
                foreach (var line in lines)
                {
                    var items = line.Split('\t');
                    main.Logs("=====StoreId=" + items[0]);
                    main.Logs("Title=" + items[1]);
                    main.Logs("Price=" + items[2]);
                    main.Logs("ProductKind=" + items[3]);
                    main.SetItemId(items[0]);
                }

            });
            File.Delete(name);
            // Release delegate.
            // デリゲートの解放
            var ds = fileNameCallback.GetInvocationList();
            foreach (var d in ds)
            {
                fileNameCallback -= (FileNameCallback)d;
            }
        }

        internal static bool AddonPurchase(MainWindow window, string itemId)
        {
            main = window;

            purchaseCallback = new PurchaseCallback(AddonPurchaseCallback);
            var ret = RequestPurchaseAddon(System.Diagnostics.Process.GetCurrentProcess().MainWindowHandle, itemId,  purchaseCallback);
            return ret;
        }

        static void AddonPurchaseCallback(bool result, string msg)
        {
            main.Dispatcher.Invoke(() =>
            {
                main.Logs("=====Add-On Purchase================");
                if (!result)
                    main.Logs("Error");
                main.Logs(msg);
            });
            // Release delegate.
            // デリゲートの解放
            var ds = purchaseCallback.GetInvocationList();
            foreach (var d in ds)
            {
                purchaseCallback -= (PurchaseCallback)d;
            }
        }

        internal static bool GetConsumableBalance(MainWindow window, string itemid)
        {
            main = window;
            consumableBalanceCallback = new ConsumableBalanceCallback(GetSonsumableBalanceCallback);
            var ret = GetConsumableBalanceRemaining(itemid, consumableBalanceCallback);

            return ret;
        }

        static void GetSonsumableBalanceCallback(bool result, uint quantity, string msg)
        {
            main.Dispatcher.Invoke(()=>
            {
                main.Logs("=====Get Consumable Balance================");
                if (!result)
                {
                    main.Logs("Error");
                }
                main.Logs(msg);
                main.Logs("Remaining=" + quantity.ToString());
            });
            // Release delegate.
            // デリゲートの解放
            var ds = consumableBalanceCallback.GetInvocationList();
            foreach (var d in ds)
            {
                consumableBalanceCallback -= (ConsumableBalanceCallback)d;
            }
        }

        internal static bool ReportFulfillment(MainWindow window, string itemid, int quantity = 1)
        {
            main = window;
            purchaseCallback = new PurchaseCallback(ReportFulFillmentCallback);
            var ret = ReportConsumableFulfillment(itemid, (uint)quantity, purchaseCallback);
            return ret;
        }

        static void  ReportFulFillmentCallback(bool result, string msg)
        {
            main.Dispatcher.Invoke(() =>
            {
                main.Logs("=====Report Fulfillment================");
                if (!result)
                {
                    main.Logs("Error");
                }
                main.Logs(msg);
            });

            // Release delegate.
            // デリゲートの解放
            var ds = purchaseCallback.GetInvocationList();
            foreach (var d in ds)
            {
                purchaseCallback -= (PurchaseCallback)d;
            }
        }

        internal static bool GetAddonLincenseInformation(MainWindow window)
        {
            main = window;
            fileNameCallback = new FileNameCallback(GetAddonLicenseCallback);
            var ret = GetAddonLicense(fileNameCallback);
            return ret;
        }

        static void GetAddonLicenseCallback(string name)
        {
            var lines = File.ReadAllLines(name);
            main.Dispatcher.Invoke(() =>
            {
                main.Logs("=====Get Addon License Information=========");
                if (lines.Length == 0)
                {
                    main.Logs("Nothing Addon license");
                    return;
                }
                foreach (var line in lines)
                {
                    var items = line.Split('\t');
                    main.Logs("=====StoreId=" + items[0]);
                    main.Logs("Title=" + items[1]);
                    main.Logs("Price=" + items[2]);
                    main.Logs("ProductKind=" + items[3]);
                    main.SetItemId(items[0]);
                }
            });
            File.Delete(name);
            // Release delegate.
            // デリゲートの解放
            var ds = fileNameCallback.GetInvocationList();
            foreach (var d in ds)
            {
                fileNameCallback -= (FileNameCallback)d;
            }
        }

    }
}
