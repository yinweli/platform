/**
 * @file setup.cs
 * @note 設定組件
 * @author yinweli
 */
//-----------------------------------------------------------------------------
using System.Collections.Generic;
using System.Collections;
using System.Reflection;
using System.Text;
using System;
//-----------------------------------------------------------------------------
namespace Setup
{
    /**
     * @brief dbf類別
     */
    public class SDBF
    {
        //-------------------------------------
        public string Name = ""; // 識別名稱
        public string Class = ""; // 類別名稱(包括命名空間與類別名稱, 用 . 分隔)
        public string Component = ""; // 組件名稱
        //-------------------------------------
    }
    /**
     * @brief 資料庫類別
     */
    public class SDatabase
    {
        //-------------------------------------
        public string Name = ""; // 識別名稱
        public string Type = ""; // 型態字串
        public string DBAddr = ""; // 資料庫位址
        public string DBName = ""; // 資料庫名稱
        public string UserID = ""; // 資料庫帳號
        public string Password = ""; // 資料庫密碼
        //-------------------------------------
    }
    /**
     * @brief 網路類別
     */
    public class SNetwork
    {
        //-------------------------------------
        public string Name = ""; // 識別名稱
        public string Addr = ""; // 網路位址
        public int Connect = 0; // 網路連線數
        //-------------------------------------
    }
    /**
     * @brief 伺服器類別
     */
    public class SServer
    {
        //-------------------------------------
        public string Name = ""; // 識別名稱
        public string Main = ""; // 主要元件名稱
        public SNetwork[] NetClient = new SNetwork[0]; // 客戶端網路列表
        public SNetwork[] NetServer = new SNetwork[0]; // 伺服器網路列表
        //-------------------------------------
    }
    /**
     * @brief 設定類別
     */
    public class Setup
    {
        //-------------------------------------
        public string Name = ""; // 識別名稱
        public string Version = ""; // 平台版本
        public SDBF[] DBF = new SDBF[0]; // dbf列表
        public SDatabase[] Database = new SDatabase[0]; // 資料庫列表
        public SServer[] Server = new SServer[0]; // 伺服器列表
        //-------------------------------------
    }
}
//-----------------------------------------------------------------------------