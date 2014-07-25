using System;
using System.IO;
using System.Collections;

namespace Filtering
{
    class Program
    {
        private static int fl = 1000,
                           fu = 3000;

        private static string fileIn = "SIGNAL.dat",
                              fileOut = "OUTPUT.DAT";

        static void Main()
        {
            var sd = DataProcessor.LoadFromFile(fileIn);
            var f = new Filter(fl, fu, sd.Fd);
            sd.ProcessData(f);
            sd.SaveToFile(fileOut);
            Console.WriteLine("Обработка завершена.");
            Console.WriteLine("Нажмите любую клавишу для выхода...");
            Console.ReadKey();
            Environment.Exit(0);
        }

        public class DataProcessor
        {
            public ArrayList Data { get; private set; }
            public int Fd { get; private set; }

            private DataProcessor(int fd, ArrayList data)
            {
                Data = data;
                Fd = fd;
            }

            public static DataProcessor LoadFromFile(string filename)
            {
                try
                {
                    var fs = new FileStream(filename, FileMode.Open, FileAccess.Read);
                    var br = new BinaryReader(fs);
                    var fd = br.ReadInt32();
                    var data = new ArrayList();
                    while (br.BaseStream.Position != br.BaseStream.Length)
                        data.Add(br.ReadInt16());
                    br.Close();
                    return new DataProcessor(fd, data);
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Ошибка чтения файла. " + ex.Message);
                    return null;
                }
            }

            public void SaveToFile(string filename)
            {
                try
                {
                    var fs = new FileStream(filename, FileMode.Create, FileAccess.Write);
                    var bw = new BinaryWriter(fs);
                    bw.Write(Fd);
                    foreach (short v in Data)
                        bw.Write(v);
                    bw.Close();
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Ошибка записи файла. " + ex.Message);
                }
            }

            public void ProcessData(Filter filter)
            {
                var countTick = Data.Count;
                var newData = new double[Data.Count + filter.h.Length - 1];
                for (int i = 0; i < countTick; i++)
                    for (int j = 0; j < filter.h.Length; j++)
                        newData[i + j] += (short)Data[i] * filter.h[j];
                Data.Clear();
                for (int i = 0; i < countTick; i++)
                    Data.Add((short)newData[i]);
            }
        }

        public class Filter
        {
            private const int delta = 40; // Дельта F - шаг в АЧХ
            private int N = 41; // Размер окна
            private int Ns; // Размер массива импульсной характеристики
            private double LLow = -40; // Нижний предел АЧХ
            private double LHi = 0; // Верхний предел АЧХ
            private double[] H; // АЧХ
            public double[] h; // Импульсная характеристика

            public Filter(int fl, int fh, int fd)
            {
                // Преобразуем пределы в квантовые единицы измерения
                LLow = Math.Pow(10.0, LLow / 20.0);
                LHi = Math.Pow(10.0, LHi / 20.0);
                // Инициализация
                Ns = fd / delta;
                H = new double[Ns];
                h = new double[N];
                // Вычисление АЧХ. Заполняем 1 половину, 2 отображаем симметрично
                for (int i = 0; i < Ns / 2; i++)
                {
                    if (i * delta < fl || i * delta > fh)
                        H[i] = LHi;
                    else
                        H[i] = LLow;
                    H[Ns - i - 1] = H[i];
                }
                // Расчёт IDFT
                for (int n = -N / 2; n <= N / 2; n++)
                {
                    var sum = 0.0;
                    for (int i = 0; i < Ns; i++)
                        sum += H[i] * Math.Cos((2.0 * Math.PI * i * n) / Ns);
                    h[n + N / 2] = (sum / Ns) * (0.53836 - 0.46164 * Math.Cos(2.0 * Math.PI * (n + N / 2) / (N - 1)));
                    //окно Хемминга
                }
            }
        }
    }
}
