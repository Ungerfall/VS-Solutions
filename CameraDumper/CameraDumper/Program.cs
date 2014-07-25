using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace CameraDumper
{
    sealed class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            bool check = false;
            if (check == true)
            {
                Parser("D:\\Dlink_DCS-2130_dump.dat");
            }
            else
            {
                p_Start().Wait();
            }
        }
        static async Task p_Start()
        {
            using (var client = new WebClient())
            {
                int j = 0;
                client.Proxy = null;
                var stream = client.OpenRead(new Uri("http://80.237.15.147:9000/?type:stream"));
                if (stream != null)
                {
                    while (true)
                    {
                        //using (var _file = File.Create("D:\\Current\\C, C++, C#\\CameraDumper\\CameraDumper\\temp\\JPG_" + j.ToString() + ".jpg"))
                        using (var _file = File.Create("D:\\Current\\C, C++, C#\\CameraDumper\\CameraDumper\\temp\\JPG_" + j.ToString() + ".jpg"))
                        {
                            var buffer = new byte[1024];
                            int size = 0;
                            string str = "";
                            string key_str = "Content-Length: ";
                            do
                            {
                                var readed = await stream.ReadAsync(buffer, size, buffer.Length - size);
                                size += readed;
                                Array.Resize(ref buffer, size);
                                str = System.Text.Encoding.Default.GetString(buffer);
                            }
                            while (str.IndexOf(key_str) == -1);
                            int offset = str.IndexOf(key_str) + key_str.Length + 9;
                            await _file.WriteAsync(buffer, offset, buffer.Length - offset);
                            string parse_string = str.Substring(str.IndexOf(key_str) + key_str.Length, 7);
                            int content_length = Int32.Parse(parse_string);
                            Array.Resize(ref buffer, content_length);
                            Array.Clear(buffer, 0, buffer.Length);
                            int length = 0;
                            while (length < content_length - _file.Length)
                            {
                                length += await stream.ReadAsync(buffer, length, content_length - length);
                            }
                            await _file.WriteAsync(buffer, 0, length);
                        }
                        j++;
                    }
                }
            }
        }

        static void Parser(string filepath)
        {
            using (BinaryReader stream = new BinaryReader(File.Open(filepath, FileMode.Open)))
            {
                while (stream.BaseStream.Position != stream.BaseStream.Length)
                {
                    var buffer = new byte[0];
                    int size = 0;
                    string str = "";
                    string key_str = "Content-Length";
                    do
                    {
                        size += 1024;
                        Array.Resize(ref buffer, size);
                        buffer = stream.ReadBytes(size);
                        str = System.Text.Encoding.Default.GetString(buffer);
                    }
                    while (str.IndexOf("X-Zoom") == 0);
                    string parse_string = str.Substring(str.IndexOf(key_str) + (key_str + ": ").Length, str.IndexOf("X-Status") - (str.IndexOf(key_str) + (key_str + ": ").Length));
                    int content_length = Int32.Parse(parse_string);
                    using (var _file = File.Create(GetUniqueFileName("D:\\Current\\C, C++, C#\\CameraDumper\\CameraDumper\\KATOK\\")))
                    {
                        Array.Resize(ref buffer, content_length);
                        stream.BaseStream.Position = stream.BaseStream.Position - size + str.IndexOf("X-Zoom") + 12;
                        var length = stream.Read(buffer, 0, content_length);
                        _file.Write(buffer, 0, length);
                    }
                }
            }
        }

        static string GetUniqueFileName(string directory)
        {
            string path = "";
            
            var rand = new Random();
            var rand_i = 0;
            do
            {
                rand_i += rand.Next(20);
                path = directory + "jpg_" + rand_i.ToString() + ".jpg";
            } 
            while (File.Exists(path));
            return path;
        }
    }
}
