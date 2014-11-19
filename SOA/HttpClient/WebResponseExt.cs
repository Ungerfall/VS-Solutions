using System.IO;
using System.Net;
using System.Text;

namespace HttpClient
{
    public static class WebResponseExt
    {
        public static string ReadToEnd(this WebResponse response)
        {
            using (var stream = response.GetResponseStream())
                if (stream != null)
                    using (var reader = new StreamReader(stream, Encoding.UTF8))
                        return reader.ReadToEnd().Trim();
            return null;
        }
    }
}