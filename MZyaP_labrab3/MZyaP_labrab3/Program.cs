using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Runtime.InteropServices;
using System.IO;

namespace MZyaP_labrab3
{
    public struct Register
    {
        private Byte w;
        public Byte W
        {
            get { return w; }
            set { w = value; }
        }

        private Byte code;
        public Byte Code
        {
            get { return code; }
            set { code = value; }
        }

        private string name;
        public string Name
        {
            get { return name; }
            set { name = value; }
        }
        public Register(Byte w, Byte code, string name)
        {
            this.w = w;
            this.code = code;
            this.name = name;
        }
    }

    public struct MachOper
    {
        private string mnem;
        public string MNem
        {
            get { return mnem; }
            set { mnem = value; }
        }

        private Byte opcode;
        public Byte OpCode
        {
            get { return opcode; }
            set { opcode = value; }
        }
        public MachOper(string mnem, Byte opcode)
        {
            this.mnem = mnem;
            this.opcode = opcode;
        }
    }

    //union
    [StructLayout(LayoutKind.Explicit)]
    public struct ModRM
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 40)]
        [FieldOffset(0)]
        private Byte holder;
        public Byte Holder
        {
            get { return holder; }
            set { holder = value; }
        }

        [FieldOffset(3)]
        private Byte rm;
        public Byte RM
        {
            get { return rm; }
            set { rm = value; }
        }

        [FieldOffset(6)]
        private Byte reg;
        public Byte Reg
        {
            get { return reg; }
            set { reg = value; }
        }

        [FieldOffset(8)]
        private Byte mod;
        public Byte Mod
        {
            get { return mod; }
            set { mod = value; }
        }
    }

    [StructLayout(LayoutKind.Explicit)]
    public struct Flags
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 40)]
        [FieldOffset(0)]
        private ushort holder;
        public ushort Holder
        {
            get { return holder; }
            set { holder = value; }
        }

        [FieldOffset(0)]
        private ushort reg;
        public ushort Reg
        {
            get { return reg; }
            set { reg = value; }
        }

        [FieldOffset(1)]
        private ushort mem;
        public ushort Mem
        {
            get { return mem; }
            set { mem = value; }
        }

        [FieldOffset(2)]
        private ushort acc;
        public ushort Acc
        {
            get { return acc; }
            set { acc = value; }
        }

        [FieldOffset(3)]
        private ushort seg;
        public ushort Seg
        {
            get { return seg; }
            set { seg = value; }
        }

        [FieldOffset(4)]
        private ushort bp;
        public ushort Bp
        {
            get { return bp; }
            set { bp = value; }
        }

        [FieldOffset(5)]
        private ushort si;
        public ushort Si
        {
            get { return si; }
            set { si = value; }
        }

        [FieldOffset(6)]
        private ushort bas;
        public ushort Bas
        {
            get { return bas; }
            set { bas = value; }
        }

        [FieldOffset(7)]
        private ushort ind;
        public ushort Ind
        {
            get { return ind; }
            set { ind = value; }
        }

        [FieldOffset(8)]
        private ushort imm;
        public ushort Imm
        {
            get { return imm; }
            set { imm = value; }
        }
    }

    class Program
    {
        public static readonly Register[] regs = new Register[] 
        {
            new Register(0, 0, "al"),
	        new Register(0, 1, "cl"),
	        new Register(0, 2, "dl"),
	        new Register(0, 3, "bl"),
	        new Register(0, 4, "ah"),
	        new Register(0, 5, "ch"),
	        new Register(0, 6, "dh"),
	        new Register(0, 7, "bh"),
	        new Register(1, 0, "ax"),
	        new Register(1, 1, "cx"),
	        new Register(1, 2, "dx"),
	        new Register(1, 3, "bx"),
	        new Register(1, 4, "bp"),
	        new Register(1, 5, "sp"),
	        new Register(1, 6, "si"),
	        new Register(1, 7, "di")
        };
        public static readonly MachOper[] MchOp = new MachOper[]
        {
            new MachOper("lea", 0x8D),
	        new MachOper("lds", 0xC5),
	        new MachOper("les", 0xC4)
        };

        public static Byte Main_OpCode = new Byte();

        //union mdr
        public static ModRM mod_rm = new ModRM();

        public static readonly string[] segments = new string[] {"es","cs","ss","ds"};

        //union flags
        public static Flags flags = new Flags();

        public static ushort mo_code = new ushort();

        public static ushort disp = new ushort();

        public static int search_reg(string name)
        {
            for (int i = 0; i < 16; i++)
            {
                if (regs[i].Name == name)
                    return i;
            }
            return -1;
        }

        public static int search_seg(string name)
        {
            for (int i = 0; i < 4; i++)
                if (segments[i] == name)
                    return i;
            return -1;
        }

        public static int search_mo(string name)
        {
            for (int i = 0; i < 3; i++)
            {
                if (MchOp[i].MNem == name)
                    return i;
            }
            return -1;
        }

        public static void clear()
        {
            flags.Holder = disp = mo_code = 0;
            mod_rm.Holder = 0;
        }

        public static void read_address(string op, char it)
        {
            StringBuilder str_adr = new StringBuilder();
            if (it == '[' || it == '+')
                it++;
            for (; it != op[op.Length - 1] && it != '+' && it != ']'; ++it)
                str_adr.Append(it);

            int index = search_reg(str_adr.ToString());

            if (index < 0)
            {
                StringWriter ss = new StringWriter();
                ss.WriteLine(str_adr);
                ss.WriteLine(disp);
                return;
            }

            Register reg = regs[index];

            if (reg.Name == "bx" || reg.Name == "bp")	
            {
                flags.Bas = 1;

                if (reg.Name == "bp")
                    flags.Bp = 1;
            }
            else if (reg.Name == "di" || reg.Name == "si")
            {
                flags.Ind = 1;

                if (reg.Name == "si")
                    flags.Si = 1;
            }
        }

        public static void operand(string op)
        {
	        int index = search_reg(op);

	        if (index >= 0)	
		        mod_rm.Reg = regs[index].Code;
	        else if (op[0] != '[')	
	        {
		        StringWriter ss = new StringWriter();
                ss.WriteLine(op);
		        ss.WriteLine(disp);

		        return;
	        }
	        else
	        {
		        foreach (char it in op) 
		        {
			        read_address(op, it);
		        }
	        }
        }

        public static void create_mod_rm()
        {
            if ((flags.Bas == 0 && flags.Ind == 0)  // Mod == 00
                || ((flags.Bas >= 1 || flags.Bas >= 1) && disp == 0))
                mod_rm.Mod = 0;
            else  // Mod == 10
                mod_rm.Mod = 2;

            if (flags.Bas >= 1 && flags.Bp == 0)	 // [bx+si] || [bx+di] || [bx]
            {
                if (flags.Ind >= 1) // [bx+si] || [bx+di]
                {
                    if (flags.Si >= 1)  // [bx+si]
                        mod_rm.RM = 0;
                    else  // [bx+di]
                        mod_rm.RM = 1;
                }
                else  // [bx]
                    mod_rm.RM = 7;
            }
            else if (flags.Bas >= 1 && flags.Bas >= 1) // [bp+si] || [bp+di]
            {
                if (flags.Si >= 1)  // [bp+si]
                    mod_rm.RM = 2;
                else  // [bp+di]
                    mod_rm.RM = 3;
            }
            else if (flags.Si >= 1)  // [si]
                mod_rm.RM = 4;
            else  // [di]
                mod_rm.RM = 5;
        }


        static void Main(string[] args)
        {
	        ifstream in("input.txt");

	        ofstream out("output.txt");

	        clear();
	
	        while (in.good())
	        {
		        StringBuilder buf = new StringBuilder();
                StringBuilder line = new StringBuilder();
		        char ch;

		        // Мнемоника.
		        while (!in.eof() && (ch = in.get()) != ' ')
			        buf.Append(ch);

		        int mo_code_i = search_mo(buf.ToString());

		        mo_code = MchOp[mo_code_i].OpCode;

		        line.Append(buf + " ");

		        // Первый операнд.
		        buf.clear();
		        while (!in.eof() && (ch = in.get()) != ',')
			        buf += ch;

		        operand(buf);

		        line.append(buf + ',');

		        // Второй операнд.
		        buf.clear();
		        while (!in.eof() && (ch = in.get()) != '\n' && ch != -1)
			        buf += ch;

		        operand(buf);

		        line.append(buf + '\n');

		        // Заполнить modR/M.
		        create_mod_rm();

		        print(line, out);

		        line.clear();

		        // Сброс.
		        clear();
	        }

	        in.close();
	        out.close();

            Console.ReadKey();
        }
    }
}
