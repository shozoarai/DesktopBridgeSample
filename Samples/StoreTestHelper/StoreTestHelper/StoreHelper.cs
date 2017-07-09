using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Windows.Services.Store;

namespace StoreTestHelper
{
    internal struct LicenseInformation
    {

        internal bool IsActive;
        internal bool IsTrial;
        internal bool IsFull;
        internal bool IsInactive;
        internal string Price;
        internal List<AddOnLicenseInformation> AddOns;
    }

    internal struct AddOnLicenseInformation
    {
        internal string Key;
        internal string SkuStoreId;
        internal DateTime ExpirationDate;
    }

    internal struct Product
    {
        internal string StoreId;
        internal string Title;
        internal string Price;
        internal string ProductKind;    // Add Product Kind.
    }

    static class StoreHelper
    {
        /// <summary>
        /// Get StoreContext with InitializeWithWindow.
        /// InitializeWithWindow メソッドを呼び出して、StoteContext を取得します
        /// </summary>
        /// <returns></returns>
        static StoreContext GetContext()
        {
            var context = StoreContext.GetDefault();
            WinRtHelper.InitializeWithWindow(context);
            return context;
        }

        /// <summary>
        /// Get license information
        /// ライセンス情報を取得します
        /// </summary>
        /// <returns></returns>
        internal static async Task<LicenseInformation> GetLicense()
        {
            var context = StoreContext.GetDefault();

            var licenseResult = new LicenseInformation();
            licenseResult.AddOns = new List<AddOnLicenseInformation>();
            // Get Price
            // 価格の取得
            var storeProductResult = await context.GetStoreProductForCurrentAppAsync();
            if (storeProductResult.ExtendedError == null)
                licenseResult.Price = storeProductResult.Product.Price.FormattedPrice;
            // Get App License
            // アプリ ライセンスの取得
            var storeLicense = await context.GetAppLicenseAsync();
            licenseResult.IsActive = storeLicense.IsActive;
            licenseResult.IsTrial = storeLicense.IsTrial;
            licenseResult.IsInactive = !licenseResult.IsActive;
            licenseResult.IsFull = !licenseResult.IsTrial;
            // Get Durable Add-on information
            // 永続アドオン情報の取得
            var addOnList = storeLicense.AddOnLicenses;
            foreach (var i in addOnList)
            {
                var addOnLicense = new AddOnLicenseInformation();
                addOnLicense.Key = i.Key;
                addOnLicense.SkuStoreId = i.Value.SkuStoreId;
                addOnLicense.ExpirationDate = i.Value.ExpirationDate.DateTime;
                licenseResult.AddOns.Add(addOnLicense);
            }

            return licenseResult;
        }

        /// <summary>
        /// Purchase App on trial app.
        /// 試用版アプリを購入済みにします
        /// </summary>
        /// <param name="isForce"></param>
        /// <returns></returns>
        internal async static Task<Tuple<bool, string>> Purchase()
        {
            var context = GetContext();
            // Get App product
            // アプリというプロダクトの取得
            var storeProductResult = await context.GetStoreProductForCurrentAppAsync();
            if (storeProductResult.ExtendedError != null)
                return new Tuple<bool, string>(false, "Error:" + storeProductResult.ExtendedError.Message);
            // Get App license, then check App license.
            // アプリ ライセンスの取得と確認
            var storeLicense = await context.GetAppLicenseAsync();
            if (storeLicense.IsActive)
                return new Tuple<bool, string>(false, "You already bought this app and have a fully-licensed version.");
            // Purchase App license.
            // アプリ ライセンスの購入
            StorePurchaseResult storePurchaseResult = await storeProductResult.Product.RequestPurchaseAsync();//StoreProductクラス
            if (storePurchaseResult.ExtendedError != null)
            {
                return new Tuple<bool, string>(false, "Error:" + storePurchaseResult.ExtendedError.Message);
            }
            // Check purchase result.
            // 購入結果の確認
            string msg = "";
            bool isPerchased = false;
            switch (storePurchaseResult.Status)
            {
                case StorePurchaseStatus.AlreadyPurchased:
                    isPerchased = false;
                    msg = "You already bought this app and have a fully-licensed version.";
                    break;

                case StorePurchaseStatus.Succeeded:
                    isPerchased = true;
                    msg = "Succeeded";
                    break;

                case StorePurchaseStatus.NotPurchased:
                    isPerchased = false;
                    msg = "Product was not purchased, it may have been canceled.";
                    break;

                case StorePurchaseStatus.NetworkError:
                    isPerchased = false;
                    msg = "Product was not purchased due to a Network Error.";
                    break;

                case StorePurchaseStatus.ServerError:
                    isPerchased = false;
                    msg = "Product was not purchased due to a Server Error.";
                    break;

                default:
                    isPerchased = false;
                    msg = "Product was not purchased due to an Unknown Error.";
                    break;
            }

            return new Tuple<bool, string>(isPerchased, msg);
        }

