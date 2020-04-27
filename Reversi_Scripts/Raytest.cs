using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Leap;
using UnityEngine.UI;

public class Raytest : MonoBehaviour
{
    int distance;
    int R_extendedFingers = 0;
    int L_extendedFingers = 0;
    int FingerCounts;
    int i_count;
    int j_count;

    char[] temp_count;

    bool fin1;
    bool fin2;
    bool fin3;
    bool fin4;
    bool fin5;

    public static float reap_time;
    public static bool changeOK;

    Hand handR, handL;

    Vector3 ray_position;
    Vector3 temp;
    Vector3 temp_outside;

    string outside_name;


    public GameObject now;
    GameObject now_temp;
    Controller controller = new Controller();
    //Quaternion fingerRotation_q;
    //Vector3 fingerRotation_v;
    AudioSource audio;

    // Start is called before the first frame update
    void Start()
    {
        distance = 10;
        temp_count = new char[2];

        audio = this.GetComponent<AudioSource>();
        //Debug.Log("audio1 " + audio1);
        //Debug.Log("audio2 " + audio2);
    }

    // Update is called once per frame
    void Update()
    {
        
        Frame frame = controller.Frame();
        FingerList fingers = frame.Fingers;
        /*

        for (int i = 0; i < fingers.Count; i++)
        {  // 見つかった全ての指について
            Finger finger = fingers[i];           // 指 i を取得（0:親指, 1:人差し指, 2:中指, 3:薬指, 4:小指）
            Debug.Log(finger.);
        }
        */
        R_extendedFingers = 0;
        L_extendedFingers = 0;

        frame = controller.Frame();          //コントローラーからフレームを作る。

        handR = frame.Hands.Rightmost;           //一番右の手を取得する。
        if (handR != frame.Hands.Leftmost)
        {
            handL = frame.Hands.Leftmost;
        }

        FingerCounts = frame.Fingers.Count;      //指の数を取得

        if(handR.Fingers[0].IsExtended)
        {
            fin1 = true;
        }
        else
        {
            fin1 = false;
        }
        if (handR.Fingers[0].IsExtended)
        {
            fin2 = true;
        }
        else
        {
            fin2 = false;
        }
        if (handR.Fingers[0].IsExtended)
        {
            fin3 = true;
        }
        else
        {
        fin3 = false;
        }
        if (handR.Fingers[0].IsExtended)
        {
            fin3 = true;
        }
        else
        {
            fin4 = false;
        }
        if (handR.Fingers[0].IsExtended)
        {
            fin5 = true;
        }
        else
        {
            fin5 = false;
        }

        if (fin1 && fin2 && fin3 && fin4 && fin5)
        {
            //
        }

        //fingerRotation_q = this.transform.rotation;
        //fingerRotation_v = fingerRotation_q.eulerAngles;
        //Ray ray = new Ray(this.transform.position, fingerRotation_v);
        if (this.transform.position.x < 0)
        {
            Ray ray = new Ray(this.transform.position, new Vector3(this.transform.position.x * 2, (this.transform.position.y + 3.0f) * 2, this.transform.position.z + 5));
            RaycastHit hit;

            if (Physics.Raycast(transform.position, transform.forward, out hit, distance))
            {
                if (hit.collider.tag == "block")
                {
                    if (now_temp == null)
                    {
                        now_temp = Instantiate(now, hit.collider.gameObject.transform.position, Quaternion.Euler(0.0f, 0f, 0f));
                    }
                    else
                    {
                        now_temp.transform.position = hit.collider.gameObject.transform.position;
                        Debug.Log("position : " + now_temp.transform.position);

                        temp_outside = now_temp.transform.position;
                        outside_name = hit.collider.gameObject.name;
                    }

                    if (temp == hit.collider.gameObject.transform.position)
                    {
                        reap_time += Time.deltaTime;
                    }
                    else
                    {
                        reap_time = 0;
                    }
                    temp = hit.collider.gameObject.transform.position;

                    if (reap_time >= 1.00f)
                    {
                        int count = 0;
                        string b = hit.collider.gameObject.name;
                        //Debug.Log(now_temp_local);
                        foreach (char a in b)
                        {
                            count++;
                            if (count == 1)
                            {
                                j_count = int.Parse(a.ToString());
                            }
                            if (count == 2)
                            {
                                i_count = int.Parse(a.ToString());
                            }
                        }

                        if (blackAgent.board[i_count, j_count] == 4)
                        {
                            audio.Play();
                            whiteAgent.i_count = i_count;
                            whiteAgent.j_count = j_count;
                            blackAgent.board[i_count, j_count] = -1;
                            changeOK = true;
                        }
                        count = 0;
                        reap_time = 0;
                    }
                }
            }
            else
            {
                Destroy(now_temp);
                /*
                if (now_temp)
                {
                    now_temp.transform.position = temp_outside;
                    reap_time++;

                    if (reap_time >= 1.00f)
                    {
                        int count = 0;
                        string b = outside_name;
                        //Debug.Log(now_temp_local);
                        foreach (char a in b)
                        {
                            count++;
                            if (count == 1)
                            {
                                j_count = int.Parse(a.ToString());
                            }
                            if (count == 2)
                            {
                                i_count = int.Parse(a.ToString());
                            }
                        }

                        if (blackAgent.board[i_count, j_count] == 4)
                        {
                            audio.Play();
                            whiteAgent.i_count = i_count;
                            whiteAgent.j_count = j_count;
                            blackAgent.board[i_count, j_count] = -1;
                            changeOK = true;
                        }
                        count = 0;
                        reap_time = 0;
                    }
                }
                */
            }
        }
        else
        {
            Ray ray = new Ray(this.transform.position, new Vector3(this.transform.position.x * 2, (this.transform.position.y + 3.0f) * 2, this.transform.position.z + 5));
            RaycastHit hit;

            Debug.DrawLine(this.transform.position, ray.direction * distance, Color.red);

            //if (Physics.Raycast(ray, out hit, distance))
            if (Physics.Raycast(transform.position, transform.forward, out hit, distance))
            {
                if (hit.collider.tag == "block")
                {
                    if (now_temp == null)
                    {
                        now_temp = Instantiate(now, hit.collider.gameObject.transform.position, Quaternion.Euler(0.0f, 0f, 0f));
                    }
                    else
                    {
                        now_temp.transform.position = hit.collider.gameObject.transform.position;
                        Debug.Log("position : " + now_temp.transform.position);

                        temp_outside = now_temp.transform.position;
                        outside_name = hit.collider.gameObject.name;
                    }

                    //Debug.Log("temp" + temp + "position" + hit.collider.gameObject.transform.position);

                    if (temp == hit.collider.gameObject.transform.position)
                    {
                        reap_time += Time.deltaTime;
                    }
                    else
                    {
                        reap_time = 0;
                    }

                    temp = hit.collider.gameObject.transform.position;

                    if (reap_time >= 1.00f)
                    {
                        int count = 0;
                        string b = hit.collider.gameObject.name;
                        //Debug.Log(now_temp_local);
                        foreach (char a in b)
                        {
                            count++;
                            if (count == 1)
                            {
                                j_count = int.Parse(a.ToString());
                            }
                            if (count == 2)
                            {
                                i_count = int.Parse(a.ToString());
                            }
                        }

                        if (blackAgent.board[i_count,j_count] == 4)
                        {
                            audio.Play();
                            whiteAgent.i_count = i_count;
                            whiteAgent.j_count = j_count;
                            blackAgent.board[i_count, j_count] = -1;
                            changeOK = true;
                        }
                        count = 0;
                        reap_time = 0;
                    }
                }
            }
            else
            {
                Destroy(now_temp);
                /*
                if (now_temp)
                {
                    now_temp.transform.position = temp_outside;
                    reap_time++;

                    if (reap_time >= 1.00f)
                    {
                        int count = 0;
                        string b = outside_name;
                        //Debug.Log(now_temp_local);
                        foreach (char a in b)
                        {
                            count++;
                            if (count == 1)
                            {
                                j_count = int.Parse(a.ToString());
                            }
                            if (count == 2)
                            {
                                i_count = int.Parse(a.ToString());
                            }
                        }

                        if (blackAgent.board[i_count, j_count] == 4)
                        {
                            audio.Play();
                            whiteAgent.i_count = i_count;
                            whiteAgent.j_count = j_count;
                            blackAgent.board[i_count, j_count] = -1;
                            changeOK = true;
                        }
                        count = 0;
                        reap_time = 0;
                    }
                }
                */
            }
        }

        //Debug.Log(new Vector3(this.transform.position.x * 2, this.transform.position.y * 2, this.transform.position.z + 10));
    }

    private void OnDrawGizmos()
    {
        Debug.DrawLine(this.transform.position, transform.position + transform.forward * distance, Color.yellow);
    }

    public void SetActive(bool temp)
    {
        if (temp)
        {
            this.GetComponent<Raytest>().enabled = true;
        }
        else
        {
            this.GetComponent<Raytest>().enabled = false;
        }
    }

    public void OnDestroy()
    {
        Destroy(now_temp);
    }
}
