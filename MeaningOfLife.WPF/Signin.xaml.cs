﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
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
using Newtonsoft.Json;

using MeaningOfLife.Cpp.CLI;

namespace ChatClient
{
	/// <summary>
	/// Логика взаимодействия для Startup.xaml
	/// </summary>
	public partial class Signin: Window
	{

        public static WS_Caller caller;
        OutputHandler csharpOutputHandler;

        public Signin()
		{
			InitializeComponent();
            //caller = new WS_Caller("input.txt", "ws://echo.websocket.org");
            caller = new WS_Caller("input.txt", "ws://localhost:443");

            MainWindow mw = new MainWindow();
            Signup sw = new Signup();
            csharpOutputHandler = new OutputHandler("output.txt");
            csharpOutputHandler.setSigninWindow(this);
            csharpOutputHandler.setMainWindow(mw);
            csharpOutputHandler.setSignupWindow(sw);

            // C++ => C#
            ThreadStart csharpHandler = new ThreadStart(csharpOutputHandler.handle);
            Thread csharpHandlerT = new Thread(csharpHandler);
            csharpHandlerT.IsBackground = true;
            csharpHandlerT.Start();
        }

		//private WsController wsController;
		private FileLogger l = new FileLogger(Config.logFileName);

		private double leftPos;
		private double topPos;
		private bool isPosition = false;

		public void SetWindowPositions(double left, double top)
		{
			leftPos = left;
			topPos = top;
			isPosition = true;
		}

		private double getCenter(double resolution, double actual)
		{
			return (resolution - actual) / 2;
		}

		private void Window_Loaded(object sender, RoutedEventArgs e)
		{
			if (isPosition)
			{
				this.Left = leftPos;
				this.Top = topPos;
			}
			// первый запуск, надо центрировать
			else
			{
				l.logg("", false);
				this.Top = getCenter(SystemParameters.PrimaryScreenHeight, ActualHeight);
				this.Left= getCenter(SystemParameters.PrimaryScreenWidth, ActualWidth);
			}

			Visibility = Visibility.Visible;
		}  
        
		public void setCaller(WS_Caller c)
		{
			caller = c;
		}

		public void setHandler(OutputHandler h)
		{
			this.csharpOutputHandler = h;
		}

        void on_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            Console.WriteLine("Closing called");
            try
            {
                if (csharpOutputHandler != null)
                {
                    if (csharpOutputHandler.signupWindow != null)
                        csharpOutputHandler.signupWindow.Close();
                    if (csharpOutputHandler.mainWindow != null)
                        csharpOutputHandler.mainWindow.Close();
                }
            }
            catch(InvalidOperationException)
            {

            }
        }



        public void dispatchOpenMainWindow()
		{
			Dispatcher.BeginInvoke(new ThreadStart(delegate
			{
				openMainWindow();
			}));
		}


		public void openMainWindow()
		{
            MainWindow w = csharpOutputHandler.mainWindow;
			w.setCaller(caller);
			w.setHandler(csharpOutputHandler);

            w.Show();
            this.Visibility = Visibility.Hidden;

		}

		private void openSignUpWindow()
		{
            Signup w = csharpOutputHandler.signupWindow;
            w.SetWindowPositions(this.Left, this.Top);
            w.setCaller(caller);
            w.setHandler(csharpOutputHandler);
            w.Show();
            this.Visibility = Visibility.Hidden;
		}

		private Entities.AuthRequest createRequest(string user, string password)
		{
			Entities.AuthRequest r = new Entities.AuthRequest();
			r.type = "authorize";
			r.user = user;
			r.password = password;
			return r;
		}

		// Sign in
		private void Button_Click(object sender, RoutedEventArgs e)
		{
			// пока что используется как наводка на использование backend
			if (RememberCheck.IsChecked != null && (bool)RememberCheck.IsChecked)
			{
				string u = UserBox.Text;
				Config.userName = u;
				string p = PasswordBox.Password;
				string jsonReq = JsonConvert.SerializeObject(createRequest(u, p));
                // пытаемся отправить сообщение об авторизации
                caller.send(jsonReq);
            }
            else
			{
				string u = UserBox.Text;
				if (u == "test1")
				{
					// метод первого теста

				}
				openMainWindow();
			}
		}
		// Create account
		private void Label_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
		{
			openSignUpWindow();
		}


	}

	
}
