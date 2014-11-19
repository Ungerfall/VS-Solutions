using System;
using System.Net;
using System.Text;
using Serialization;

namespace HttpClient
{
    public class Client
    {
        private HttpWebRequest request;
        public int Port { get; set; }

        public Client(int port)
        {
            Port = port;
        }

        public void SendRequest(string method, string httpMethod = "GET")
        {
            request = (HttpWebRequest)WebRequest.Create(string.Format("http://127.0.0.1:{0}/{1}", Port, method));
            request.Proxy = null;
            request.Timeout = 150;
            request.Method = httpMethod;
        }

        public bool Ping()
        {
            try
            {
                request = (HttpWebRequest) WebRequest.Create(string.Format("http://127.0.0.1:{0}/Ping", Port));
                request.Proxy = null;
                request.Timeout = 150;
                using (var response = (HttpWebResponse) request.GetResponse())
                {
                    return response.StatusCode == HttpStatusCode.OK;
                }
            }
            catch (Exception)
            {
                return false;
            }

        }

        public Input GetInputData()
        {
            try
            {
                request = (HttpWebRequest) WebRequest.Create(string.Format("http://127.0.0.1:{0}/GetInputData", Port));
                using (var response = request.GetResponse())
                {
                    var jsonSerial = new JsonSerializer();
                    return (jsonSerial.Deserialize<Input>(response.ReadToEnd()));
                }
            }
            catch (Exception)
            {
                return null;
            }
        }

        public void WriteAnswer(Output output)
        {
            try
            {
                request = (HttpWebRequest) WebRequest.Create(string.Format("http://127.0.0.1:{0}/WriteAnswer", Port));
                request.Method = "POST";
                request.ContentType = "application/json";
                var jsonSerial = new JsonSerializer();
                var bytes = Encoding.UTF8.GetBytes(jsonSerial.Serialize(output));
                request.ContentLength = bytes.Length;
                using (var os = request.GetRequestStream())
                {
                    os.Write(bytes, 0, bytes.Length);
                }
            }
            catch (Exception)
            {
                throw new Exception();
            }
        }
    }
}