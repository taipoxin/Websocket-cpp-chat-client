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
using System.Threading;
using System.Windows.Threading;

namespace MeaningOfLife.WPF
{
    using Cpp.CLI;
    using Microsoft.Win32;
    using System.Threading;

    public partial class MainWindow : Window
    {
        Logic wrapper = new Logic();
        WS_Caller caller = new WS_Caller("input.txt", "ws://echo.websocket.org");

        public MainWindow()
        {
            InitializeComponent();
            var pathLib = "MeaningOfLife.Cpp.dll";
            Logic.InitializeLibrary(pathLib);
            ThreadStart threadDelegate = new ThreadStart(wrapper.wsCoreLoop);
            Thread newThread = new Thread(threadDelegate);
            newThread.Start();

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            FileLogger logger = new FileLogger("logs.txt");
            
            //caller.send("init:::ws://echo.websocket.org");
            //Thread.Sleep(3000);
            string j = @"
            {
              ""type"": ""authorize"",
              ""user"": ""username"",
              ""password"": ""12345""
            }"; 
            caller.send(j);
            logger.log("test лог");
            
            /*
            string aa = "Дарова с++";
            string res = wrapper.Get(aa);
            Console.WriteLine(res);
            MessageBox.Show("The answer is " + res);
            */
           

            
        }
    }
}
