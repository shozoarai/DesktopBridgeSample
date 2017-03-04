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

namespace WpfAppUsingWinRT
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

        /// <summary>
        /// マネージ コードでFilePicker を開きます
        /// using OpenFilePicker by Managed Code.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private async void btnOpenPicker_Click(object sender, RoutedEventArgs e)
        {
            var picker = new Windows.Storage.Pickers.FileOpenPicker();

            WinRtHelper.InitializeWithWindow(picker);

            picker.FileTypeFilter.Add(".txt");
            picker.FileTypeFilter.Add(".doc");
            picker.FileTypeFilter.Add(".pptx");

            var file = await picker.PickSingleFileAsync();
            if (file == null)
            {
            }
            else
            {
                UpdateLog(file.Name);
            }

        }

        /// <summary>
        /// DLL を使用して開きます
        /// Using Dynamic Link Library
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnOpenNative_Click(object sender, RoutedEventArgs e)
        {
            NaitiveHelper.OpenPicker(this);
        }

        internal void UpdateLog(string msg)
        {
            txtOut.Text += msg + "\n";
        }

    }
}
