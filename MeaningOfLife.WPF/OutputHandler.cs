using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace MeaningOfLife.WPF
{
    class OutputHandler
    {
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
                }
                Thread.Sleep(1000);
            }
        }
    }
}
