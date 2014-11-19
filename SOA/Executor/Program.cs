using System;
using System.Globalization;
using System.Text.RegularExpressions;
using HttpClient;
using Serialization;

namespace Executor
{
    class Program
    {
        private enum TaskType
        {
            Serialization,
            Client,
            Server
        }
        static void Main()
        {
            const TaskType task = TaskType.Client;
            switch (task)
            {
                case TaskType.Serialization:
                    SerializeCase();
                    break;
                case TaskType.Client:
                    ClientCase();
                    break;
                case TaskType.Server:
                    ServerCase();
                    break;
            }
        }

        private static void SerializeCase()
        {
            var serializer = new ISerializer[]{new XmlSerializer(), new JsonSerializer()};
            var type = Console.ReadLine();
            var text = Regex.Replace(Console.In.ReadToEnd(), @"\s+", string.Empty);
            Console.Write(type == "Xml"
                ? serializer[0].Serialize(serializer[0].Deserialize<Input>(text))
                : serializer[1].Serialize(serializer[1].Deserialize<Input>(text)));
        }

        private static void ClientCase()
        {
            var port = int.Parse(Console.ReadLine(), NumberStyles.Integer);
            var client = new Client(port);
            while (true)
            {
                if (!client.Ping()) continue;
                var input = client.GetInputData();
                if (input == null) continue;
                client.WriteAnswer(new Output(input));
                break;
            }
        }

        private static void ServerCase()
        {
            
        }
    }
}
