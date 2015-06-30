/**
 * @file formtable.cs
 * @note 表格組件
 * @author yinweli
 */
//-----------------------------------------------------------------------------
using System.Collections.Generic;
using System.Collections;
using System.IO;
using System.Linq;
using System.Text;
using System;
//-----------------------------------------------------------------------------
namespace LibCSNStandard
{
    /**
     * @brief 表格類別
     */
    public class FormTable
    {
        //-------------------------------------
        public char Vertical = '|'; // 直線字元
        public char Horizontal = '-'; // 橫線字元
        public char Cross = '+'; // 交錯字元
        //-------------------------------------
        private Dictionary<string, string> m_Data = new Dictionary<string, string>(); // 表格列表 <座標字串, 內容字串>
        private int m_iSizeX = 0; // x軸長度
        private int m_iSizeY = 0; // y軸長度
        //-------------------------------------
        /**
         * @brief 清除全部
         */
        public void Clear()
        {
            m_Data.Clear();
            m_iSizeX = 0;
            m_iSizeY = 0;
        }
        /**
         * @brief 設定內容
         * @param iX x軸座標
         * @param iY y軸座標
         * @param szData 資料字串
         */
        public void Set(int iX, int iY, string szData)
        {
            m_Data[StringCoor(iX, iY)] = szData;
            m_iSizeX = Math.Max(m_iSizeX, iX + 1);
            m_iSizeY = Math.Max(m_iSizeY, iY + 1);
        }
        /**
         * @brief 新增內容
         * @param Param 參數列表
         */
        public void Add(params string[] Param)
        {
            int iX = 0;
            int iY = m_iSizeY;

            foreach (string Itor in Param)
                m_Data[StringCoor(iX++, iY)] = Itor;

            m_iSizeX = Math.Max(m_iSizeX, iX);
            m_iSizeY = Math.Max(m_iSizeY, iY + 1);
        }
        /**
         * @brief 輸出表格
         * @return 結果列表
         */
        public List<string> ExportList()
        {
            if (m_Data.Count <= 0)
                return new List<string>();

            List<string> Result = new List<string>();
            List<int> Len = Length();
            string szLine = StringLine(Len);

            Result.Add(szLine);

            for (int iY = 0; iY < m_iSizeY; ++iY)
            {
                List<string> Data = new List<string>();

                for (int iX = 0; iX < m_iSizeX; ++iX)
                {
                    string szCoor = StringCoor(iX, iY);

                    Data.Add(m_Data.ContainsKey(szCoor) ? m_Data[szCoor] : "");
                }//for

                Result.Add(StringData(Len, Data, iY == 0));
                Result.Add(szLine);
            }//for

            return Result;
        }
        /**
         * @brief 輸出表格
         * @return 結果字串
         */
        public string ExportString()
        {
            string szResult = "";

            foreach (string Itor in ExportList())
                szResult += Itor + "\n";

            return szResult;
        }
        //-------------------------------------
        /**
         * @brief 取得字串位元數
         * @param szData 資料字串
         * @return 位元數
         */
        private int Bytes(string szData)
        {
            return Encoding.Default.GetByteCount(szData);
        }
        /**
         * @brief 取得長度列表
         * @return 長度列表
         */
        private List<int> Length()
        {
            List<int> Result = new List<int>();

            for (int iX = 0; iX < m_iSizeX; ++iX)
            {
                Result.Add(0);

                for (int iY = 0; iY < m_iSizeY; ++iY)
                {
                    string szCoor = StringCoor(iX, iY);

                    if (m_Data.ContainsKey(szCoor))
                        Result[Result.Count - 1] = Math.Max(Result.Last(), Bytes(m_Data[szCoor]));
                }//for
            }//for

            return Result;
        }
        /**
         * @brief 取得座標字串
         * @param iX x軸座標
         * @param iY y軸座標
         * @return 座標字串
         */
        private string StringCoor(int iX, int iY)
        {
            return iY + ":" + iX;
        }
        /**
         * @brief 建立格線字串
         * @param Len 長度列表
         * @return 格線字串
         */
        private string StringLine(List<int> Len)
        {
            string szResult = "";

            for (int iPos = 0; iPos < Len.Count; ++iPos)
            {
                szResult += new string(Horizontal, Len[iPos]);

                if (iPos + 1 < Len.Count)
                    szResult += Cross;
            }//for

            return szResult;
        }
        /**
         * @brief 建立內容字串
         * @param Len 長度列表
         * @param Data 資料列表
         * @param bAlign 對齊旗標
         * @return 內容字串
         */
        private string StringData(List<int> Len, List<string> Data, bool bAlign)
        {
            if (Len.Count != Data.Count)
                return "";

            string szResult = "";

            for (int iPos = 0; iPos < Data.Count; ++iPos)
            {
                string szData = Data[iPos];
                int iLenColumn = Len[iPos];
                int iLenData = Bytes(szData);
                int iSpaceF = bAlign ? Math.Max(0, (iLenColumn - iLenData) / 2) : 0; // 計算前置的cFill字元數量
                int iSpaceB = Math.Max(0, iLenColumn - iSpaceF - iLenData); // 計算後置的cFill字元數量

                szResult += new string(' ', iSpaceF) + szData + new string(' ', iSpaceB);

                if (iPos + 1 < Len.Count)
                    szResult += Vertical;
            }//for

            return szResult;
        }
        //-------------------------------------
    }
}
//-----------------------------------------------------------------------------