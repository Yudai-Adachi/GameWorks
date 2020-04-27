using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Manager
{
    public class FadeManager : SingletonBase<FadeManager>
    {
        public GameObject Canvas = null;
        private Image _Image = null;

        public float FadeSpeed = 0.1f;

        public enum FadeState
        {
            None,
            FadeOut,
            FadeIn,
        }

        public FadeState State = FadeState.None;

        private void Start()
        {

            _Image = Canvas?.GetComponent<Image>();
        }

        private void Update()
        {
            if (_Image == null)
            {
                return;
            }
            var color = _Image.color;
            switch (State)
            {
                case FadeState.FadeIn:
                    {
                        color = new Color(color.r, color.g, color.b, color.a - FadeSpeed);
                        _Image.color = color;
                        if(color.a<=0)
                        {
                            State = FadeState.None;
                        }
                    }
                    break;
                case FadeState.FadeOut:
                    {
                        color = new Color(color.r, color.g, color.b, color.a + FadeSpeed);
                        _Image.color = color;
                        if (color.a >= 2f)
                        {
                            State = FadeState.None;
                        }
                    }
                    break;
            }
           // Debug.Log(color.a);
        }

        public bool StartFadeOut()
        {
            if (State != FadeState.None)
            {
                return false;
            }
            if (_Image == null)
            {
                return false;
            }

            State = FadeState.FadeOut;
            return true;
        }

        public bool StateFadeIn()
        {
            if (State != FadeState.None)
            {
                return false;
            }
            if (_Image == null)
            {
                return false;
            }
            State = FadeState.FadeIn;
            return true;
        }


    }
}