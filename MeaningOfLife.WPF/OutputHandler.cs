using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Windows.Threading;

using ChatClient;


namespace ChatClient
{
    public class OutputHandler
    {
        private FileLogger l = new FileLogger(Config.logFileName);

        private Signin signinWindow;
        private Signup signupWindow;
        private ChatClient.MainWindow mainWindow;

        public void setSigninWindow(Signin w)
        {
            signinWindow = w;
        }

        public void setSignupWindow(Signup w)
        {
            signupWindow = w;
        }

        public void setMainWindow(ChatClient.MainWindow w)
        {
            mainWindow = w;
        }


        private string file;
        public OutputHandler(string file)
        {
            this.file = file;
        }
        public void handle()
        {
            while (true)
            {
                if (File.Exists(this.file))
                {
                    string jsonStr = System.IO.File.ReadAllText(this.file);
                    var resp = JsonConvert.DeserializeObject<dynamic>(jsonStr);
                    Console.WriteLine("FROM OUTPUT: ");
                    Console.Write(resp);
                    File.Delete(this.file);
                    callForm(resp);
                }
                Thread.Sleep(1000);
            }
        }


        // call with json 
        public void callForm(dynamic resp)
        {

            string type = resp.type;

            if ("authorize".Equals(type))
            {
                bool success = resp.success;
                l.log("new auth: " + success);
                if (success)
                {
                    l.log("success auth");
                    signinWindow.dispatchOpenMainWindow();
                }
                else
                {
                    l.log("bad data for user");
                }
            }

            // пришло новое сообщение - отображаем в списке сообщений
            else if ("message".Equals(type))
            {
                l.log("new message");
                Entities.MessageResponse m = Utils.dynamicToMessageResponse(resp);
                while (mainWindow == null)
                {
                    l.log("another sleep");
                    Thread.Sleep(100);
                }
                // show
                Dispatchers.dispatchShowMessage(m, mainWindow);
                // serialize
            }

            else if ("register".Equals(type))
            {
                l.log("registration answer");
                bool success = resp.success;
                if (success)
                {
                    while (signupWindow == null)
                    {
                        l.log("another sleep");
                        Thread.Sleep(100);
                    }
                    signupWindow.dispatchOpenSigninWindow();
                }
                else
                {
                    l.log("user already exists");
                }
            }
            // рендерит в MainWindow список каналов
            else if ("get_channel".Equals(type))
            {
                JArray channels = resp.channels;
                List<dynamic> chList = channels.ToObject<List<dynamic>>();
                l.log("received channels:  " + channels.ToString());

                JArray userCounts = resp.user_counts;
                List<Int32> counts = userCounts.ToObject<List<Int32>>();
                l.log("received counts: " + userCounts.ToString());
                Dispatchers.dispatchGetChannels(chList, counts, mainWindow);
            }

            else if ("new_channel".Equals(type))
            {
                Entities.NewChannelResponse m = Utils.dynamicToNewChannelResponse(resp);
                Dispatchers.dispatchCreateChannel(m, mainWindow);
            }
            else if ("get_channel_messages".Equals(type))
            {
                JArray array = resp.messages;
                List<dynamic> ll = array.ToObject<List<dynamic>>();
                string ch = resp.channel;

                l.log("received messages for channel " + ch + " are " + array.ToString());
                // show
                Dispatchers.dispatchShowChannelMessages(ch, ll, mainWindow);
                // serialize
            }
            else if ("get_online_users".Equals(type))
            {
                JArray array = resp.users;
                Entities.GetOnlineUsers obj = new Entities.GetOnlineUsers();
                obj.sender = resp.sender;
                obj.users = array.ToObject<List<string>>();
                obj.type = resp.type;
                Dispatchers.dispatchGetOnlineUsers(obj, mainWindow);
            }

            else if ("add_user".Equals(type))
            {
                Entities.AddUser evnt = new Entities.AddUser();
                evnt.sender = resp.sender;
                evnt.user = resp.user;
                evnt.channel = resp.channel;
                evnt.success = resp.success;
                evnt.type = resp.type;


                if (evnt.sender == Config.userName)
                {
                    // notify about successful or not adding	
                    // display info about adding (using add user menu)
                    Dispatchers.dispatchNotifyOnAddingUserResponse(evnt.user, evnt.channel, evnt.success, mainWindow);
                }
                // evnt.success apriori true here
                else
                {
                    // user have been added
                    if (evnt.user == Config.userName)
                    {
                        // show new channel
                        mainWindow.globalChannel.generateChannelRequest(evnt.channel);
                    }
                    // other members of channel (exclude admin)
                    else
                    {
                        // update channel data
                        // +1 channel's members displayed
                        Dispatchers.dispatchIncrementChannelMembersView(evnt.channel, mainWindow);
                    }
                }
            }
            else if ("get_channel_users".Equals(type))
            {
                JArray array = resp.users;
                Entities.GetChannelUsers obj = new Entities.GetChannelUsers();
                obj.sender = resp.sender;
                obj.channel = resp.channel;
                obj.users = array.ToObject<List<Entities.User>>();
                obj.type = resp.type;
                Dispatchers.dispatchGetChannelUsers(obj, mainWindow);
            }
        }

    }
}
