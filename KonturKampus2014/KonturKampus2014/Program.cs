using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;

namespace KonturKampus2014
{
    class Program
    {
        public class Point
        {
            public Point(int x, int y)
            {
                X = x;
                Y = y;
            }
            public readonly int X;
            public readonly int Y;
        }

        public abstract class Classroom
        {
            public readonly List<string> Students = new List<string>();
        }

        public static int[] ParseNumbers(IEnumerable<string> lines)
        {
            return lines
                .Where(w => w.Length > 0)
                .Select(int.Parse)
                .ToArray();
        }

        public static string[] GetAllStudents(IEnumerable<Classroom> classes)
        {
            return classes
                .SelectMany(s => s.Students)
                .ToArray();
        }

        public static List<Point> ParsePoints(IEnumerable<string> lines)
        {
            return lines
                .Select(s =>
                {
                    var nums = s.Split(' ');
                    return new Point(int.Parse(nums[0]), int.Parse(nums[1]));
                })
                .ToList();
        }

        private static IEnumerable<string> GetSortedWords(params string[] textLines)
        {
            return textLines
                .Select(s => Regex.Split(s, @"\W+"))
                .SelectMany(sm => sm.Where(w => !string.IsNullOrEmpty(w)))
                .Select(s => s.ToLower())
                .OrderBy(ob => ob)
                .Distinct()
                .ToArray();
        }

        private static IEnumerable<Point> GetNeighbours(Point p)
        {
	        int[] d = {-1, 0, 1};
            return d
                .SelectMany(sm => d.Select((x, y) => new Point(p.X + x, p.Y + y)))
                .Where(w => !(w.X == p.X && w.Y == p.Y));
        }

        static void Main()
        {
            var vocabulary = GetSortedWords(
                "Hello, hello, hello, how low",
                "",
                "With the lights out, it's less dangerous",
                "Here we are now; entertain us",
                "I feel stupid and contagious",
                "Here we are now; entertain us",
                "A mulatto, an albino, a mosquito, my libido...",
                "Yeah, hey"
            );
            foreach (var item in GetNeighbours(new Point(5, 6)))
                Console.WriteLine("{0} - {1}", item.X, item.Y);
        }
    }
}
