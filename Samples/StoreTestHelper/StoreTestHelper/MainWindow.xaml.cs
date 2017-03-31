using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace StoreTestHelper
{
    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private async void btnQueryLicense_Click(object sender, RoutedEventArgs e)
        {
            var result = await StoreHelper.GetLicense();
            Logs("=====Get License Information=========");
            Logs("Active=" + result.IsActive.ToString());
            Logs("Inactive=" + result.IsInactive.ToString());
            Logs("Trial=" + result.IsTrial.ToString());
            Logs("Full=" + result.IsFull.ToString());
            Logs("Price=" + result.Price);
        }

        private async void btnPurchase_Click(object sender, RoutedEventArgs e)
        {
            var result = await StoreHelper.Purchase();
            Logs("=====Purchase  App==================");
            if (!result.Item1)
                Logs("Error");
            Logs(result.Item2);
        }

        private async void btnGetAddOnList_Click(object sender, RoutedEventArgs e)
        {
            var result = await StoreHelper.GetAddOnList();
            Logs("=====Get Add-On List================");
            if (!result.Item1)
            {
                Logs("Error");
                Logs(result.Item3);
                return;
            }
            foreach (var item in result.Item2)
            {
                Logs("StoreId=" + item.StoreId);
                Logs("Title=" + item.Title);
                Logs("Price=" + item.Price);
                txtAddOnId.Text = item.StoreId;
            }
        }

        private async void btnAddOn_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrEmpty(txtAddOnId.Text))
            {
                MessageBox.Show("Please input Add-On StoreId");
                return;
            }
            var storeId = txtAddOnId.Text;
            var result = await StoreHelper.PurchaseAddOn(storeId);
            Logs("=====Add-On Purchase================");
            if (!result.Item1)
                Logs("Error");
            Logs(result.Item2);
        }

        void Logs(string msg)
        {
            txtOut.Text += msg + "\n";
        }

    }
}
