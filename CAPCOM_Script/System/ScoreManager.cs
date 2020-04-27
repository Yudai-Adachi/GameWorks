using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Manager
{
    public class ScoreManager : SingletonBase<ScoreManager>
    {
        public int RankingNum = 5;

        public Data.RankingData Ranking = new Data.RankingData();

        private string _RankingTag = "RANKING";



        public void LoadScore()
        {

            string json = PlayerPrefs.GetString(_RankingTag);
            Ranking = JsonUtility.FromJson<Data.RankingData>(json);

            //! 足りない分足す
            while (Ranking.ScoreList.Count < RankingNum)
            {
                var data = new Data.ScoreData();
                Ranking.ScoreList.Add(data);
            }

            Ranking.ScoreList.Sort((a, b) => b.Score - a.Score);
        }

        public void AddScore(Data.ScoreData data)
        {
            Data.ScoreData min = null;
            if(Ranking?.ScoreList==null )
            {
                Ranking = new Data.RankingData();
                Ranking.ScoreList = new List<Data.ScoreData>();
                for(int i=0;i<RankingNum;++i)
                {
                    Ranking.ScoreList.Add(new Data.ScoreData());
                }
            }
            for (int i = 0; i < Ranking.ScoreList.Count; ++i)
            {
                if (min == null || min.Score > Ranking.ScoreList[i].Score)
                    min = Ranking.ScoreList[i];
                Ranking.ScoreList[i].IsNew = false;
            }

            if (data.Score >= min.Score)
            {
                data.IsNew = true;
                Ranking.ScoreList.Remove(min);
                Ranking.ScoreList.Add(data);
                Ranking.ScoreList.Sort((a, b) => b.Score - a.Score);
            }

            SaveScore();
        }

        public void SaveScore()
        {
            if (Ranking == null)
            {
                LoadScore();
            }
            string json = JsonUtility.ToJson(Ranking);
            PlayerPrefs.SetString(_RankingTag, json);
        }

        // Start is called before the first frame update
        void Start()
        {
            LoadScore();

        }

        public bool test = false;

        // Update is called once per frame
        void Update()
        {
     
            //if (test)
            //{
            //    var data = new Data.ScoreData();
            //    data.Score = 100;
            //    AddScore(data);
            //}
        }




    }
}