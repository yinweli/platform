/**
 * @file socket.cs
 * @note Socket組件
 * @author yinweli
 */
//-----------------------------------------------------------------------------
using System.Collections.Generic;
using System.Collections;
using System.IO;
using System.Net.Sockets;
using System.Net;
using System;
//-----------------------------------------------------------------------------
namespace LibCSNStandard
{
    /**
     * @brief 定義類別
     */
    public class SocketDefine
    {
        //-------------------------------------
        public const int HeadLength = 2; // 標頭長度
        public const int RecvLength = 8192; // 接收資料長度
        public const int SendLength = 65535; // 傳送資料長度
        //-------------------------------------
    }
    /**
	 * @brief 接收資料類別
	 */
    public class DataRecv
    {
        //-------------------------------------
        public int m_iLength; // 資料總長度
        public int m_iOffset; // 資料位移
        public byte[] m_cData; // 接收資料陣列
        //-------------------------------------
        /**
         * @brief 是否為空
         */
        public bool Empty()
        {
            return m_cData == null;
        }
        /**
         * @brief 是否完成
         */
        public bool Complete()
        {
            return m_cData != null && m_iLength == m_iOffset;
        }
        //-------------------------------------
    }
    /**
     * @brief 接收物件列表類別
     */
    public class DataRecvList
    {
        //-------------------------------------
        private List<DataRecv> m_Data = new List<DataRecv>(); // 接收物件列表
        //-------------------------------------
        /**
         * @brief 新增資料
         * @param cData 資料陣列
         * @param iLength 資料長度
         */
        public void Add(byte[] cData, int iLength)
        {
            if (iLength <= 0)
                return;

            int iProcLength = 0;
            int iLessLength = 0;
            int iNeedLength = 0;
            int iCopyLength = 0;

            while (iProcLength < iLength)
            {
                DataRecv Recv = m_Data.Count <= 0 ? new DataRecv() : m_Data[m_Data.Count - 1];

                if (Recv.Complete())
                    Recv = new DataRecv();

                if (Recv.Empty())
                {
                    byte[] cHead = new byte[SocketDefine.HeadLength];

                    Buffer.BlockCopy(cData, iProcLength, cHead, 0, SocketDefine.HeadLength);
                    iProcLength += SocketDefine.HeadLength;
                    iLessLength = iLength - iProcLength;

                    Recv.m_iLength = BitConverter.ToUInt16(cHead, 0);
                    Recv.m_iOffset = Recv.m_iLength >= iLessLength ? iLessLength : Recv.m_iLength;
                    Recv.m_cData = new byte[Recv.m_iLength];

                    Buffer.BlockCopy(cData, iProcLength, Recv.m_cData, 0, Recv.m_iOffset);
                    iProcLength += Recv.m_iOffset;

                    m_Data.Add(Recv);
                }
                else
                {
                    iLessLength = iLength - iProcLength;
                    iNeedLength = Recv.m_iLength - Recv.m_iOffset;
                    iCopyLength = iNeedLength >= iLessLength ? iLessLength : iNeedLength;

                    Buffer.BlockCopy(cData, iProcLength, Recv.m_cData, Recv.m_iOffset, iCopyLength);
                    iProcLength += iCopyLength;
                    Recv.m_iOffset += iCopyLength;
                }//if
            }//while
        }
        /**
         * @brief 取得資料
         * @return 資料陣列
         */
        public byte[] Get()
        {
            if (m_Data.Count <= 0)
                return null;

            if (m_Data[0].Complete() == false)
                return null;

            byte[] cData = m_Data[0].m_cData;

            m_Data.RemoveAt(0);

            return cData;
        }
        //-------------------------------------
    }
    /**
	 * @brief 客戶端Socket類別
	 */
    public class Socket
    {
        //-------------------------------------
        private TcpClient m_Socket = null; // 網路物件
        private NetworkStream m_Stream = null; // 網路資料流物件
        private DataRecvList m_RecvList = null; // 接收列表
        private byte[] m_cReceive = null; // 接收資料陣列
        //-------------------------------------
        /**
         * @brief 啟動客戶端
         * @param szIP 伺服器IP
         * @param iPort 伺服器埠號
         * @return true表示成功, false則否
         */
        public bool Start(string szIP, int iPort)
        {
            Stop();

            try
            {
                IPAddress[] IPAddr = Dns.GetHostAddresses(szIP);

                if (IPAddr.Length <= 0)
                    return false;

                m_Socket = new TcpClient(IPAddr[0].ToString(), iPort);
                m_Stream = m_Socket.GetStream();
                m_RecvList = new DataRecvList();
                m_cReceive = new byte[SocketDefine.RecvLength];

                return m_Socket.Connected;
            }//try

            catch (Exception Error)
            {
                Output.Error(this, Error.Message);
                Stop();

                return false;
            }//catch
        }
        /**
         * @brief 停止客戶端
         */
        public void Stop()
        {
            m_RecvList = null;
            m_cReceive = null;

            if (m_Stream != null)
            {
                m_Stream.Close();
                m_Stream = null;
            }//if

            if (m_Socket != null)
            {
                m_Socket.Close();
                m_Socket = null;
            }//if
        }
        /**
         * @brief 傳送資料到伺服器
         * @param cMessage 資料陣列
         * @return true表示成功, false則否
         */
        public bool Send(byte[] cMessage)
        {
            if (cMessage.Length > SocketDefine.SendLength)
                return false;

            if (IsRunning() == false)
                return false;

            try
            {
                // 傳送資料
                StreamWriter Writer = new StreamWriter(m_Stream);
                byte[] cHeadBuf = BitConverter.GetBytes(cMessage.Length);
                byte[] cDataFin = new byte[cMessage.Length + SocketDefine.HeadLength];

                Buffer.BlockCopy(cHeadBuf, 0, cDataFin, 0, SocketDefine.HeadLength);
                Buffer.BlockCopy(cMessage, 0, cDataFin, SocketDefine.HeadLength, cMessage.Length);

                m_Stream.Write(cDataFin, 0, cDataFin.Length);
                Writer.Flush();

                return true;
            }//try

            catch (Exception Error)
            {
                Output.Error(this, Error.Message);
                Stop();

                return false;
            }//catch
        }
        /**
         * @brief 取得接收資料
         * @return 接收資料
         */
        public byte[] Recv()
        {
            if (IsRunning() == false)
                return null;

            try
            {
                if (m_Stream.DataAvailable)
                    m_RecvList.Add(m_cReceive, m_Stream.Read(m_cReceive, 0, SocketDefine.RecvLength));

                return m_RecvList.Get();
            }//try

            catch (Exception Error)
            {
                Output.Error(this, Error.Message);
                Stop();

                return null;
            }//catch
        }
        /**
         * @brief 取得是否執行中
         * @return trur表示執行中, false則否
         */
        public bool IsRunning()
        {
            if (m_Socket == null)
                return false;

            if (m_Stream == null)
                return false;

            if (m_RecvList == null)
                return false;

            if (m_cReceive == null)
                return false;

            if (m_Socket.Connected == false)
                return false;

            try
            {
                bool bRunning = true;
                byte[] PeekData = new byte[1];

                if (m_Socket.Client.Poll(0, SelectMode.SelectRead))
                    bRunning = m_Socket.Client.Receive(PeekData, SocketFlags.Peek) != 0;

                return bRunning;
            }//try

            catch (Exception Error)
            {
                Output.Error(this, Error.Message);
                Stop();

                return false;
            }//catch
        }
        /**
         * @brief 取得Socket
         * @return Socket
         */
        public int SocketID()
        {
            return m_Socket != null ? m_Socket.Client.Handle.ToInt32() : 0;
        }
        //-------------------------------------
    }
}
//-----------------------------------------------------------------------------