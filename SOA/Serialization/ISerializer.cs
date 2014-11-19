namespace Serialization
{
    public interface ISerializer
    {
        string Serialize(Input input);
        T Deserialize<T>(string sText);
    }
}