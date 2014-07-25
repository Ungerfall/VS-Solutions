using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Runtime.InteropServices;

namespace AutowashQueue
{
    public class Camera
    {
        [DllImport("Shtil400499cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void awInitCamera();

        [DllImport("Shtil400499cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void awGetImage();

        [DllImport("Shtil400499cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void awLoadImage(StringBuilder path);

        [DllImport("Shtil400499cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void awComplete();
    }
}
