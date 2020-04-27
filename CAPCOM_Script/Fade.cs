using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;


public class Fade : MonoBehaviour
{
    SpriteRenderer mySpriteRenderer;

    public float speed;

    public Type fadeType;

    public enum Type
    {
        FADEIN,
        FADEOUT
    }

    // Start is called before the first frame update
    void Start()
    {
        mySpriteRenderer = GetComponent<SpriteRenderer>();
        mySpriteRenderer.color = new Vector4(0, 0,0, 0);
    }

    // Update is called once per frame
    void Update()
    {
        if (fadeType == Type.FADEIN)
            FadeIn();
        else if (fadeType == Type.FADEOUT)
            FadeOut();
    }

    void FadeIn()
    {
        if(mySpriteRenderer.color.a>0.0f)
        {
            mySpriteRenderer.color = new Vector4(1, 1, 1, mySpriteRenderer.color.a - speed*Time.deltaTime);
        }
        else
        {
            mySpriteRenderer.color = new Vector4(1, 1, 1, 0);
        }
    }

    void FadeOut()
    {
        if (mySpriteRenderer.color.a < 1.0f)
        {
            mySpriteRenderer.color = new Vector4(1, 1, 1, mySpriteRenderer.color.a + speed * Time.deltaTime);
        }
        else
        {
            mySpriteRenderer.color = new Vector4(1, 1, 1, 1);
            SceneManager.LoadScene("Marge");
        }
    }

    public void changeToFadeOut()
    {
        fadeType = Type.FADEOUT;
    }
}
