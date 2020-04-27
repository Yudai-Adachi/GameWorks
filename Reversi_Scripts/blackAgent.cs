using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using MLAgents;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class blackAgent : Agent
{
    whiteAgent white;
    AudioSource audio;
    //White_Piece white;

    public GameObject piece_black;
    public GameObject panel;
    public GameObject OK_image_effect;
    public GameObject now;

    public GameObject win;
    public GameObject lose;
    public GameObject draw;

    public GameObject black_now_effect;

    public static GameObject[,] piece_temp;
    GameObject[,] effect;
    GameObject now_temp;
    GameObject black_now;
    bool[,] reverse_OK;
    int[,] repair;
    int reverse_ok_i;
    int reverse_ok_j;

    int i_count;
    int j_count;
    int up_count;
    int temp_count_tate;
    int temp_count_yoko;
    int reverse_black_count;
    int delete_count;
    int judge_white;
    int judge_black;

    bool reset_now;
    bool stop;

    public int reset_count;

    public bool black_initialize;
    bool black_position_initialize;
    bool white_OK_sign;
    bool turn_time;
    public static bool black_find_flag;
    public static int[,] board;
    public static bool pass_white_check;
    public static bool pass_black_check;
    public static bool turn_change;

    Vector3 temp_repair;

    // Start is called before the first frame update
    void Start()
    {
        //now_temp = Instantiate(now, new Vector3(-0.5f, -4.55f, 4.0f), Quaternion.Euler(0.0f, 0f, 0f));

        i_count = 4;
        j_count = 4;
        up_count = 0;
        temp_count_tate = 0;
        temp_count_yoko = 0;
        delete_count = 0;
        black_initialize = true;
        black_position_initialize = true;
        black_find_flag = true;

        piece_temp = new GameObject[10, 10];
        effect = new GameObject[10, 10];
        repair = new int[10, 10];
        reverse_OK = new bool[10, 10];
        white = GameObject.Find("white_Agent").GetComponent<whiteAgent>();
        //white = GameObject.Find("white_presenter").GetComponent<White_Piece>();
        audio = GetComponent<AudioSource>();
    }

    public void change(int i_count, int j_count)
    {
        if (board[i_count, j_count] == 1)
        {
            piece_temp[i_count, j_count] = Instantiate(piece_black, new Vector3(i_count - 4 - 0.5f, 4 - j_count - 4.5f, 4.9f), Quaternion.Euler(90.0f, 0f, 0f));
        }
    }

    public void Change_After_Black(int count_yoko, int count_tate)                                                    //下に置いた時
    {
        int temp = i_count;
        temp_count_yoko = count_yoko;
        temp_count_tate = count_tate;

        if (board[i_count, j_count] == 1)//今いるマスが黒なら
        {
            while (board[count_yoko, count_tate] != 9)//----------------------------------------------------------------------------------------------1
            {
                count_tate--;
                if (up_count == 0 && (board[count_yoko, count_tate] == 1 || board[count_yoko, count_tate] == 0))   //１つ上のコマが黒or無なら終了
                {
                    break;
                }
                else if (up_count > 0)
                {
                    if (board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                    {
                        for (int i = j_count; i > count_tate; i--)
                        {
                            reverse_black_count++;
                            board[count_yoko, i] = 1;                                                          //全てを反転
                            if (delete_count > 0)
                            {
                                if (piece_temp[count_yoko, i] != null)
                                {
                                    piece_temp[count_yoko, i].transform.rotation = Quaternion.Euler(90.0f, 0.0f, 0.0f);
                                }
                                else
                                {
                                    //Debug.Log.Log("board : " + board[count_yoko, i]);
                                }
                            }
                            delete_count++;
                        }
                        reverse_black_count--;
                        break;
                    }
                    if (board[count_yoko, count_tate] == 0)
                    {
                        break;
                    }
                }
                else if (up_count == 0 && board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                {
                    up_count++;
                }
            }
            up_count = 0;
            count_tate = temp_count_tate;
            count_yoko = temp_count_yoko;
            delete_count = 0;
            //------------------------------------------------------------------------------------------------------------------------------------------2
            while (board[count_yoko, count_tate] != 9)
            {
                count_tate--;
                count_yoko--;
                if (up_count == 0 && (board[count_yoko, count_tate] == 1 || board[count_yoko, count_tate] == 0))   //１つ上のコマが黒or無なら終了
                {
                    break;
                }
                else if (up_count > 0)
                {
                    if (board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                    {
                        for (int i = j_count; i > count_tate; i--)
                        {
                            reverse_black_count++;
                            temp--;
                            board[temp + 1, i] = 1;
                            if (delete_count > 0)
                            {
                                if (piece_temp[temp + 1, i] != null)
                                {
                                    piece_temp[temp + 1, i].transform.rotation = Quaternion.Euler(90.0f, 0.0f, 0.0f);
                                }
                                else
                                {
                                    //Debug.Log.Log("board : " + board[temp + 1, i]);
                                }
                            }
                            delete_count++;
                        }
                        reverse_black_count--;
                        break;
                    }
                    if (board[count_yoko, count_tate] == 0)
                    {
                        break;
                    }
                }
                else if (up_count == 0 && board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
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
            while (board[count_yoko, count_tate] != 9)
            {
                count_yoko--;
                if (up_count == 0 && (board[count_yoko, count_tate] == 1 || board[count_yoko, count_tate] == 0))   //１つ上のコマが黒or無なら終了
                {
                    break;
                }
                else if (up_count > 0)
                {
                    if (board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                    {
                        for (int i = i_count; i > count_yoko; i--)
                        {
                            reverse_black_count++;
                            board[i, count_tate] = 1;                                                          //全てを反転
                            if (delete_count > 0)
                            {
                                if (piece_temp[i, count_tate] != null)
                                {
                                    piece_temp[i, count_tate].transform.rotation = Quaternion.Euler(90.0f, 0.0f, 0.0f);
                                }
                            }
                            delete_count++;
                        }
                        reverse_black_count--;
                        break;
                    }
                    if (board[count_yoko, count_tate] == 0)
                    {
                        break;
                    }
                }
                else if (up_count == 0 && board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                {
                    up_count++;
                }
            }
            up_count = 0;
            delete_count = 0;
            count_tate = temp_count_tate;
            count_yoko = temp_count_yoko;
            //------------------------------------------------------------------------------------------------------------------------------------------4
            while (board[count_yoko, count_tate] != 9)
            {
                count_tate++;
                count_yoko--;
                if (up_count == 0 && (board[count_yoko, count_tate] == 1 || board[count_yoko, count_tate] == 0))   //１つ上のコマが黒or無なら終了
                {
                    break;
                }
                else if (up_count > 0)
                {
                    if (board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                    {
                        for (int i = j_count; i < count_tate; i++)
                        {
                            reverse_black_count++;
                            temp--;
                            board[temp + 1, i] = 1;                                                          //全てを反転
                            if (delete_count > 0)
                            {
                                if (piece_temp[temp + 1, i] != null)
                                {
                                    piece_temp[temp + 1, i].transform.rotation = Quaternion.Euler(90.0f, 0.0f, 0.0f);
                                }
                            }
                            delete_count++;
                        }
                        reverse_black_count--;
                        break;
                    }
                    if (board[count_yoko, count_tate] == 0)
                    {
                        break;
                    }
                }
                else if (up_count == 0 && board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
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
            while (board[count_yoko, count_tate] != 9)
            {
                count_tate++;
                if (up_count == 0 && (board[count_yoko, count_tate] == 1 || board[count_yoko, count_tate] == 0))   //１つ上のコマが黒or無なら終了
                {
                    break;
                }
                else if (up_count > 0)
                {
                    if (board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                    {
                        for (int i = j_count; i < count_tate; i++)
                        {
                            reverse_black_count++;
                            board[count_yoko, i] = 1;                                                          //全てを反転
                            if (delete_count > 0)
                            {
                                if (piece_temp[count_yoko, i] != null)
                                    piece_temp[count_yoko, i].transform.rotation = Quaternion.Euler(90.0f, 0.0f, 0.0f);
                            }
                            delete_count++;
                        }
                        reverse_black_count--;
                        break;
                    }
                    if (board[count_yoko, count_tate] == 0)
                    {
                        break;
                    }
                }
                else if (up_count == 0 && board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                {
                    up_count++;
                }
            }
            up_count = 0;
            delete_count = 0;
            count_tate = temp_count_tate;
            count_yoko = temp_count_yoko;
            //----------------------------------------------------------------------------------------------------------------------------------------------6
            while (board[count_yoko, count_tate] != 9)
            {
                count_yoko++;
                count_tate++;
                if (up_count == 0 && (board[count_yoko, count_tate] == 1 || board[count_yoko, count_tate] == 0))   //１つ上のコマが黒or無なら終了
                {
                    break;
                }
                else if (up_count > 0)
                {
                    if (board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                    {
                        for (int i = j_count; i < count_tate; i++)
                        {
                            reverse_black_count++;
                            temp++;
                            board[temp - 1, i] = 1;                                                          //全てを反転
                            if (delete_count > 0)
                            {
                                if (piece_temp[temp - 1, i] != null)
                                {
                                    piece_temp[temp - 1, i].transform.rotation = Quaternion.Euler(90.0f, 0.0f, 0.0f);
                                }
                            }
                            delete_count++;
                        }
                        reverse_black_count--;
                        break;
                    }
                    if (board[count_yoko, count_tate] == 0)
                    {
                        break;
                    }
                }
                else if (up_count == 0 && board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
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
            while (board[count_yoko, count_tate] != 9)
            {
                count_yoko++;
                if (up_count == 0 && (board[count_yoko, count_tate] == 1 || board[count_yoko, count_tate] == 0))   //１つ上のコマが黒or無なら終了
                {
                    break;
                }
                else if (up_count > 0)
                {
                    if (board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                    {
                        for (int i = i_count; i < count_yoko; i++)
                        {
                            reverse_black_count++;
                            board[i, count_tate] = 1;                                                          //全てを反転
                            if (delete_count > 0)
                            {
                                if (piece_temp[i, count_tate] != null)
                                {
                                    piece_temp[i, count_tate].transform.rotation = Quaternion.Euler(90.0f, 0.0f, 0.0f);
                                }
                            }
                            delete_count++;
                        }
                        reverse_black_count--;
                        break;
                    }
                    if (board[count_yoko, count_tate] == 0)
                    {
                        break;
                    }
                }
                else if (up_count == 0 && board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                {
                    up_count++;
                }
            }
            up_count = 0;
            delete_count = 0;
            count_tate = temp_count_tate;
            count_yoko = temp_count_yoko;
            //--------------------------------------------------------------------------------------------------------------------------------------------------8
            while (board[count_yoko, count_tate] != 9)
            {
                count_tate--;
                count_yoko++;
                if (up_count == 0 && (board[count_yoko, count_tate] == 1 || board[count_yoko, count_tate] == 0))   //１つ上のコマが黒or無なら終了
                {
                    break;
                }
                else if (up_count > 0)
                {
                    if (board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                    {
                        for (int i = j_count; i > count_tate; i--)
                        {
                            reverse_black_count++;
                            temp++;
                            board[temp - 1, i] = 1;                                                          //全てを反転
                            if (delete_count > 0)
                            {
                                if (piece_temp[temp - 1, i] != null)
                                {
                                    piece_temp[temp - 1, i].transform.rotation = Quaternion.Euler(90.0f, 0.0f, 0.0f);
                                }
                            }
                            delete_count++;
                        }
                        reverse_black_count--;
                        break;
                    }
                    if (board[count_yoko, count_tate] == 0)
                    {
                        break;
                    }
                }
                else if (up_count == 0 && board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                {
                    up_count++;
                }
            }
            up_count = 0;
            //Debug.Log.Log("reverse_black_count : " + reverse_black_count);
            delete_count = 0;
            temp_count_yoko = count_yoko;
            temp_count_tate = count_tate;
        }
    }

    public void Find_Black_OK()
    {
        for (int count_yoko = 1; count_yoko < 9; count_yoko++)
        {
            for (int count_tate = 1; count_tate < 9; count_tate++)
            {
                if (board[count_yoko, count_tate] == 0)
                {
                    temp_count_yoko = count_yoko;
                    temp_count_tate = count_tate;

                    while (board[count_yoko, count_tate] != 9)//----------------------------------------------------------------------------------------------1
                    {
                        count_tate--;
                        if (up_count == 0 && (board[count_yoko, count_tate] == 1 || board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 6))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 6)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;

                    //------------------------------------------------------------------------------------------------------------------------------------------2
                    while (board[count_yoko, count_tate] != 9)
                    {
                        count_tate--;
                        count_yoko--;
                        if (up_count == 0 && (board[count_yoko, count_tate] == 1 || board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 6))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 6)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //------------------------------------------------------------------------------------------------------------------------------------------3
                    while (board[count_yoko, count_tate] != 9)
                    {
                        count_yoko--;
                        if (up_count == 0 && (board[count_yoko, count_tate] == 1 || board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 6))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 6)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //------------------------------------------------------------------------------------------------------------------------------------------4
                    while (board[count_yoko, count_tate] != 9)
                    {
                        count_tate++;
                        count_yoko--;
                        if (up_count == 0 && (board[count_yoko, count_tate] == 1 || board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 6))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 6)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //------------------------------------------------------------------------------------------------------------------------------------------5
                    while (board[count_yoko, count_tate] != 9)
                    {
                        count_tate++;
                        if (up_count == 0 && (board[count_yoko, count_tate] == 1 || board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 6))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 6)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //----------------------------------------------------------------------------------------------------------------------------------------------6
                    while (board[count_yoko, count_tate] != 9)
                    {
                        count_yoko++;
                        count_tate++;
                        if (up_count == 0 && (board[count_yoko, count_tate] == 1 || board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 6))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 6)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //------------------------------------------------------------------------------------------------------------------------------------------------7
                    while (board[count_yoko, count_tate] != 9)
                    {
                        count_yoko++;
                        if (up_count == 0 && (board[count_yoko, count_tate] == 1 || board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 6))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 6)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //--------------------------------------------------------------------------------------------------------------------------------------------------8
                    while (board[count_yoko, count_tate] != 9)
                    {
                        count_tate--;
                        count_yoko++;
                        if (up_count == 0 && (board[count_yoko, count_tate] == 1 || board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 6))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (board[count_yoko, count_tate] == 1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 6)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && board[count_yoko, count_tate] == -1)                                  //１つ上のコマが白なら＋１する
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
                    board[count_yoko, count_tate] = 6;
                    white_OK_sign = false;
                }
            }
        }
    }

    public void Find_White_OK()
    {
        for (int count_yoko = 1; count_yoko < 9; count_yoko++)
        {
            for (int count_tate = 1; count_tate < 9; count_tate++)
            {
                if (board[count_yoko, count_tate] == 0)
                {
                    temp_count_yoko = count_yoko;
                    temp_count_tate = count_tate;

                    while (board[count_yoko, count_tate] != 9)//----------------------------------------------------------------------------------------------1
                    {
                        count_tate--;
                        if (up_count == 0 && (board[count_yoko, count_tate] == -1 || board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 4))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 4)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;

                    //------------------------------------------------------------------------------------------------------------------------------------------2
                    while (board[count_yoko, count_tate] != 9)
                    {
                        count_tate--;
                        count_yoko--;
                        if (up_count == 0 && (board[count_yoko, count_tate] == -1 || board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 4))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 4)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //------------------------------------------------------------------------------------------------------------------------------------------3
                    while (board[count_yoko, count_tate] != 9)
                    {
                        count_yoko--;
                        if (up_count == 0 && (board[count_yoko, count_tate] == -1 || board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 4))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 4)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //------------------------------------------------------------------------------------------------------------------------------------------4
                    while (board[count_yoko, count_tate] != 9)
                    {
                        count_tate++;
                        count_yoko--;
                        if (up_count == 0 && (board[count_yoko, count_tate] == -1 || board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 4))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 4)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //------------------------------------------------------------------------------------------------------------------------------------------5
                    while (board[count_yoko, count_tate] != 9)
                    {
                        count_tate++;
                        if (up_count == 0 && (board[count_yoko, count_tate] == -1 || board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 4))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 4)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //----------------------------------------------------------------------------------------------------------------------------------------------6
                    while (board[count_yoko, count_tate] != 9)
                    {
                        count_yoko++;
                        count_tate++;
                        if (up_count == 0 && (board[count_yoko, count_tate] == -1 || board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 4))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 4)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //------------------------------------------------------------------------------------------------------------------------------------------------7
                    while (board[count_yoko, count_tate] != 9)
                    {
                        count_yoko++;
                        if (up_count == 0 && (board[count_yoko, count_tate] == -1 || board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 4))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 4)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
                        {
                            up_count++;
                        }
                    }
                    up_count = 0;
                    count_tate = temp_count_tate;
                    count_yoko = temp_count_yoko;
                    //--------------------------------------------------------------------------------------------------------------------------------------------------8
                    while (board[count_yoko, count_tate] != 9)
                    {
                        count_tate--;
                        count_yoko++;
                        if (up_count == 0 && (board[count_yoko, count_tate] == -1 || board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 4))   //１つ上のコマが黒or無なら終了
                        {
                            break;
                        }
                        else if (up_count > 0)
                        {
                            if (board[count_yoko, count_tate] == -1)                                                    //２つ以上、上のコマでどれかが黒なら
                            {
                                white_OK_sign = true;
                                break;
                            }
                            if (board[count_yoko, count_tate] == 0 || board[count_yoko, count_tate] == 4)
                            {
                                break;
                            }
                        }
                        else if (up_count == 0 && board[count_yoko, count_tate] == 1)                                  //１つ上のコマが白なら＋１する
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
                    //reverse_OK[temp_count_yoko, temp_count_tate] = 3;
                    board[count_yoko, count_tate] = 4;
                    if (effect[count_yoko, count_tate] == null)
                    {
                        effect[count_yoko, count_tate] = Instantiate(OK_image_effect);
                        effect[count_yoko, count_tate].transform.position = new Vector3((count_yoko - 4) * 1.05f - 0.5f, (4 - count_tate) * 1.05f - 4.55f, 4.5f);
                    }
                    white_OK_sign = false;
                }
                if (board[count_yoko, count_tate] != 4)
                {
                    Destroy(effect[count_yoko, count_tate]);
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
                if (board[i, j] == 4)
                {
                    //Debug.Log.Log("通ったらダメ");
                    pass_white_check = false;
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
                if (board[i, j] == 6)
                {
                    pass_black_check = false;
                }
            }
        }
    }

    public void Show_result()
    {
        for (int i = 1; i < 9; i++)
        {
            for (int j = 1; j < 9; j++)
            {
                ////Debug.Log.Log("i : " + i + " j : " + j + " board : " + board[i, j] + " i_count : " + i_count + " j_count : " + j_count + " reverse_ok_i : " + reverse_ok_i + " j : " + reverse_ok_j);
            }
        }
    }

    public void Black_Destroy(int i, int j)
    {
        //Debug.Log.Log("i : " + i + "j : " + j + "Destroy_black : " + piece_temp[i, j]);
        Destroy(piece_temp[i, j]);
    }

    public void Destroy_Prefab()
    {
        for (int i = 1; i < 9; i++)
        {
            for (int j = 1; j < 9; j++)
            {
                if (effect[i, j] != null)
                {
                    Destroy(effect[i, j]);
                }
            }
        }
    }

    public void Black_Initialize()
    {

        for (int i = 1; i < 9; i++)
        {
            for (int j = 1; j < 9; j++)
            {
                if (board[i, j] == 1)
                {
                    piece_temp[i, j] = Instantiate(piece_black, new Vector3(i - 4 - 0.5f, 4 - j - 4.5f, 4.9f), Quaternion.Euler(90.0f, 0f, 0f));
                }
            }
        }
    }

    public void Square_Position_Initialize()
    {
        //if (now_temp == null)
        //{
        ////    now_temp = Instantiate(now, new Vector3(-0.5f, -4.55f, 4.0f), Quaternion.Euler(0.0f, 0f, 0f));
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

    public void Reset_Black_OK()
    {
        for (int i = 1; i < 9; i++)
        {
            for (int j = 1; j < 9; j++)
            {
                if (board[i, j] == 6)
                {
                    board[i, j] = 0;
                }
            }
        }
        pass_black_check = true;
    }

    public override void AgentReset()
    {
        if (reset_count == 0)
        {
            reverse_ok_i = 4;
            reverse_ok_j = 4;
            ///*
            board = new int[,]
            {
                { 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, },
                { 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, },
                { 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, },
                { 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, },
                { 9, 0, 0, 0, 1,-1, 0, 0, 0, 9, },
                { 9, 0, 0, 0,-1, 1, 0, 0, 0, 9, },
                { 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, },
                { 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, },
                { 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, },
                { 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 }
            };
            //*/
            /*

            board = new int[,]
            {
                { 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, },
                { 9, 1, 1, 1, 1,-1, 1,-1, 0, 9, },
                { 9, 1,-1,-1, 1, 1, 1,-1,-1, 9, },
                { 9, 1, 1, 1, 1, 1, 1,-1, 1, 9, },
                { 9, 1,-1, 1,-1,-1, 1, 1, 1, 9, },
                { 9,-1, 1, 1, 1, 1,-1, 1, 1, 9, },
                { 9,-1, 1, 1, 1,-1,-1,-1, 1, 9, },
                { 9, 1, 1,-1,-1,-1, 1, 1, 1, 9, },
                { 9, 1, 1,-1, 1, 1, 1,-1,-1, 9, },
                { 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 }
            };
            */
        }
        if (reset_count > 0)
        {
            //Debug.Log.Log("２ボーイ");
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
                    if (board[i, j] == 1)
                    {
                        Black_Destroy(i, j);
                    }

                    if (board[i, j] == -1)
                    {
                        white.White_Destroy(i, j);
                    }

                    if ((i == 4 && j == 4) || (i == 5 && j == 5))
                    {
                        board[i, j] = 1;
                    }
                    else if ((i == 5 && j == 4) || (i == 4 && j == 5))
                    {
                        board[i, j] = -1;
                    }
                    else
                    {
                        board[i, j] = 0;
                    }
                }
            }
        }

        black_initialize = true;

        Square_Position_Initialize();

        turn_change = false;
        reset_count++;
        pass_white_check = true;

        white.white_initialize = true;

        white.Square_Position_Initialize();
        pass_black_check = true;

        black_find_flag = true;

        Find_Black_OK();

        turn_time = true;

        stop = false;

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

    public override void CollectObservations()
    {
        for (int i = 1; i < 9; i++)
        {
            for (int j = 1; j < 9; j++)
            {
                AddVectorObs(i);
                AddVectorObs(j);
                AddVectorObs(board[i, j]);
            }
        }
    }

    public override void AgentAction(float[] vectorAction, string textAction)
    {
        if (!stop)
        {
            StartCoroutine("OneSecond_stop");
        }

        if (black_initialize)
        {
            Black_Initialize();
            black_initialize = false;
        }
        if (black_find_flag)
        {
            Find_Black_OK();
            black_find_flag = false;
        }
        if (!turn_change && turn_time && stop)
        {
            Show_result();
            if (black_position_initialize)
            {
                Square_Position_Initialize();
                black_position_initialize = false;
            }
            /*
            if (Input.GetKeyUp(KeyCode.A) && i_count > 1)
            {
                now_temp.transform.position += new Vector3(-1.0f, 0.0f, 0.0f);
                i_count--;
            }
            if (Input.GetKeyUp(KeyCode.W) && j_count > 1)
            {
                now_temp.transform.position += new Vector3(0.0f, 1.0f, 0.0f);
                j_count--;
            }
            if (Input.GetKeyUp(KeyCode.S) && j_count < 8)
            {
                now_temp.transform.position += new Vector3(0.0f, -1.0f, 0.0f);
                j_count++;
            }
            if (Input.GetKeyUp(KeyCode.D) && i_count < 8)
            {
                now_temp.transform.position += new Vector3(1.0f, 0.0f, 0.0f);
                i_count++;
            }

            if (Input.GetKeyUp(KeyCode.Space))
            */
            ///*
            Reverse_OK_find();
            if (vectorAction[0] > -1 && vectorAction[0] < 0 && i_count > 0 && reset_now)
            {
                i_count = reverse_ok_i;
                j_count = reverse_ok_j;
                //Debug.Log.Log("押したよ");
                while (!(i_count == 1 && j_count == 8))
                {
                    //Debug.Log.Log("通過地点2 : i : " + i_count + " j " + j_count);
                    if (i_count == 1 && j_count != 8)
                    {
                        i_count = 9;
                        j_count++;
                        //trans_j++;
                    }
                    if (i_count != 1)
                    {
                        i_count--;
                    }
                    Show_result();
                    //trans_i++
                    if (reverse_OK[i_count, j_count])
                    {
                        //now_temp.transform.position = new Vector3(i_count - 4 - 0.5f, 4 - j_count - 4.55f, 4.0f);
                        reverse_ok_i = i_count;
                        reverse_ok_j = j_count;
                        Show_result();
                        break;
                    }
                    ////Debug.Log.Log(i_count + " : " + j_count + " reverse_ok_i : " + reverse_ok_i + " j : " + reverse_ok_j);

                }
                vectorAction[0] = 0;
            }
            
            if (vectorAction[0] < 1 && vectorAction[0] > 0 && i_count < 9 && reset_now)
            //if (Input.GetKeyUp(KeyCode.D) && i_count < 8)
            {
                i_count = reverse_ok_i;
                j_count = reverse_ok_j;
                //AddReward(10.0f);
                //Debug.Log.Log("押したよ");
                while (!(i_count == 8 && j_count == 1))
                {
                    //Show_result();
                    //Debug.Log.Log("通過地点2 : i : " + i_count + " j " + j_count);

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
                    ////Debug.Log.Log(i_count + " : " + j_count);
                    if (reverse_OK[i_count, j_count])
                    {
                        //Debug.Log.Log("通過地点3");
                        //now_temp.transform.position = new Vector3(i_count - 4 - 0.5f, 4 - j_count - 4.55f, 4.0f);
                        reverse_ok_i = i_count;
                        reverse_ok_j = j_count;
                        Show_result();
                        break;
                    }
                    ////Debug.Log.Log(i_count + " : " + j_count +  "main : " + board[i_count, j_count] + " reverse_ok_i : " + reverse_ok_i + " j : " + reverse_ok_j);
                    Show_result();
                }
                vectorAction[0] = 0;
            }

            /*
            if (vectorAction[1] < 1 && vectorAction[1] > 0 && j_count > 1)
            {
                //AddReward(10.0f);
                ////Debug.Log.Log("押したよ");
                now_temp.transform.position += new Vector3(0.0f, 1.0f, 0.0f);
                j_count--;
                vectorAction[1] = 0;
                AddReward(-0.01f);
            }
            if (vectorAction[1] > -1 && vectorAction[1] < 0 && j_count < 8)
            {
                //AddReward(10.0f);
                ////Debug.Log.Log("押したよ");
                now_temp.transform.position += new Vector3(0.0f, -1.0f, 0.0f);
                j_count++;
                vectorAction[1] = 0;
                AddReward(-0.01f);
            }
            */

            if (vectorAction[1] < 1 && vectorAction[1] > 0 && reset_now)
                //*/
            {
                i_count = reverse_ok_i;
                j_count = reverse_ok_j;
                Show_result();
                ////Debug.Log.Log("押したよ");
                //Show_result();
                if (board[i_count, j_count] == 6)
                {
                    audio.Play();
                    AddReward(1.0f);
                    //Debug.Log.Log("今だよ1");
                    Reset_Black_OK();
                    board[i_count, j_count] = 1;
                    change(i_count, j_count);
                    Effect_Appear();
                    Change_After_Black(i_count, j_count);
                    corner_reward();
                    turn_change = true;
                    Find_White_OK();//new
                    Search_White_pass();//new
                    if (pass_white_check)
                    {
                        //Debug.Log.Log("pass");
                        turn_change = false;
                        Find_Black_OK();
                        Search_Black_pass();
                        if (pass_black_check)
                        {
                            turn_time = false;
                            //Debug.Log.Log("今だよ2");
                            for (int i = 1; i < 9; i++)
                            {
                                for (int j = 1; j < 9; j++)
                                {
                                    if (board[i, j] == -1)
                                    {
                                        judge_white++;
                                    }
                                    if (board[i, j] == 1)
                                    {
                                        judge_black++;
                                    }
                                }
                            }
                            if (judge_white < judge_black)           //白の負け
                            {
                                lose.SetActive(true);
                                //Debug.Log.Log("Loser");
                                AddReward(10.0f);
                                //Done();
                            }
                            else if(judge_white == judge_black)
                            {
                                draw.SetActive(true);
                                //Debug.Log.Log("Draw");
                                //white.WhiteReward(10.0f);
                                //Done();
                            }
                            else
                            {
                                win.SetActive(true);
                                //Debug.Log("Winner");
                                //Done();
                            }

                            pass_black_check = false;
                            //StartCoroutine("Do");
                            StartCoroutine("transScene");
                        }
                    }
                    black_position_initialize = true;
                    Now_delete();
                    stop = false;
                }
                else
                {
                    AddReward(-0.1f);
                }
                vectorAction[1] = 0;
            }
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


    public void Now_delete()
    {
        //Destroy(now_temp);
    }

    public void corner_reward()
    {
        if (board[1, 1] == 1 || board[8, 1] == 1 || board[1, 8] == 1 || board[8, 8] == 1)
        {
            AddReward(3.0f);
        }

        if (board[1, 1] == -1 || board[8, 1] == -1 || board[1, 8] == -1 || board[8, 8] == -1)
        {
            AddReward(-3.0f);
        }
    }

    public void BlackReward(float temp)
    {
        AddReward(temp);
    }

    public void Reverse_OK_find()
    {
        for (int i = 1; i < 9; i++)
        {
            for (int j = 1; j < 9; j++)
            {
                if (board[i, j] == 6)
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

    IEnumerator OneSecond_stop()
    {
        yield return new WaitForSeconds(3.0f);
        stop = true;
    }

    public void OnDestroy()
    {
        Destroy(GameObject.Find("Music"));
    }

    public void Effect_Appear()
    {
        if (black_now == null)
        {
            black_now = Instantiate(black_now_effect, new Vector3(i_count - 4 - 0.5f, 4 - j_count - 4.55f, 4.0f), Quaternion.Euler(0.0f, 0f, 0f));
        }
        else
        {
            black_now.transform.position = new Vector3(i_count - 4 - 0.5f, 4 - j_count - 4.55f, 4.0f);
        }
    }
}
