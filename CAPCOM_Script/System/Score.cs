using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Manager
{
    public class Score : MonoBehaviour
    {
        Data.RankingData Ranking;

        /// <summary>
        /// ハードコード…
        /// </summary>
        public Text Text01;
        public Text Text02;
        public Text Text03;
        public Text Text04;
        public Text Text05;

        private List<Text> TextList = new List<Text>();

        // Start is called before the first frame update
        void Start()
        {
            if(ScoreManager.Instance==null)
            {
                return;
            }
            Ranking = ScoreManager.Instance.Ranking;

            TextList = new List<Text>();
            TextList.Add(Text01);
            TextList.Add(Text02);
            TextList.Add(Text03);
            TextList.Add(Text04);
            TextList.Add(Text05);

            ScoreManager.Instance.SaveScore();
        }

        // Update is called once per frame
        void Update()
        {
            UpdateDraw();
        }

        public Color NewColor = Color.red;
        public Color OldColor = Color.white;



        private void UpdateDraw()
        {
            if (ScoreManager.Instance == null)
            {
                return;
            }
            for (int i = 0; i < ScoreManager.Instance.RankingNum; ++i)
            {
                if (i >= TextList.Count)
                {
                    break;
                }
                if (TextList[i] == null || Ranking.ScoreList[i] == null)
                {
                    break;
                }
                TextList[i].text = string.Format("{0:D7}", Ranking.ScoreList[i].Score);
                if (Ranking.ScoreList[i].IsNew)
                {
                    TextList[i].color = NewColor;
                }
                else
                {
                    TextList[i].color = OldColor;
                }
            }
        }
    }
}