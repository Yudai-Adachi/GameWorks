using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Manager
{
    /// <summary>
    /// Singleton Class base
    /// </summary>
    public abstract class SingletonBase<T> : MonoBehaviour where T : MonoBehaviour
    {
        #region Property

        private static T _Instance = null;

        public static T Instance
        {
            get
            {
                if (_Instance == null)
                {
                    Type t = typeof(T);

                    _Instance = (T)FindObjectOfType(t);
                }
                return _Instance;
            }
        }

        #endregion

        #region Private Method

        void Awake()
        {
            DontDestroyOnLoad(this);
        }

        #endregion
    }
}