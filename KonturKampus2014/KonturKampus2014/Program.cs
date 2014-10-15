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
            public int X, Y;
        }

        public class Classroom
        {
            public List<string> Students = new List<string>();
        }

        public static int[] ParseNumbers(IEnumerable<string> lines)
        {
            return lines
                .Where(w => w.Length > 0)
                .Select(int.Parse)
                .ToArray();
        }

        public static string[] GetAllStudents(Classroom[] classes)
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

        public static string[] GetSortedWords(params string[] textLines)
        {
            return textLines
                .Select(s => Regex.Split(s, @"\W+"))
                .SelectMany(sm => sm.Where(w => !string.IsNullOrEmpty(w)))
                .Select(s => s.ToLower())
                .OrderBy(ob => ob)
                .Distinct()
                .ToArray();
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
            foreach (var word in vocabulary)
                Console.WriteLine(word);
        }
    }
}
