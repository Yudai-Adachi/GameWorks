using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Score200 : MonoBehaviour
{
    public Text TotalScore;

    public GameObject frame1;
    public GameObject frame2;
    public GameObject frame3;
    public GameObject frame4;

    public GameObject food3;

    GameObject food3_temp;

    Rigidbody rb;

    bool tempkun;
    bool score_trans;

    // Start is called before the first frame update
    void Start()
    {
        rb = food3.GetComponent<Rigidbody>();
        food3_temp = Instantiate(food3, new Vector3(-24.59924f, -0.3272538f, -21f), Quaternion.identity);
        food3_temp.GetComponent<MeshCollider>().enabled = false;
        rb.useGravity = false;

        food3_temp.transform.localScale = new Vector3(30, 30, 30);

        tempkun = false;
        score_trans = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (Score10.Score >= 400)
        {
            score_trans = true;
        }

        Vector3 temp;
        Vector3 temp_food;

        temp = this.transform.position;
        temp_food = food3_temp.transform.position;
        if (!tempkun && score_trans)
        {
            temp.y += 0.1f;
            temp_food.y += 0.1f;
        }

        if (tempkun && score_trans)
        {
            temp.y -= 0.1f;
            temp_food.y -= 0.1f;
        }

        if (this.transform.position.y >= 8.0f)
        {
            tempkun = true;
        }

        if (this.transform.position.y <= -0.30f)
        {
            tempkun = false;
        }

        this.transform.position = temp;
        food3_temp.transform.position = temp_food;
    }

    public void OnTriggerEnter(Collider other)
    {
        Score10.conbo++;

        if (other.gameObject.name == "Wine Variant(Clone)")
        {
            Score10.Score += 10;
        }

        if (Score10.conbo < 5)
        {
            Score10.Score += 200;
        }

        if (Score10.conbo >= 5 && Score10.conbo < 10)
        {
            Score10.Score += 240;
        }

        if (Score10.conbo >= 10)
        {
            Score10.Score += 300;
        }

        TotalScore.text = Score10.Score.ToString();
        frame1.GetComponent<Renderer>().material.color = Color.red;
        frame2.GetComponent<Renderer>().material.color = Color.red;
        frame3.GetComponent<Renderer>().material.color = Color.red;
        frame4.GetComponent<Renderer>().material.color = Color.red;
        StartCoroutine("White");
    }

    IEnumerator White()
    {
        yield return new WaitForSeconds(0.2f);
        frame1.GetComponent<Renderer>().material.color = Color.black;
        frame2.GetComponent<Renderer>().material.color = Color.black;
        frame3.GetComponent<Renderer>().material.color = Color.black;
        frame4.GetComponent<Renderer>().material.color = Color.black;
        //StartCoroutine("Red");
    }

    /*
    IEnumerator Red()
    {
        yield return new WaitForSeconds(0.2f);
        frame1.GetComponent<Renderer>().material.color = Color.red;
        frame2.GetComponent<Renderer>().material.color = Color.red;
        frame3.GetComponent<Renderer>().material.color = Color.red;
        frame4.GetComponent<Renderer>().material.color = Color.red;
        StartCoroutine("White2");
    }

    IEnumerator White2()
    {
        yield return new WaitForSeconds(0.2f);
        frame1.GetComponent<Renderer>().material.color = Color.black;
        frame2.GetComponent<Renderer>().material.color = Color.black;
        frame3.GetComponent<Renderer>().material.color = Color.black;
        frame4.GetComponent<Renderer>().material.color = Color.black;
    }
    */
}
