using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;


public class Goal : MonoBehaviour
{
    //public Text Point_text;
    public GameObject desk_position;

    int score;
    float xDis;
    float yDis;
    double distance;

    // Start is called before the first frame update
    void Start()
    {
        score = 0;
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void OnCollisionEnter(Collision other)
    {
        //other.ClosestPoint
        if (other.transform.position.x > 0.1f && other.transform.position.y < 0.4f)
        {
            xDis = other.transform.position.x - desk_position.transform.position.x;
            yDis = other.transform.position.z - desk_position.transform.position.z;

            distance = Math.Sqrt((xDis * xDis) + (yDis * yDis));
            if(distance <= 0.09f)
            {
                Debug.Log("当たり");
            }

            score += 10;
            //Point_text.text = score.ToString();
        }
    }
}