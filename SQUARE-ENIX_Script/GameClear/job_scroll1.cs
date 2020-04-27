using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class job_scroll1 : MonoBehaviour
{
    public GameObject text;
    public GameObject text1;
    public GameObject text2;
    public GameObject text3;
    public GameObject text4;
    public GameObject text5;
    public GameObject text6;
    public GameObject text7;
    public GameObject text8;
    public GameObject text9;

    Vector3 position;
    Vector3 position1;
    Vector3 position2;
    Vector3 position3;
    Vector3 position4;
    Vector3 position5;
    Vector3 position6;
    Vector3 position7;
    Vector3 position8;
    Vector3 position9;

    // Start is called before the first frame update
    void Start()
    {
            DontDestroyOnLoad(this);
    }

    // Update is called once per frame
    void Update()
    {
        position = text.transform.position;
		position.y += 3.0f;
        text.transform.position = position;

        position1 = text1.transform.position;
        position1.y += 3.0f;
        text1.transform.position = position1;

        position2 = text2.transform.position;
        position2.y += 3.0f;
        text2.transform.position = position2;

        position3 = text3.transform.position;
        position3.y += 3.0f;
        text3.transform.position = position3;

        position4 = text4.transform.position;
        position4.y += 3.0f;
        text4.transform.position = position4;

        position5 = text5.transform.position;
        position5.y += 3.0f;
        text5.transform.position = position5;

        position6 = text6.transform.position;
        position6.y += 3.0f;
        text6.transform.position = position6;

        position7 = text7.transform.position;
        position7.y += 3.0f;
        text7.transform.position = position7;

        position8 = text8.transform.position;
        position8.y += 3.0f;
        text8.transform.position = position8;

        position9 = text9.transform.position;
        position9.y += 3.0f;
        text9.transform.position = position9;

        if(text9.transform.localPosition.y > 800.0f)
        {
            SceneManager.LoadScene("GameClear2");
        }
    }
}
