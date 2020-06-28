using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VirtualPanel
{
    class FileHandle
    {
        private List<string> lines = null;
        private int readCaret = 0;
        private int writeCaret = 0;
        private string filePath = "";
        private bool changed = false;

        public bool isOpen { get { return filePath != ""; } }
        public int LineCount { get { return lines.Count; } }

        public FileHandle()
        {
        }

        public Int32 Open(string filepath)
        {
            lines = File.ReadAllLines(filepath).ToList();
            readCaret = 0;
            writeCaret = lines.Count;
            filePath = filepath;
            return (lines.Count);
        }

        public void MoveWriteCaret(long line)
        {
            if (!isOpen)
                return;

            int newPos = (int) line - 1;

            if (newPos < 0)
                newPos = 0;

            writeCaret = newPos;
        }

        public void MoveReadCaret(long line)
        {
            if (!isOpen)
                return;

            int newPos = (int)line - 1;

            if (newPos >= lines.Count)
                newPos = lines.Count - 1;
            if (newPos < 0)
                newPos = 0;

            readCaret = newPos;
        }

        public string ReadLine()
        {
            if (!isOpen)
                return null;

            if (readCaret < 0 || readCaret >= lines.Count)
                return null;

            string line = lines[readCaret];
            readCaret++;

            if (line == "")
                return "";

            return line.Truncate(60);
        }

        public void WriteLine(string line)
        {
            if (!isOpen)
                return;

            if (writeCaret < 0)
                return;

            changed = true;

            if (writeCaret < lines.Count)
            {
                lines[writeCaret] = line;
            }
            else
            {
                var pos = writeCaret - lines.Count;

                for (int i = 0; i < pos; i++)
                {
                    lines.Add("");
                }

                lines.Add(line);
            }
            writeCaret++;
        }

        public void Clear()
        {
            if (!isOpen)
                return;

            changed = true;

            lines = new List<string>();

            readCaret = 0;
            writeCaret = 0;
        }

        public void Delete()
        {
            if (!isOpen)
                return;

            File.Delete(filePath);

            filePath = "";
            lines = new List<string>();
        }

        public void toDisk()
        {
            if (!isOpen || !changed)
                return;

            try
            {
                File.WriteAllLines(filePath, lines);
                changed = false;
            }
            catch (IOException)
            {
            }

        }
    }
}
