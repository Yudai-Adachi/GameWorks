using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CanvasManager : MonoBehaviour
{
    private GameObject player;
    public GameObject Canvas;
    public GameObject UI_DamageDog;
    public GameObject LifeBar1;
    public GameObject LifeBar2;
    public GameObject LifeBar3;
    public GameObject LifeBar4;
    public GameObject LifeBar5;
    public GameObject Mode;
    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player");
    }

    // Update is called once per frame
    void Update()
    {
        int hp = player.GetComponent<Player>().HP;
        if (hp< 5)
        {
            LifeBar1.SetActive(false);
        }
        if (hp < 4)
        {
            LifeBar2.SetActive(false);
        }
        if (hp < 3)
        {
            LifeBar3.SetActive(false);
        }
        if (hp < 2)
        {
            LifeBar4.SetActive(false);
        }
        if (hp < 1)
        {
            LifeBar5.SetActive(false);
            SceneManager.LoadScene("GameOver");
        }
        if (player.GetComponent<Player>().isSmelling) {
            Mode.SetActive(true);
        }
        else
        {
            Mode.SetActive(false);
        }
    }
}
