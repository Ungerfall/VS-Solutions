using System.IO;
using System.Text;
using System.Xml;
using Xml = System.Xml.Serialization;

namespace Serialization
{
    public class XmlSerializer : ISerializer
    {
        private Xml.XmlSerializer xmlSerializer;
        public string Serialize(Input input)
        {
            var output = new Output(input);
            var sBuilder = new StringBuilder();
            xmlSerializer = new Xml.XmlSerializer(typeof(Output));
            using (var xmlWriter = XmlWriter.Create(sBuilder, new XmlWriterSettings { OmitXmlDeclaration = true }))
            {
                xmlSerializer.Serialize(
                    xmlWriter, 
                    output, 
                    new Xml.XmlSerializerNamespaces(new[] { XmlQualifiedName.Empty }));
                return sBuilder.ToString();
            }
        }

        public T Deserialize<T>(string sText)
        {
            xmlSerializer = new Xml.XmlSerializer(typeof(T));
            using (var stream = new MemoryStream(Encoding.UTF8.GetBytes(sText)))
                return (T)xmlSerializer.Deserialize(stream);
        }
    }
}