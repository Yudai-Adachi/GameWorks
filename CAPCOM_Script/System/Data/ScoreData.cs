using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Data
{
    [System.Serializable]
    public class ScoreData
    {
        public int Score = 0;

        public bool IsNew = false;

        public string Name = "";
    }

    [System.Serializable]
    public class RankingData
    {
        public List<ScoreData> ScoreList = new List<ScoreData>();
    }
}