        /// <summary>
        /// Puchase Add-on
        /// アドオンの購入
        /// </summary>
        /// <param name="itemId"></param>
        /// <returns></returns>
        internal async static Task<Tuple<bool, string>> PurchaseAddOn(string itemId)
        {
            var context = GetContext();
            // Puchase Add-On.
            // アドオンの購入
            var storePurchaseResult = await context.RequestPurchaseAsync(itemId);
            if (storePurchaseResult.ExtendedError != null)
            {
                return new Tuple<bool, string>(false, "Error:" + storePurchaseResult.ExtendedError.Message);
            }
            // Check purchase result.
            // 購入結果の確認
            string msg = "";
            bool isPerchased = false;
            switch (storePurchaseResult.Status)
            {
                case StorePurchaseStatus.AlreadyPurchased:
                    isPerchased = false;
                    msg = "You already bought this AddOn.";
                    break;

                case StorePurchaseStatus.Succeeded:
                    isPerchased = true;
                    msg = "Succeeded";
                    break;

                case StorePurchaseStatus.NotPurchased:
                    isPerchased = false;
                    msg = "AddOn Product was not purchased, it may have been canceled.";
                    break;

                case StorePurchaseStatus.NetworkError:
                    isPerchased = false;
                    msg = "AddOn Product was not purchased due to a network error.";
                    break;

                case StorePurchaseStatus.ServerError:
                    isPerchased = false;
                    msg = "AddOn Product was not purchased due to a server error.";
                    break;

                default:
                    isPerchased = false;
                    msg = "AddOn Product was not purchased due to an unknown error.";
                    break;
            }

            return new Tuple<bool, string>(isPerchased, msg);
        }

        /// <summary>
        /// Get Add-On list.
        /// アドオンのリストを取得
        /// </summary>
        /// <returns></returns>
        internal static async Task<Tuple<bool, List<Product>, string>> GetAddOnList()
        {
            var context = StoreContext.GetDefault();
            // Set filters.
            // フィルターの設定
            var filter = new string[] {
                "Durable",
                "Consumable",
                "UnmanagedConsumable"
            };
            // Get Add-On products.
            // アドオンの取得
            var storeProductQueryResult = await context.GetAssociatedStoreProductsAsync(filter);
            if (storeProductQueryResult.ExtendedError != null)
            {
                return new Tuple<bool, List<Product>, string>(false, null, "Error:" + storeProductQueryResult.ExtendedError.Message);
            }
            // Check Add-On product count.
            // アドオンのチェック
            if (storeProductQueryResult.Products.Count == 0)
            {
                return new Tuple<bool, List<Product>, string>(false, null, "AdOns is nothing");
            }
            // Create Add-On collection.
            // アドオンのコレクションの作成
            var products = new List<Product>();
            foreach (var item in storeProductQueryResult.Products)
            {
                var product = new Product()
                {
                    StoreId = item.Value.StoreId,
                    Title = item.Value.Title,
                    Price = item.Value.Price.FormattedPrice,
                    ProductKind = item.Value.ProductKind    // Add Product Kind.
                };
                products.Add(product);
            }

            return new Tuple<bool, List<Product>, string>(true, products, "");
        }

        /// <summary>
        /// Get Consumable Balance
        /// Consumable Balance を取得します
        /// </summary>
        /// <param name="itemId"></param>
        /// <returns></returns>
        internal static async Task<Tuple<bool, long, string>> GetBalance(string itemId)
        {
            var context = StoreContext.GetDefault();
            // Get CosumableBalance
            // ConsumableBalance を取得します。
            var consumableResult = await context.GetConsumableBalanceRemainingAsync(itemId);

            long balance = 0;
            bool result = false;
            string msg = "";
            string extendedError = "";
            if (consumableResult.ExtendedError != null)
            {
                extendedError = consumableResult.ExtendedError.Message;
            }
            // Check CosumableBalance Result
            switch (consumableResult.Status)
            {
                case StoreConsumableStatus.Succeeded:
                    msg = "Remaining balance: " + consumableResult.BalanceRemaining.ToString();
                    balance = consumableResult.BalanceRemaining;
                    result = true;
                    break;

                case StoreConsumableStatus.NetworkError:
                    msg = "Could not retrieve balance due to a network error. " +
                        "ExtendedError: " + extendedError;
                    break;

                case StoreConsumableStatus.ServerError:
                    msg = "Could not retrieve balance due to a server error. " +
                        "ExtendedError: " + extendedError;
                    break;

                default:
                    msg = "Could not retrieve balance due to an unknown error. " +
                        "ExtendedError: " + extendedError;
                    break;
            }
            return new Tuple<bool, long, string>(result, balance, msg);
        }

        internal static async Task<Tuple<bool, string>> FulfillmentReport(string itemId, int quantity = 1)
        {
            var context = StoreContext.GetDefault();
            // Report Fulfillment
            // Fulfillment を報告します。
            var trackId = Guid.NewGuid();
            var consumableResult = await context.ReportConsumableFulfillmentAsync(itemId, (uint)quantity, trackId);

            bool result = false;
            string msg = "";
            string extendedError = "";
            if (consumableResult.ExtendedError != null)
            {
                extendedError = consumableResult.ExtendedError.Message;
            }
            // Check CosumableBalance Result
            switch (consumableResult.Status)
            {
                case StoreConsumableStatus.Succeeded:
                    result = true;
                    msg = "The fulfillment was successful. " +
                        $"Remaining balance: {consumableResult.BalanceRemaining}";
                    break;

                case StoreConsumableStatus.InsufficentQuantity:
                    msg = "The fulfillment was unsuccessful because the remaining " +
                        $"balance is insufficient. Remaining balance: {consumableResult.BalanceRemaining}";
                    break;

                case StoreConsumableStatus.NetworkError:
                    msg = "The fulfillment was unsuccessful due to a network error. " +
                        "ExtendedError: " + extendedError;
                    break;

                case StoreConsumableStatus.ServerError:
                    msg = "The fulfillment was unsuccessful due to a server error. " +
                        "ExtendedError: " + extendedError;
                    break;

                default:
                    msg = "The fulfillment was unsuccessful due to an unknown error. " +
                        "ExtendedError: " + extendedError;
                    break;
            }

            return new Tuple<bool, string>(result, msg);
        }

    }
}
