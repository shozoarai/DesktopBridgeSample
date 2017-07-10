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
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void btnQueryLicense_Click(object sender, RoutedEventArgs e)
        {
            StoreHelper.GetAppLicenseInformation(this);
        }

        private void btnQueryAddonLicense_Click(object sender, RoutedEventArgs e)
        {
            StoreHelper.GetDurableAddonLincenseInformation(this);
        }

        private void btnPurchase_Click(object sender, RoutedEventArgs e)
        {
            StoreHelper.AppPurchase(this);
        }

        private void btnGetAddOnList_Click(object sender, RoutedEventArgs e)
        {
            StoreHelper.GetAddonListInformation(this);
        }

        private void btnAddOn_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrEmpty(txtAddOnId.Text))
            {
                MessageBox.Show("Please input Add-On StoreId");
                return;
            }
            StoreHelper.AddonPurchase(this, txtAddOnId.Text);
        }

        private void btnUserCollection_Click(object sender, RoutedEventArgs e)
        {
            StoreHelper.GetAddonLincenseInformation(this);
        }

        private void btnBalance_Click(object sender, RoutedEventArgs e)
        {
            StoreHelper.GetConsumableBalance(this, txtAddOnId.Text);
        }

        private void btnFulfillment_Click(object sender, RoutedEventArgs e)
        {
            var quantity = int.Parse(txtQuantity.Text);
            StoreHelper.ReportFulfillment(this, txtAddOnId.Text, quantity);
        }

        internal void SetItemId(string id)
        {
            txtAddOnId.Text = id;
        }
        internal void Logs(string msg)
        {
            txtOut.Text += msg + "\n";
        }

    }
}
