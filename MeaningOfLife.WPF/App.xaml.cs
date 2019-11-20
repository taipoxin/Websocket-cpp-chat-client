using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;

using MeaningOfLife.Cpp.CLI;
namespace MeaningOfLife.WPF
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        static Logic wrapper = new Logic();
        public static Thread bThread;

        public static Thread newThread()
        {
            ThreadStart cppHandler = new ThreadStart(wrapper.wsCoreLoop);
            Thread cppHandlerT = new Thread(cppHandler);
            cppHandlerT.IsBackground = true;
            return cppHandlerT;
        }

        public App()
        {
            var pathLib = "MeaningOfLife.Cpp.dll";
            Logic.InitializeLibrary(pathLib);
            // C# => C++
            ThreadStart cppHandler = new ThreadStart(wrapper.wsCoreLoop);
            Thread cppHandlerT = new Thread(cppHandler);
            cppHandlerT.IsBackground = true;
            cppHandlerT.Start();
            bThread = cppHandlerT;

            
        }
    }
}
