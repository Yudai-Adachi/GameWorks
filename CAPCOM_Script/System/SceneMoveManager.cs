using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Manager
{
    public class SceneMoveManager : SingletonBase<SceneMoveManager>
    {
        // Start is called before the first frame update
        #region Enum

        public enum SceneType
        {
            Title,
            Game,
            Result,

            Max,
        }

        public List<string> SceneNameList = new List<string>();

        public bool Move = false;

        private bool _IsFadeing = false;

        #endregion

        #region Property

        /// <summary>
        /// 現在のシーン状態
        /// </summary>
        public SceneType CurrentScene
        {
            get;
            set;
        } = SceneType.Max;//! invalid

        private SceneType _NextScene = SceneType.Max;
        public SceneType NextScene
        {
            get
            {
                return _NextScene;
            }
            set
            {
                Debug.Log("Move->" + value.ToString());
                _NextScene = value;
            }
        }

        #endregion

        #region Public Method

        public bool MoveScene(SceneType type)
        {
            // Debug.Log("Move->" + type.ToString());
            if (type == CurrentScene)
            {
                Debug.Log($"移動先が一緒 : {type.ToString()}");
                return false;
            }

            if (_IsFadeing)
            {
                Debug.Log($"フェード中");
                return false;
            }


            Debug.Log("Move->" + type.ToString() + ":" + SceneNameList[(int)(type)]);
            UnityEngine.SceneManagement.SceneManager.LoadScene(SceneNameList[(int)(type)]);

            CurrentScene = type;
            // NextScene = type;
            if (CurrentScene == SceneType.Game)
            {
                //! kaetai 
                MainGameManager.Instance.StartGame();
            }

            return true;
        }

        public bool SetNextScene(SceneType type)
        {
            //  Debug.Log("Move->" + type.ToString());
            if (type == CurrentScene)
            {
                Debug.Log($"移動先が一緒 : {type.ToString()}");
                return false;
            }

            if (_IsFadeing)
            {
                Debug.Log($"フェード中");
                return false;
            }
            Move = true;
            return true;
        }

        #endregion

        #region Private Method

        private void Awake()
        {
            Application.targetFrameRate = 60;

            //! とりあえず固定値でシーン名入れていく
            SceneNameList.Add("TitleScene");
            SceneNameList.Add("Marge");
            SceneNameList.Add("ResultScene");

            DontDestroyOnLoad(this);
        }

        private void Start()
        {
            //! 初期シーンに移行
            MoveScene(SceneType.Title);
        }

        public bool Test = false;

        private void Update()
        {
            if (Input.GetKey(KeyCode.Escape))
            {
#if UNITY_EDITOR
                UnityEditor.EditorApplication.isPlaying = false;
#elif UNITY_STANDALONE
    UnityEngine.Application.Quit();
#endif
            }

            switch (CurrentScene)
            {
                case SceneType.Title:
                    {
                        //! test
                        if (Test)
                        {
                            Test = false;
                            // Debug.Log("test");
                            Move = true;
                            // NextScene = (SceneType)(((int)CurrentScene + 1) % (int)(SceneType.Max));
                            //Debug.Log(NextScene.ToString());
                            NextScene = SceneType.Game;
                        }
                    }
                    break;
                case SceneType.Result:
                    {
                        //! test
                        if (Input.GetKey(KeyCode.Space))
                        {
                            // Debug.Log("test");
                            Move = true;
                            // NextScene = (SceneType)(((int)CurrentScene + 1) % (int)(SceneType.Max));
                            //Debug.Log(NextScene.ToString());
                            NextScene = SceneType.Title;
                        }
                    }
                    break;
                case SceneType.Game:
                    {
                        if (MainGameManager.Instance.State == MainGameManager.GameState.End)
                        {
                            NextScene = SceneType.Result;
                            MainGameManager.Instance.State = MainGameManager.GameState.None;
                            Move = true;
                        }
                    }
                    break;
            }
            //  Debug.Log(NextScene.ToString());



            if (Move)
            {
                StartCoroutine(nameof(MoveSceneCoroutine));

                Move = false;
            }
        }

        private IEnumerator MoveSceneCoroutine()
        {
            _IsFadeing = true;
            //! fadeout
            bool success = FadeManager.Instance.StartFadeOut();
            if (!success)
            {
                _IsFadeing = false;
                yield break;
            }

            while (FadeManager.Instance.State != FadeManager.FadeState.None)
            {
                //   Debug.Log("out");
                yield return null;
            }
            _IsFadeing = false;
            // Debug.Log("Move")
            //  Debug.Log("Move->" + NextScene.ToString());
            //while (!MoveScene(NextScene))
            //{
            //    yield return null;
            //}
            MoveScene(NextScene);
            _IsFadeing = true;

            //  MoveScene((SceneType)(((int)(CurrentScene) + 1) % ((int)SceneType.Max)));

            success = FadeManager.Instance.StateFadeIn();
            if (!success)
            {
                _IsFadeing = false;
                yield break;
            }
            while (FadeManager.Instance.State != FadeManager.FadeState.None)
            {
                //  Debug.Log("in");
                yield return null;
            }

            _IsFadeing = false;
        }


        #endregion
    }
}
