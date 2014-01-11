using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FileTimeCSharp
{
    class Program
    {
        static unsafe void Main(string[] args)
        {

            var dt = System.DateTime.FromFileTime(0x1cf0e46b0737550);
            Console.WriteLine("DateTime: {0}", dt);
            long ft = dt.ToFileTime();
            Console.WriteLine("100ns: {0} == 0x{0:X}", ft);
            byte[] bytes;
            unsafe
            {
                byte* b = (byte*)&ft;
                bytes = new byte[] { b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7] };
            }
            Console.WriteLine("mem: 0x{0}", string.Join("", bytes.Select(x => string.Format("{0:X2}", x))));
            /*
              Generates output:
DateTime: 2014-01-10 21:58:18
100ns: 130338610987890000 == 0x1CF0E46B0737550
mem: 0x507573B0460ECF01
             */
        }
    }
}
