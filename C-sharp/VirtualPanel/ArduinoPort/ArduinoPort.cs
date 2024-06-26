﻿using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Globalization;
using System.IO.Ports;
using System.IO;
using System.Linq;
using System.Threading;
using System.Text;
using VirtualPanel;

namespace ArduinoCom
{
    public class ArduinoPort
    {
        public String PortName { get { return port.PortName; } set { port.PortName = value; } }
        public String DeviceID { get; set; }
        public Boolean IsConnected { get { return connected; } }
        public TimeSpan SearchPortTimeout { get; set; } = TimeSpan.FromMilliseconds(2000);
        public TimeSpan SearchPollFrequency { get; set; } = TimeSpan.FromMilliseconds(500);
        public int BaudRate { get { return port.BaudRate; } }

        private bool connected = false;
        private SerialPort port;
        private BackgroundWorker port_finder;
        private String read_buffer;
        private System.Timers.Timer checkPort = new System.Timers.Timer(100);
        private string pre_selected_port = "";

        public event EventHandler<MessageEventArgs<object>> MessageReceived;
        public event EventHandler<MessageEventArgs<object>> MessageSent;
        public event EventHandler<MessageEventArgs<object>> MessageError;
        public event EventHandler<ConnectedEventArgs> Connected;
        public event EventHandler<ConnectedEventArgs> Disconnected;

        public ArduinoPort(string device_id, String portname="", int baudrate = 115200)
        {
            DeviceID = device_id;

            // Set up port object.
            port = new SerialPort();
            SetPortSettings(baudrate);

            pre_selected_port = portname;

            // Setup port checker timer.
            checkPort.Elapsed += CheckPort_Elapsed;

            // Create Backgroundworker.
            port_finder = new BackgroundWorker();

            // Set properties
            port_finder.WorkerSupportsCancellation = true;
            port_finder.WorkerReportsProgress = false;

            // Attach event handlers.
            port_finder.DoWork += Port_finder_DoWork;
            port_finder.RunWorkerCompleted += Port_finder_RunWorkerCompleted;

        }

        private void SetPortSettings(int baudrate)
        {
            port.BaudRate = baudrate;
            port.Parity = Parity.None;
            port.DataBits = 8;
            port.StopBits = StopBits.One;
            port.Handshake = Handshake.None;
            port.RtsEnable = false;
            port.DtrEnable = false;
            port.NewLine = "\r\n";
            port.Encoding = Encoding.UTF8;
            port.WriteTimeout = 200;
        }

        private void CheckPort_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            if (connected && !port.IsOpen)
                Disconnect(true);
        }

        public void Open()
        {   
            if (!connected && !port_finder.IsBusy)
                port_finder.RunWorkerAsync();
        }

        public void Close()
        {
            Disconnect(false);
        }

        public void Reset()
        {
            port.DtrEnable = !port.DtrEnable;
            port.RtsEnable = !port.RtsEnable;
            Thread.Sleep(1000);
            port.DtrEnable = !port.DtrEnable;
            port.RtsEnable = !port.RtsEnable;
            //Thread.Sleep(50);

            Disconnect(true);
        }

        #region Port Finding Worker

