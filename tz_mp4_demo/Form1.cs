using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Threading;

namespace tz_mp4_demo
{
    public partial class Form1 : Form
    {

        Int32 m_lPlayId = 0; //播放流ID
        public Form1()
        {
            InitializeComponent();
        }

        [DllImport(@"..\..\..\x64\Debug\tz_mp4.dll")]
        extern static bool open_mp4(ref Int32 lPlayID,IntPtr sFilePath,Int32 w,Int32 h,Int32 frameRate);

        [DllImport(@"..\..\..\x64\Debug\tz_mp4.dll")]
        extern static bool play_start(Int32 lPlayID, IntPtr hWnd);


        private void play_Click(object sender, EventArgs e)
        {
            IntPtr filePath = IntPtr.Zero;
            bool ret = open_mp4(ref m_lPlayId,filePath,1920,1080,50);

            IntPtr hwnd = pictureBox1.Handle;

            ret = play_start(m_lPlayId, hwnd);
        }
    }
}
