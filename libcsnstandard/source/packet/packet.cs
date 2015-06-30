/**
 * @file packet.cs
 * @note 封包組件
 * @author yinweli
 */
//-----------------------------------------------------------------------------
using System.Collections.Generic;
using System.Collections;
using System;
//-----------------------------------------------------------------------------
namespace LibCSNStandard
{
    /**
     * @brief 封包類別
     */
    public class Packet
    {
        //-------------------------------------
        public int packet = 0; // 封包編號
        //-------------------------------------
        public Packet() { }
        public Packet(int pkt) { packet = pkt; }
        //-------------------------------------
    }
}
//-----------------------------------------------------------------------------