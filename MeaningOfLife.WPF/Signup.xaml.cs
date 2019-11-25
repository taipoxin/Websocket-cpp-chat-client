using System;
using System.Collections.Generic;
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
using System.Windows.Shapes;
using MeaningOfLife.Cpp.CLI;
using Newtonsoft.Json;

namespace ChatClient
{
	/// <summary>
	/// Логика взаимодействия для Signup.xaml
	/// </summary>
	public partial class Signup: Window
	{
		public Signup()
		{
			InitializeComponent();
		}

        WS_Caller caller;
        OutputHandler csharpOutputHandler;
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

		private void Window_Loaded(object sender, RoutedEventArgs e)
		{
			//l.logg("", false);
			if (isPosition)
			{
				this.Left = leftPos;
				this.Top = topPos;
			}
		}

        public void setCaller(WS_Caller c)
        {
            this.caller = c;
        }

        public void setHandler(OutputHandler h)
        {
            this.csharpOutputHandler = h;
        }


        private Entities.RegRequest createRegRequest(string user, string email, string password)
		{
			Entities.RegRequest r = new Entities.RegRequest();
			r.type = "register";
			r.user = user;
			r.email = email;
			r.password = password;
			return r;
		}

		// return success
		private bool registerFromForm()
		{
			string user = LoginBox.Text;
			string email = EmailBox.Text;
			string pass = PasswordBox.Password;
			string cpass = ConfirmBox.Password;

			if (!pass.Equals(cpass))
			{
				return false;
			}
			string jsonReq = JsonConvert.SerializeObject(createRegRequest(user, email, pass));

            // пытаемся отправить сообщение об регистрации
            if (caller != null)
            {
                l.log("sending auth request");
                caller.send(jsonReq);
                return true;
            }
            return false;

		}
        
		public void dispatchOpenSigninWindow()
		{
			Dispatcher.BeginInvoke(new ThreadStart(delegate {
				openSigninWindow();
			}));
		}


		private void openSigninWindow()
		{
            Signin w = csharpOutputHandler.signinWindow;
			w.SetWindowPositions(this.Left, this.Top);
			// показываем новое окно
			w.Show();
            w.setCaller(caller);
            w.setHandler(csharpOutputHandler);
  
            // закрываем текущее окно логина
            this.Visibility = Visibility.Hidden;

		}

		// Cancel
		private void Button_Click(object sender, RoutedEventArgs e)
		{
			openSigninWindow();
		}

        void on_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            Console.WriteLine("Closing called");
            try
            {
                if (csharpOutputHandler != null)
                {
                    if (csharpOutputHandler.signinWindow != null)
                        csharpOutputHandler.signinWindow.Close();
                    if (csharpOutputHandler.mainWindow != null)
                        csharpOutputHandler.mainWindow.Close();
                }
            }
            catch (InvalidOperationException)
            {

            }
        }


        // Sign up
        private void Button_Click_1(object sender, RoutedEventArgs e)
		{

			bool res = registerFromForm();
			if (res)
			{
				l.log("try to register");
			}
			else
			{
				l.log("bad data for register");
			}

		}

	}
}
