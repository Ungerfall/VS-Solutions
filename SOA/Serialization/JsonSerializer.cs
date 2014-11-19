using Newtonsoft.Json;

namespace Serialization
{
    public class JsonSerializer : ISerializer
    {
        public string Serialize(Input input)
        {
            var output = new Output(input);
            return JsonConvert.SerializeObject(output);
        }

        public string Serialize(Output output)
        {
            return JsonConvert.SerializeObject(output);
        }

        public T Deserialize<T>(string sText)
        {
            return JsonConvert.DeserializeObject<T>(sText);
        }
    }
}