        private void Port_finder_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Cancelled)
                return;

            Debug.WriteLine("Port found " + port.PortName);

            read_buffer = "";

            // Reattach handler.
            port.DataReceived += Port_DataReceived;
            checkPort.Start();

            connected = true;
            Connected?.ThreadAwareRaise(this, new ConnectedEventArgs(port.PortName));

        }


        /// <summary>
        /// Attempts to find a port with a matching ID such that we can use the communication.
        /// </summary>
        /// <param name="sender">Event Sender</param>
        /// <param name="e">Empty</param>
        private void Port_finder_DoWork(object sender, DoWorkEventArgs e)
        {
            BackgroundWorker owner = sender as BackgroundWorker;

            // While we haven't found a port.
            while (!connected)
            {
                port.DtrEnable = !port.DtrEnable;
                port.RtsEnable = !port.RtsEnable;

                foreach (String name in SerialPort.GetPortNames())
                {
                    if (pre_selected_port != "" && name != pre_selected_port)
                        continue;

                    Debug.WriteLine(name);
                    if (owner.CancellationPending)
                    {
                        e.Cancel = true;
                        return;
                    }

                    if (port.IsOpen) port.Close();
                    port.PortName = name;

                    // It can happen that Windows will give us incorrect port names, if this occurs we skip the processing for it.
                    try
                    {
                        port.Open();
                    }
                    catch (IOException)
                    {
                        continue; // Happens when a port is broken or not compatible.
                    }
                    catch (UnauthorizedAccessException)
                    {
                        continue; // Happens when a port is already in use by some other program.
                    }
                    // reset arduino before connection
                    port.DtrEnable = !port.DtrEnable;
                    Thread.Sleep(1000);
                    port.DtrEnable = !port.DtrEnable;

                    DateTime then = DateTime.Now + SearchPortTimeout;
                    DateTime send_id = DateTime.Now + SearchPollFrequency;

                    while (then > DateTime.Now)
                    {

                        if (send_id < DateTime.Now)
                        {
                            try
                            {
                                port.WriteLine("ID");
                            }
                            catch (Exception)
                            {
                                continue;
                            }
                            send_id = DateTime.Now + SearchPollFrequency;
                        }

                        read_buffer += port.ReadExisting();

                        Debug.Write(read_buffer);

                        string[] chunks = read_buffer.Split(new string[] { port.NewLine }, StringSplitOptions.None);

                        read_buffer = "";

                        if (chunks.Last() != "")
                        {
                            read_buffer = chunks.Last();
                            chunks[chunks.Length - 1] = "";
                        }

                        foreach (var data in chunks)
                        {
                            if (data.Contains(DeviceID))
                                return;
                        }

                        Thread.Sleep((int)SearchPollFrequency.TotalMilliseconds);
                    }


                    port.Close();
                }

                Thread.Sleep((int)SearchPollFrequency.TotalMilliseconds);
            }
        }

        #endregion

        private void Disconnect(bool restart)
        {
            connected = false;
            port.DataReceived -= Port_DataReceived;
            checkPort.Stop();
            port_finder.CancelAsync();

            if (restart) // Connection is lost
                port_finder.RunWorkerAsync();

            else        // Disconnect is requested from UI
                port.Close();

            Disconnected.ThreadAwareRaise(this, new ConnectedEventArgs(port.PortName));
        }

        #region Port IO Functions


        public void Send(byte channel, bool data)
        {
            SendMessage(channel, vp_type.vp_boolean, Convert.ToInt16(Convert.ToBoolean(data)).ToString("X"), data);
        }

        public void Send(byte channel, float data)
        {
            byte[] bytes = BitConverter.GetBytes(data);
            String hexdata = Convert.ToUInt32(BitConverter.ToUInt32(bytes, 0)).ToString("X8");
            SendMessage(channel, vp_type.vp_float, hexdata, data);
            // SendMessage(channel, vp_type.vp_float, data.ToString("0.0000", CultureInfo.InvariantCulture));
        }

        public void Send(byte channel, string data)
        {
            string stringLenght = Convert.ToByte(data.Length).ToString("X2"); 
            SendMessage(channel, vp_type.vp_string, stringLenght + data, data);
        }

        public void Send(byte channel)
        {
            SendMessage(channel, vp_type.vp_void, "", "");
        }

        public void Send(byte channel, vp_type type, long data)
        {
            String hexdata = "";

            try {

                switch (type)
                {
                    case vp_type.vp_byte:
                        hexdata = Convert.ToByte(data).ToString("X2"); break;
                    case vp_type.vp_int:
                        hexdata = Convert.ToInt16(data).ToString("X4"); break;
                    case vp_type.vp_uint:
                        hexdata = Convert.ToUInt16(data).ToString("X4"); break;
                    case vp_type.vp_long:
                        hexdata = Convert.ToInt32(data).ToString("X8"); break;
                    case vp_type.vp_ulong:
                        hexdata = Convert.ToUInt32(data).ToString("X8"); break;
                    default:
                        throw new InvalidOperationException("Non numeric vp_type with numeric data.");
                }
            }
            catch (OverflowException oe)
            {
                throw new OverflowException("Numeric data not compatible with: " + type.ToString(), oe);
            }

           SendMessage(channel, type, hexdata, data);
        }

        // Wrapper for converted Send functions helps with even and prevents duplicate code.
        private void SendMessage(byte channel, vp_type type, string data, object messageData)
        {
            String message = channel.ToString("X2") + ((byte)type).ToString("X1") + data;
            this.Write(message);
            MessageSent?.ThreadAwareRaise(this, new MessageEventArgs<object>(channel, type, messageData));
        }

        // Write to Arduino port (GUI thread)
        public void Write(string data)
        {
            // Suppress any disconnected calls.
            if (!connected)
                throw new InvalidOperationException("Arduino Port is not connected.");

            Debug.WriteLine(data);

            try
            {
                if (port.IsOpen)
                    port.WriteLine(data);
                else // If we are connected but the port is not open we need to update internal state, and notify.
                    Disconnect(true);
            }
            catch (Exception e)
            {
                Debug.WriteLine("Writing to port failed: " + e);
            }
        }

        // Attached to port receive event (PORT thread)
        private void Port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            object messagedata = null;
            vp_type type = vp_type.vp_error;

            if (!(connected && port.IsOpen))
                return;

            string temp = port.ReadExisting();

            read_buffer += temp;

            string[] chunks = read_buffer.Split(new string[] { port.NewLine }, StringSplitOptions.None);

            read_buffer = "";

            if (chunks.Last() != "")
            {
                read_buffer = chunks.Last();
                chunks[chunks.Length - 1] = "";
            }

            foreach (var data in chunks)
            {
                Debug.WriteLine(data);

                if (data.Length < 3)
                    continue;

                int channel;
                if (!int.TryParse(data.Substring(0, 2), NumberStyles.HexNumber, null, out channel))
                {
                    channel = (int) ChannelId.EndChannel;
                    messagedata = data;
                    MessageError?.ThreadAwareRaise(this, new MessageEventArgs<object>(channel, type, messagedata));
                    continue;
                }

                int type_temp;
                if (!int.TryParse(data.Substring(2, 1), NumberStyles.HexNumber, null, out type_temp))
                {
                    messagedata = data;
                    MessageError?.ThreadAwareRaise(this, new MessageEventArgs<object>(channel, type, messagedata));
                    continue;
                }
                type = (vp_type)type_temp;

                int string_length = 0;
                string value_string = "";
                if (type == vp_type.vp_string && data.Length >= 5)
                {
                    if (!int.TryParse(data.Substring(3, 2), NumberStyles.HexNumber, null, out string_length))
                        continue;
                    value_string = data.Substring(5, data.Length - 5);
                    int received_Lenght = ASCIIEncoding.UTF8.GetByteCount(value_string);
                    if (received_Lenght != string_length)
                    {
                        messagedata = data;
                        MessageError?.ThreadAwareRaise(this, new MessageEventArgs<object>(channel, type, messagedata));
                        continue;
                    }
                }
                else
                {
                    value_string = data.Substring(3, data.Length - 3);
                }
                             

                try
                {
                    switch (type)
                    {
                        case vp_type.vp_void:
                            messagedata = "";
                            break;
                        case vp_type.vp_string:
                            messagedata = value_string;
                            break;
                        case vp_type.vp_boolean:
                            messagedata = Convert.ToBoolean(Convert.ToInt32(value_string, 16));
                            break;
                        case vp_type.vp_byte:
                            messagedata = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(value_string, 16)));
                            break;
                        case vp_type.vp_int:
                            messagedata = Convert.ToInt32(Convert.ToInt16(value_string, 16));
                            break;
                        case vp_type.vp_uint:
                            messagedata = Convert.ToInt32(Convert.ToUInt16(value_string, 16));
                            break;
                        case vp_type.vp_long:
                            messagedata = Convert.ToInt64(Convert.ToInt32(value_string, 16));
                            break;
                        case vp_type.vp_ulong:
                            messagedata = Convert.ToInt64(Convert.ToUInt32(value_string, 16));
                            break;
                        case vp_type.vp_float:
                            byte[] bytes = BitConverter.GetBytes(Convert.ToUInt32(value_string, 16));
                            messagedata = BitConverter.ToSingle(bytes, 0);
                            //messagedata = float.Parse(value_string, CultureInfo.InvariantCulture);
                            break;
                        default:
                            {
                                MessageError?.ThreadAwareRaise(this, new MessageEventArgs<object>(channel, type, value_string));
                                continue;
                            }
                    }

                    MessageReceived?.ThreadAwareRaise(this, new MessageEventArgs<object>(channel, type, messagedata));
                }
                catch (FormatException fe)
                {
                    Debug.WriteLine(fe);
                    continue;
                }
                catch (ArgumentOutOfRangeException ae)
                {
                    Debug.WriteLine(ae);
                    continue;
                }
                catch (OverflowException oe)
                {
                    Debug.WriteLine(oe);
                    continue;
                }
                catch (Exception ex)
                {
                    Debug.WriteLine(ex);
                    continue;
                }
            }
        }

        #endregion

    }
}
