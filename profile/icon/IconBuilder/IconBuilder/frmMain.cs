using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Imaging;
using System.IO;

namespace IconBuilder
{
    public partial class frmMain : Form
    {
        string path = "";
        public frmMain()
        {
            InitializeComponent();
        }


        /// <summary>
        /// 获取等比例缩放图片的方法
        /// </summary>
        /// <param name="imgPath">待缩放图片路径</param>
        /// <param name="savePath">缩放图片保存路径</param>
        /// <param name="format">缩放图片保存的格式</param>
        /// <param name="scaling">要保持的宽度或高度</param>
        /// <returns></returns>
        public bool GetThumbnail(string imgPath, string savePath, ImageFormat format, int scaling)
        {
            try
            {
                using (Bitmap myBitmap = new Bitmap(imgPath))
                {
                    using (Image myThumbnail = myBitmap.GetThumbnailImage(scaling, scaling, () => { return false; }, IntPtr.Zero))
                    {
                        myThumbnail.Save(savePath, format);
                    }
                }
                return true;
            }
            catch
            {
                return false;
            }

        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "PNG Image|*.png";
            openFileDialog1.Title = "打开";
            openFileDialog1.Multiselect = false;
            openFileDialog1.CheckFileExists = false;
            openFileDialog1.FileName = string.Empty;
            openFileDialog1.ShowDialog();
            txtPath.Text = openFileDialog1.FileName;
            path = openFileDialog1.FileName.Substring(0, openFileDialog1.FileName.Length - openFileDialog1.SafeFileName.Length);
            path = path + DateTime.Now.ToString("yyyyMMddhhmmss") + "\\";
            //txtPath.Text = path;
        }

        private void btnBuilder_Click(object sender, EventArgs e)
        {
            if (txtPath.Text.Equals("") || path.Equals(""))
                return;
            if (Directory.CreateDirectory(path) != null)
            {
                bool flag = true;
                flag = flag && GetThumbnail(txtPath.Text, path + "iTunesArtwork", ImageFormat.Png, 512);//iTunesArtwork
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon@2x.png", ImageFormat.Png, 114);//Application Icon for iPhone (retina display)
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon-72@2x.png", ImageFormat.Png, 114);//Application Icon for the new iPad (retina display)
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon-Small-50@2x.png", ImageFormat.Png, 100);//Settings/Spotlight icon for iPad
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon-Small@2x.png", ImageFormat.Png, 58);//Settings/Spotlight icon for iPhone (retina display)
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon.png", ImageFormat.Png, 57);//Application Icon icon for iPhone
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon-Small-50.png", ImageFormat.Png, 50);//Settings/Spotlight icon for iPad
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon-Small.png", ImageFormat.Png, 29);//Settings/Spotlight icon for iPhone
				flag = flag && GetThumbnail(txtPath.Text, path + "Icon-28.png", ImageFormat.Png, 28);//Settings/Spotlight icon for iPhone
				flag = flag && GetThumbnail(txtPath.Text, path + "Icon-108.png", ImageFormat.Png, 108);//Settings/Spotlight icon for iPhone
				flag = flag && GetThumbnail(txtPath.Text, path + "Icon-16.png", ImageFormat.Png, 16);//Settings/Spotlight icon for iPhone
				flag = flag && GetThumbnail(txtPath.Text, path + "Icon-120.png", ImageFormat.Png, 120);//Settings/Spotlight icon for iPhone
				flag = flag && GetThumbnail(txtPath.Text, path + "Icon-64.png", ImageFormat.Png, 64);//Settings/Spotlight icon for iPhone
				flag = flag && GetThumbnail(txtPath.Text, path + "Icon-75.png", ImageFormat.Png, 75);//Settings/Spotlight icon for iPhone
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon-29.png", ImageFormat.Png, 29);//Settings/Spotlight icon for iPhone
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon-40.png", ImageFormat.Png, 40);//Settings/Spotlight icon for iPhone
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon-50.png", ImageFormat.Png, 50);//Settings/Spotlight icon for iPhone
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon-57.png", ImageFormat.Png, 57);//Settings/Spotlight icon for iPhone
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon-58.png", ImageFormat.Png, 58);//Settings/Spotlight icon for iPhone
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon-72.png", ImageFormat.Png, 72);//Application Icon for the iPad
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon-76.png", ImageFormat.Png, 76);//Application Icon for the iPad
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon-80.png", ImageFormat.Png, 80);//Settings/Spotlight icon for iPhone
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon-100.png", ImageFormat.Png, 100);//Settings/Spotlight icon for iPhone
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon-114.png", ImageFormat.Png, 114);//Settings/Spotlight icon for iPhone
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon-144.png", ImageFormat.Png, 144);//Settings/Spotlight icon for iPhone
                flag = flag && GetThumbnail(txtPath.Text, path + "Icon-152.png", ImageFormat.Png, 152);//Settings/Spotlight icon for iPhone
                if (flag)
                {
                    MessageBox.Show("ICON生成完毕！", "成功", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    System.Diagnostics.Process.Start("Explorer.exe", path);
                }
                else
                {
                    MessageBox.Show("出错啦！", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

    }
}
