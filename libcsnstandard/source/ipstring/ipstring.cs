/**
 * @file ipstring.cs
 * @note 位址字串類別
 * @author yinweli
 */
//-----------------------------------------------------------------------------
using System.Collections.Generic;
using System.Collections;
using System.Reflection;
using System;
//-----------------------------------------------------------------------------
namespace LibCSNStandard
{
    /**
     * @brief 位址字串類別
     */
    public class IPString
    {
        //-------------------------------------
        public static char[] Separator = new char[] { ':', ',', ' ' }; // 分割字串
        //-------------------------------------
        public string IP = ""; // 位址字串
        public int Port = 0; // 埠號
        //-------------------------------------
        public IPString() { }
        public IPString(string ipstring)
        {
            string[] Result = ipstring.Split(Separator, 2);

            if (Result.Length > 0)
                IP = Result[0];

            if (Result.Length > 1)
                Port = Convert.ToInt32(Result[1]);
        }
        public IPString(string ip, int port)
        {
            IP = ip;
            Port = port;
        }
        //-------------------------------------
        public static implicit operator IPString(string value)
        {
            return new IPString(value);
        }
        public static implicit operator string(IPString value)
        {
            return value.IP + Separator[0] + value.Port;
        }
        //-------------------------------------
    }
}
//-----------------------------------------------------------------------------