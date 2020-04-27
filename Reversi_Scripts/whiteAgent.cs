using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using MLAgents;
using UnityEngine.SceneManagement;
using UnityEngine.UI;


public class whiteAgent : Agent
{
    blackAgent black;
    Raytest ray;

    public GameObject piece_white;
    public GameObject panel;
    public GameObject now;

    public GameObject win;
    public GameObject lose;
    public GameObject draw;

    public GameObject[,] piece_temp;
    public Text black_count;
    public Text white_count;
    //GameObject now_temp;
    bool[,] reverse_OK;

    public static int i_count;
    public static int j_count;
    int up_count;
    int temp_count_tate;
    int temp_count_yoko;
    int reverse_white_count;
    int delete_count;
    int judge_white;
    int judge_black;
    int reverse_ok_i;
    int reverse_ok_j;
    public int reset_count = 0;

    bool reset_now;

    bool turn_time;
    bool white_OK_sign;
    public bool white_initialize;
    bool white_position_initialize;

    Vector3 temp_vec;

    // Start is called before the first frame update
    void Start()
    {
        i_count = 4;
        j_count = 4;
        up_count = 0;
        temp_count_tate = 0;
        temp_count_yoko = 0;
        delete_count = 0;
        white_initialize = true;
        white_position_initialize = true;

        piece_temp = new GameObject[10, 10];
        reverse_OK = new bool[10, 10];

        black = GameObject.Find("black_Agent").GetComponent<blackAgent>();
    }

    public void change(int i_count, int j_count)
    {
        if (blackAgent.board[i_count, j_count] == -1)
        {
            blackAgent.piece_temp[i_count, j_count] = Instantiate(piece_white, new Vector3(i_count - 4 - 0.5f, 4 - j_count - 4.5f, 4.9f), Quaternion.Euler(-90.0f, 0f, 0f));
        }
    }

