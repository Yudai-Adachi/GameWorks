using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Manager
{
    public class MainGameManager : SingletonBase<MainGameManager>
    {
        #region Field

        /// <summary>
        /// ゲーム時間(秒単位)
        /// </summary>
        public float GameSecond = 5f;

        /// <summary>
        /// 残り時間
        /// </summary>
        private float _Time;

        public enum GameState
        {
            None,
            Start,
            Game,
            End,
        }

        public GameState State = GameState.None;


        #endregion

        public void StartGame()
        {
            if (State != GameState.None)
            {
                return;
            }
            _Time = GameSecond;
            State = GameState.Start;
        }

        public int GetTimeToInt()
        {
            return (int)_Time;
        }

        #region Private Method

        private void Update()
        {
            switch (State)
            {
                case GameState.Game:
                    {
                        _Time -= Time.deltaTime;

                    //    Debug.Log(_Time);
                        if (_Time <= 0)
                        {
                            //! スコアを取得
                            var score = 0;
                            // typeで指定した型の全てのオブジェクトを配列で取得し,その要素数分繰り返す.
                            foreach (GameObject obj in UnityEngine.Object.FindObjectsOfType(typeof(GameObject)))
                            {
                                // シーン上に存在するオブジェクトならば処理.
                                if (obj.activeInHierarchy)
                                {
                                    var score10 = obj.GetComponent<Score10>();
                                    if(score10!=null)
                                    {
                                        score = Score10.Score;
                                    }
                                }
                            }

                            var data = new Data.ScoreData();
                            data.Score = score;
                            data.IsNew = true;
                            ScoreManager.Instance.AddScore(data);
                            //! ゲーム終了
                            State = GameState.End;
                         //   SceneMoveManager.Instance.SetNextScene(SceneMoveManager.SceneType.Result);
                        }
                    }
                    break;
                case GameState.End:
                    {
                        //  State = GameState.None;
                    }
                    break;
                case GameState.Start:
                    {
                        //! カウントダウンしたい
                        State = GameState.Game;
                    }
                    break;
            }

        }



        #endregion
    }
}