    public void Change_After_White(int count_yoko, int count_tate)                                                    //下に置いた時
    {
        int temp = i_count;
        temp_count_yoko = count_yoko;
        temp_count_tate = count_tate;

        if (blackAgent.board[i_count, j_count] == -1)//今いるマスが黒なら
        {
            while (blackAgent.board[count_yoko, count_tate] != 9)//----------------------------------------------------------------------------------------------1
            {
                count_tate--;
                if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == -1 || blackAgent.board[count_yoko, count_tate] == 0))   //１つ上のコマが黒or無なら終了
                {
                    break;
                }
                else if (up_count > 0)
                {
                    if (blackAgent.board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                    {
                        for (int i = j_count; i > count_tate; i--)
                        {
                            reverse_white_count++;
                            blackAgent.board[count_yoko, i] = -1;                                                          //全てを反転
                            if (delete_count > 0)
                            {
                                if (blackAgent.piece_temp[count_yoko, i] != null)
                                {
                                    blackAgent.piece_temp[count_yoko, i].transform.rotation = Quaternion.Euler(-90.0f, 0.0f, 0.0f);
                                }
                            }
                            delete_count++;
                        }
                        reverse_white_count--;
                        break;
                    }
                    if (blackAgent.board[count_yoko, count_tate] == 0)
                    {
                        break;
                    }
                }
                else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                {
                    up_count++;
                }
            }
            up_count = 0;
            delete_count = 0;
            count_tate = temp_count_tate;
            count_yoko = temp_count_yoko;
            //------------------------------------------------------------------------------------------------------------------------------------------2
            while (blackAgent.board[count_yoko, count_tate] != 9)
            {
                count_tate--;
                count_yoko--;
                if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == -1 || blackAgent.board[count_yoko, count_tate] == 0))   //１つ上のコマが黒or無なら終了
                {
                    break;
                }
                else if (up_count > 0)
                {
                    if (blackAgent.board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                    {
                        for (int i = j_count; i > count_tate; i--)
                        {
                            reverse_white_count++;
                            temp--;
                            blackAgent.board[temp + 1, i] = -1;                                                          //全てを反転
                            if (delete_count > 0)
                            {
                                if (blackAgent.piece_temp[temp + 1, i] != null)
                                {
                                    blackAgent.piece_temp[temp + 1, i].transform.rotation = Quaternion.Euler(-90.0f, 0.0f, 0.0f);
                                }
                            }
                            delete_count++;
                        }
                        reverse_white_count--;
                        break;
                    }
                    if (blackAgent.board[count_yoko, count_tate] == 0)
                    {
                        break;
                    }
                }
                else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                {
                    up_count++;
                }
            }
            up_count = 0;
            delete_count = 0;
            count_tate = temp_count_tate;
            count_yoko = temp_count_yoko;
            temp = i_count;
            //------------------------------------------------------------------------------------------------------------------------------------------3
            while (blackAgent.board[count_yoko, count_tate] != 9)
            {
                count_yoko--;
                if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == -1 || blackAgent.board[count_yoko, count_tate] == 0))   //１つ上のコマが黒or無なら終了
                {
                    break;
                }
                else if (up_count > 0)
                {
                    if (blackAgent.board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                    {
                        for (int i = i_count; i > count_yoko; i--)
                        {
                            reverse_white_count++;
                            blackAgent.board[i, count_tate] = -1;                                                          //全てを反転
                            if (delete_count > 0)
                            {
                                if (blackAgent.piece_temp[i, count_tate] != null)
                                {
                                    blackAgent.piece_temp[i, count_tate].transform.rotation = Quaternion.Euler(-90.0f, 0.0f, 0.0f);
                                }
                            }
                            delete_count++;
                        }
                        reverse_white_count--;
                        break;
                    }
                    if (blackAgent.board[count_yoko, count_tate] == 0)
                    {
                        break;
                    }
                }
                else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                {
                    up_count++;
                }
            }
            up_count = 0;
            delete_count = 0;
            count_tate = temp_count_tate;
            count_yoko = temp_count_yoko;
            //------------------------------------------------------------------------------------------------------------------------------------------4
            while (blackAgent.board[count_yoko, count_tate] != 9)
            {
                count_tate++;
                count_yoko--;
                if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == -1 || blackAgent.board[count_yoko, count_tate] == 0))   //１つ上のコマが黒or無なら終了
                {
                    break;
                }
                else if (up_count > 0)
                {
                    if (blackAgent.board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                    {
                        for (int i = j_count; i < count_tate; i++)
                        {
                            reverse_white_count++;
                            temp--;
                            blackAgent.board[temp + 1, i] = -1;                                                          //全てを反転
                            if (delete_count > 0)
                            {
                                if (blackAgent.piece_temp[temp + 1, i] != null)
                                {
                                    blackAgent.piece_temp[temp + 1, i].transform.rotation = Quaternion.Euler(-90.0f, 0.0f, 0.0f);
                                }

                            }
                            delete_count++;
                        }
                        reverse_white_count--;
                        break;
                    }
                    if (blackAgent.board[count_yoko, count_tate] == 0)
                    {
                        break;
                    }
                }
                else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                {
                    up_count++;
                }
            }
            up_count = 0;
            delete_count = 0;
            count_tate = temp_count_tate;
            count_yoko = temp_count_yoko;
            temp = i_count;
            //------------------------------------------------------------------------------------------------------------------------------------------5
            while (blackAgent.board[count_yoko, count_tate] != 9)
            {
                count_tate++;
                if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == -1 || blackAgent.board[count_yoko, count_tate] == 0))   //１つ上のコマが黒or無なら終了
                {
                    break;
                }
                else if (up_count > 0)
                {
                    if (blackAgent.board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                    {
                        for (int i = j_count; i < count_tate; i++)
                        {
                            reverse_white_count++;
                            blackAgent.board[count_yoko, i] = -1;                                                          //全てを反転
                            if (delete_count > 0)
                            {
                                if (blackAgent.piece_temp[count_yoko, i] != null)
                                {
                                    blackAgent.piece_temp[count_yoko, i].transform.rotation = Quaternion.Euler(-90.0f, 0.0f, 0.0f);
                                }

                            }
                            delete_count++;
                        }
                        reverse_white_count--;
                        break;
                    }
                    if (blackAgent.board[count_yoko, count_tate] == 0)
                    {
                        break;
                    }
                }
                else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                {
                    up_count++;
                }
            }
            up_count = 0;
            delete_count = 0;
            count_tate = temp_count_tate;
            count_yoko = temp_count_yoko;
            //----------------------------------------------------------------------------------------------------------------------------------------------6
            while (blackAgent.board[count_yoko, count_tate] != 9)
            {
                count_yoko++;
                count_tate++;
                if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == -1 || blackAgent.board[count_yoko, count_tate] == 0))   //１つ上のコマが黒or無なら終了
                {
                    break;
                }
                else if (up_count > 0)
                {
                    if (blackAgent.board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                    {
                        for (int i = j_count; i < count_tate; i++)
                        {
                            reverse_white_count++;
                            temp++;
                            blackAgent.board[temp - 1, i] = -1;                                                          //全てを反転
                            if (delete_count > 0)
                            {
                                if(blackAgent.piece_temp[temp - 1, i] != null)
                                blackAgent.piece_temp[temp - 1, i].transform.rotation = Quaternion.Euler(-90.0f, 0.0f, 0.0f);

                            }
                            delete_count++;
                        }
                        reverse_white_count--;
                        break;
                    }
                    if (blackAgent.board[count_yoko, count_tate] == 0)
                    {
                        break;
                    }
                }
                else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                {
                    up_count++;
                }
            }
            up_count = 0;
            delete_count = 0;
            count_tate = temp_count_tate;
            count_yoko = temp_count_yoko;
            temp = i_count;
            //------------------------------------------------------------------------------------------------------------------------------------------------7
            while (blackAgent.board[count_yoko, count_tate] != 9)
            {
                count_yoko++;
                if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == -1 || blackAgent.board[count_yoko, count_tate] == 0))   //１つ上のコマが黒or無なら終了
                {
                    break;
                }
                else if (up_count > 0)
                {
                    if (blackAgent.board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                    {
                        for (int i = i_count; i < count_yoko; i++)
                        {
                            reverse_white_count++;
                            blackAgent.board[i, count_tate] = -1;                                                          //全てを反転
                            if (delete_count > 0)
                            {
                                if (blackAgent.piece_temp[i, count_tate] != null)
                                {
                                    blackAgent.piece_temp[i, count_tate].transform.rotation = Quaternion.Euler(-90.0f, 0.0f, 0.0f);
                                }

                            }
                            delete_count++;
                        }
                        reverse_white_count--;
                        break;
                    }
                    if (blackAgent.board[count_yoko, count_tate] == 0)
                    {
                        break;
                    }
                }
                else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                {
                    up_count++;
                }
            }
            up_count = 0;
            delete_count = 0;
            count_tate = temp_count_tate;
            count_yoko = temp_count_yoko;
            //--------------------------------------------------------------------------------------------------------------------------------------------------8
            while (blackAgent.board[count_yoko, count_tate] != 9)
            {
                count_tate--;
                count_yoko++;
                if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == -1 || blackAgent.board[count_yoko, count_tate] == 0))   //１つ上のコマが黒or無なら終了
                {
                    break;
                }
                else if (up_count > 0)
                {
                    if (blackAgent.board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                    {
                        for (int i = j_count; i > count_tate; i--)
                        {
                            reverse_white_count++;
                            temp++;
                            blackAgent.board[temp - 1, i] = -1;                                                          //全てを反転
                            if (delete_count > 0)
                            {
                                if (blackAgent.piece_temp[temp - 1, i] != null)
                                {
                                    blackAgent.piece_temp[temp - 1, i].transform.rotation = Quaternion.Euler(-90.0f, 0.0f, 0.0f);
                                }

                            }
                            delete_count++;
                        }
                        reverse_white_count--;
                        break;
                    }
                    if (blackAgent.board[count_yoko, count_tate] == 0)
                    {
                        break;
                    }
                }
                else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                {
                    up_count++;
                }
            }
            up_count = 0;
            //Debug.Log("reverse_white_count : " + reverse_white_count);
            delete_count = 0;
            temp_count_yoko = count_yoko;
            temp_count_tate = count_tate;
        }
    }

    public void Find_White_OK()
    {
        for (int count_yoko = 1; count_yoko < 9; count_yoko++)
        {
            for (int count_tate = 1; count_tate < 9; count_tate++)
            {
                if (blackAgent.board[count_yoko, count_tate] == 0)
                {
                    temp_count_yoko = count_yoko;
                    temp_count_tate = count_tate;

                    while (blackAgent.board[count_yoko, count_tate] != 9)//----------------------------------------------------------------------------------------------1
                    {
                        count_tate--;
                        if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == -1 || blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 4))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (blackAgent.board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 4)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;

                    //------------------------------------------------------------------------------------------------------------------------------------------2
                    while (blackAgent.board[count_yoko, count_tate] != 9)
                    {
                        count_tate--;
                        count_yoko--;
                        if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == -1 || blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 4))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (blackAgent.board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 4)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //------------------------------------------------------------------------------------------------------------------------------------------3
                    while (blackAgent.board[count_yoko, count_tate] != 9)
                    {
                        count_yoko--;
                        if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == -1 || blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 4))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (blackAgent.board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 4)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //------------------------------------------------------------------------------------------------------------------------------------------4
                    while (blackAgent.board[count_yoko, count_tate] != 9)
                    {
                        count_tate++;
                        count_yoko--;
                        if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == -1 || blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 4))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (blackAgent.board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 4)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //------------------------------------------------------------------------------------------------------------------------------------------5
                    while (blackAgent.board[count_yoko, count_tate] != 9)
                    {
                        count_tate++;
                        if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == -1 || blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 4))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (blackAgent.board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 4)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //----------------------------------------------------------------------------------------------------------------------------------------------6
                    while (blackAgent.board[count_yoko, count_tate] != 9)
                    {
                        count_yoko++;
                        count_tate++;
                        if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == -1 || blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 4))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (blackAgent.board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 4)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //------------------------------------------------------------------------------------------------------------------------------------------------7
                    while (blackAgent.board[count_yoko, count_tate] != 9)
                    {
                        count_yoko++;
                        if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == -1 || blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 4))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (blackAgent.board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 4)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //--------------------------------------------------------------------------------------------------------------------------------------------------8
                    while (blackAgent.board[count_yoko, count_tate] != 9)
                    {
                        count_tate--;
                        count_yoko++;
                        if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == -1 || blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 4))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (blackAgent.board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 4)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                }
                if (white_OK_sign)
                {
                    blackAgent.board[count_yoko, count_tate] = 4;
                    white_OK_sign = false;
                }
            }
        }
    }

    public void Find_Black_OK()
    {
        for (int count_yoko = 1; count_yoko < 9; count_yoko++)
        {
            for (int count_tate = 1; count_tate < 9; count_tate++)
            {
                if (blackAgent.board[count_yoko, count_tate] == 0)
                {
                    temp_count_yoko = count_yoko;
                    temp_count_tate = count_tate;

                    while (blackAgent.board[count_yoko, count_tate] != 9)//----------------------------------------------------------------------------------------------1
                    {
                        count_tate--;
                        if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == 1 || blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 6))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (blackAgent.board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 6)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;

                    //------------------------------------------------------------------------------------------------------------------------------------------2
                    while (blackAgent.board[count_yoko, count_tate] != 9)
                    {
                        count_tate--;
                        count_yoko--;
                        if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == 1 || blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 6))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (blackAgent.board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 6)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //------------------------------------------------------------------------------------------------------------------------------------------3
                    while (blackAgent.board[count_yoko, count_tate] != 9)
                    {
                        count_yoko--;
                        if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == 1 || blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 6))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (blackAgent.board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 6)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //------------------------------------------------------------------------------------------------------------------------------------------4
                    while (blackAgent.board[count_yoko, count_tate] != 9)
                    {
                        count_tate++;
                        count_yoko--;
                        if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == 1 || blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 6))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (blackAgent.board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 6)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //------------------------------------------------------------------------------------------------------------------------------------------5
                    while (blackAgent.board[count_yoko, count_tate] != 9)
                    {
                        count_tate++;
                        if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == 1 || blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 6))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (blackAgent.board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 6)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //----------------------------------------------------------------------------------------------------------------------------------------------6
                    while (blackAgent.board[count_yoko, count_tate] != 9)
                    {
                        count_yoko++;
                        count_tate++;
                        if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == 1 || blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 6))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (blackAgent.board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 6)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //------------------------------------------------------------------------------------------------------------------------------------------------7
                    while (blackAgent.board[count_yoko, count_tate] != 9)
                    {
                        count_yoko++;
                        if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == 1 || blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 6))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (blackAgent.board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 6)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //--------------------------------------------------------------------------------------------------------------------------------------------------8
                    while (blackAgent.board[count_yoko, count_tate] != 9)
                    {
                        count_tate--;
                        count_yoko++;
                        if (up_count == 0 && (blackAgent.board[count_yoko, count_tate] == 1 || blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 6))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (blackAgent.board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (blackAgent.board[count_yoko, count_tate] == 0 || blackAgent.board[count_yoko, count_tate] == 6)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && blackAgent.board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                }
                if (white_OK_sign)
                {
                    blackAgent.board[count_yoko, count_tate] = 6;
                    white_OK_sign = false;
                }
            }
        }
    }

    public void Search_White_pass()
    {
        for (int i = 1; i < 9; i++)
        {
            for (int j = 1; j < 9; j++)
            {
                if (blackAgent.board[i, j] == 4)
                {
                    blackAgent.pass_white_check = false;
                }
            }
        }
    }

    public void Search_Black_pass()
    {
        for (int i = 1; i < 9; i++)
        {
            for (int j = 1; j < 9; j++)
            {
                if (blackAgent.board[i, j] == 6)
                {
                    blackAgent.pass_black_check = false;
                }
            }
        }
    }

    public void White_Destroy(int i, int j)
    {
        Destroy(blackAgent.piece_temp[i, j]);
    }

    public void Show_result()
    {
        for (int i = 1; i < 9; i++)
        {
            for (int j = 1; j < 9; j++)
            {
                ////Debug.Log("i : " + i + "j : " + j + "  " + blackAgent.board[i, j] + "i_count : " + i_count + "j_count : " + j_count);

            }
        }
    }

    public void White_Initialize()
    {
        for (int i = 1; i < 9; i++)
        {
            for (int j = 1; j < 9; j++)
            {
                if (blackAgent.board[i, j] == -1)
                {
                    blackAgent.piece_temp[i, j] = Instantiate(piece_white, new Vector3(i - 4 - 0.5f, 4 - j - 4.5f, 4.9f), Quaternion.Euler(-90.0f, 0f, 0f));
                }
            }
        }
    }

    public void Square_Position_Initialize()
    {
        //if (now_temp == null)
        //{
        //    //Debug.Log("12345");
        //    now_temp = Instantiate(now, new Vector3(-0.5f, -4.55f, 4.0f), Quaternion.Euler(0.0f, 0f, 0f));
        //}

        i_count = 4;
        j_count = 4;
        reverse_ok_i = 4;
        reverse_ok_j = 4;

        for (int i = 1; i < 9; i++)
        {
            for (int j = 1; j < 9; j++)
            {
                reverse_OK[i, j] = false;
            }
        }
    }

    public void Reset_White_OK()
    {
        for (int i = 1; i < 9; i++)
        {
            for (int j = 1; j < 9; j++)
            {
                if (blackAgent.board[i, j] == 4)
                {
                    blackAgent.board[i, j] = 0;
                }
            }
        }
        blackAgent.pass_white_check = true;
    }

    public void now_delete()
    {
        //Destroy(now_temp);
    }

    public override void AgentReset()
    {
        reverse_ok_i = 4;
        reverse_ok_j = 4;

        if (reset_count > 0)
        {
            //Debug.Log("AgentReset");
            i_count = 4;
            j_count = 4;
            up_count = 0;
            temp_count_tate = 0;
            temp_count_yoko = 0;

            judge_black = 0;
            judge_white = 0;

            for (int i = 1; i < 9; i++)
            {
                for (int j = 1; j < 9; j++)
                {
                    if (blackAgent.board[i, j] == -1)
                    {
                        White_Destroy(i, j);
                    }

                    if (blackAgent.board[i, j] == 1)
                    {
                        black.Black_Destroy(i, j);
                    }

                    if ((i == 4 && j == 4) || (i == 5 && j == 5))
                    {
                        blackAgent.board[i, j] = 1;
                    }
                    else if ((i == 5 && j == 4) || (i == 4 && j == 5))
                    {
                        blackAgent.board[i, j] = -1;
                    }
                    else
                    {
                        blackAgent.board[i, j] = 0;
                    }
                }
            }
        }

        white_initialize = true;

        Square_Position_Initialize();

        blackAgent.turn_change = false;
        reset_count++;
        blackAgent.pass_black_check = true;


        black.black_initialize = true;

        black.Square_Position_Initialize();

        blackAgent.turn_change = false;
        blackAgent.pass_white_check = true;

        judge_black = 0;
        judge_white = 0;

        Find_Black_OK();

        turn_time = true;

        win.SetActive(false);
        lose.SetActive(false);
        draw.SetActive(false);

        StartCoroutine("ResetTime");

        if (reset_count > 0)
        {
            //SceneManager.LoadScene("Title");
        }
    }

    IEnumerator ResetTime()
    {
        yield return new WaitForSeconds(1.0f);
        reset_now = true;
    }

    public override void CollectObservations()//渡したい値
    {
        for (int i = 1; i < 9; i++)
        {
            for (int j = 1; j < 9; j++)
            {
                AddVectorObs(i);
                AddVectorObs(j);
                AddVectorObs(blackAgent.board[i, j]);
            }
        }
    }

    public override void AgentAction(float[] vectorAction, string textAction)//全処理
    {
        if (white_initialize)
        {
            White_Initialize();
            white_initialize = false;
        }

        Othello_Count();

        if (blackAgent.turn_change && turn_time)
        {
            //Show_result();
            if (white_position_initialize)
            {
                Square_Position_Initialize();
                white_position_initialize = false;
            }
            /*
            if (vectorAction[1] < 1 && vectorAction[1] > 0 && j_count > 1)
            {
                //AddReward(10.0f);
                ////Debug.Log("押したよ");
                now_temp.transform.position += new Vector3(0.0f, 1.0f, 0.0f);
                j_count--;
                vectorAction[1] = 0;
                AddReward(-0.01f);
            }
            if (vectorAction[1] > -1 && vectorAction[1] < 0 && j_count < 8)
            {
                //AddReward(10.0f);
                ////Debug.Log("押したよ");
                now_temp.transform.position += new Vector3(0.0f, -1.0f, 0.0f);
                j_count++;
                vectorAction[1] = 0;
                AddReward(-0.01f);
            }
            */
            Reverse_OK_find();
            if (vectorAction[0] > -1 && vectorAction[0] < 0 && i_count > 0 && reset_now)
            {
                i_count = reverse_ok_i;
                j_count = reverse_ok_j;
                //Debug.Log("押したよ");
                while (!(i_count == 1 && j_count == 8))
                {
                    //Debug.Log("通過地点2 : i : " + i_count + " j " + j_count);
                    if (i_count == 1 && j_count != 8)
                    {
                        i_count = 9;
                        j_count++;
                    }
                    if (i_count != 1)
                    {
                        i_count--;
                    }
                    Show_result();
                    if (reverse_OK[i_count, j_count])
                    {
                        //now_temp.transform.position = new Vector3(i_count - 4 - 0.5f, 4 - j_count - 4.55f, 4.0f);
                        reverse_ok_i = i_count;
                        reverse_ok_j = j_count;
                        break;
                    }
                    ////Debug.Log(i_count + " : " + j_count + " reverse_ok_i : " + reverse_ok_i + " j : " + reverse_ok_j);
                }
                vectorAction[0] = 0;
            }

            if (vectorAction[0] < 1 && vectorAction[0] > 0 && i_count < 9 && reset_now)
            //if (Input.GetKeyUp(KeyCode.D) && i_count < 8)
            {
                i_count = reverse_ok_i;
                j_count = reverse_ok_j;
                //AddReward(10.0f);
                //Debug.Log("押したよ");
                while (!(i_count == 8 && j_count == 1))
                {
                    //Debug.Log("通過地点2 : i : " + i_count + " j " + j_count);
                    //Debug.Log(i_count + " : " + j_count);

                    if (i_count == 8 && j_count != 1)
                    {
                        i_count = 0;
                        j_count--;
                    }

                    if (i_count != 8)
                    {
                        i_count++;
                    }
                    Show_result();
                    if (reverse_OK[i_count, j_count])
                    {
                        //Debug.Log("通過地点3");
                        //now_temp.transform.position = new Vector3(i_count - 4 - 0.5f, 4 - j_count - 4.55f, 4.0f);
                        reverse_ok_i = i_count;
                        reverse_ok_j = j_count;
                        break;
                    }
                    ////Debug.Log(i_count + " : " + j_count + "main" + blackAgent.board[i_count,j_count] +  " reverse_ok_i : " + reverse_ok_i + " j : " + reverse_ok_j);
                    Show_result();
                }
                vectorAction[0] = 0;
            }

            //if (vectorAction[1] < 1 && vectorAction[1] > 0 && reset_now)
            //{
                //i_count = reverse_ok_i;
                //j_count = reverse_ok_j;
                //Debug.Log("押したよ");
                //if (blackAgent.board[i_count, j_count] == 4)
            if(Raytest.changeOK)
            {
                AddReward(1.0f);
                Reset_White_OK();
                //blackAgent.board[i_count, j_count] = -1;
                change(i_count, j_count);
                Change_After_White(i_count, j_count);
                //Debug.Log("オセロのいち" + blackAgent.piece_temp[i_count, j_count].transform.position);
                corner_reward();
                //blackAgent.turn_change = false;
                StartCoroutine("Turn");
                Find_Black_OK();
                Search_Black_pass();
                if (blackAgent.pass_black_check)
                {
                    Debug.Log("pass");
                    blackAgent.turn_change = true;
                    Find_White_OK();
                    Search_White_pass();
                    if (blackAgent.pass_white_check)
                    {
                        reset_now = false;
                        turn_time = false;
                        for (int i = 1; i < 9; i++)
                        {
                            for (int j = 1; j < 9; j++)
                            {
                                if (blackAgent.board[i, j] == -1)
                                {
                                    judge_white++;
                                }
                                if (blackAgent.board[i, j] == 1)
                                {
                                    judge_black++;
                                }
                            }
                        }
                        if (judge_white > judge_black)           //白の勝利
                        {
                            win.SetActive(true);
                            //Debug.Log("Winner");
                            AddReward(10.0f);
                            //Done();
                        }
                        else if(judge_white == judge_black)
                        {
                            draw.SetActive(true);
                            //Debug.Log("Draw");
                            //Done();
                        }
                        else
                        {
                            lose.SetActive(true);
                            //Debug.Log("Loser");
                            //Done();
                        }

                        blackAgent.pass_white_check = false;
                        Debug.Log("111");
                        //StartCoroutine("Do");
                        StartCoroutine("transScene");
                    }
                }
                white_position_initialize = true;
                now_delete();
                Raytest.changeOK = false;
            }
            // vectorAction[1] = 0;
        //}
        }
    }

    IEnumerator transScene()
    {
        yield return new WaitForSeconds(3.0f);
        SceneManager.LoadScene("Title");
    }

    IEnumerator Do()
    {
        yield return new WaitForSeconds(3.0f);
        Done();
    }

    public void corner_reward()
    {
    }

    public void WhiteReward(float temp)
    {
        AddReward(temp);
    }

    public void Reverse_OK_find()
    {
        for (int i = 1; i < 9; i++)
        {
            for (int j = 1; j < 9; j++)
            {
                if (blackAgent.board[i, j] == 4)
                {
                    reverse_OK[i, j] = true;
                }
                else
                {
                    reverse_OK[i, j] = false;
                }
            }
        }
    }

    public void OnDestroy()
    {
        Destroy(GameObject.Find("Music"));
    }

    IEnumerator Turn()
    {
        yield return new WaitForSeconds(1.0f);
        blackAgent.turn_change = false;
    }

    public void Othello_Count()
    {
        int a = 0;
        int b = 0;
        for (int i = 1; i < 9; i++)
        {
            for (int j = 1; j < 9; j++)
            {
                if(blackAgent.board[i, j] == -1)
                {
                    a++;
                }
                if (blackAgent.board[i, j] == 1)
                {
                    b++;
                }
            }
        }
        white_count.text = a.ToString();
        black_count.text = b.ToString();
    }
}
