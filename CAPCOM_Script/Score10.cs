using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Score10 : MonoBehaviour
{
    [SerializeField] float maxComboTime = 5.0f;
    [SerializeField] GameObject launcher;
    [SerializeField] int phase1 = 200;
    [SerializeField] int phase2 = 400;
    [SerializeField] int phase3 = 800;

    public Text CountDown;

    public Text TotalScore;
    public Text Conbo;

    public static int conbo;


    public GameObject food1;
    public int currentScore = 0;

    GameObject food1_temp;

    float currentTime = 0.0f;

    public static int Score;

    public GameObject frame1;
    public GameObject frame2;
    public GameObject frame3;
    public GameObject frame4;

    Rigidbody rb;

    bool p1 = true;
    bool p2 = true;
    bool p3 = true;

    Launcher m_launcher;

    // Start is called before the first frame update
    void Start()
    {
        p1 = true;
        p2 = true;
        p3 = true;

        currentScore = 0;
        currentTime = 0.0f;

        Score = 0;
        rb = food1.GetComponent<Rigidbody>();
        food1_temp = Instantiate(food1, new Vector3(-24.59924f, -0.3272538f, -1.1f), Quaternion.identity);
        food1_temp.GetComponent<MeshCollider>().enabled = false;
        rb.useGravity = false;
        conbo = 0;

        food1_temp.transform.localScale = new Vector3(30, 30, 30);
        food1_temp.transform.rotation = Quaternion.AngleAxis(-90.0f, Vector3.forward);

        m_launcher = launcher.GetComponent<Launcher>();
    }

    // Update is called once per frame
    void Update()
    {
        CountDown.text = Manager.MainGameManager.Instance.GetTimeToInt().ToString();

        currentTime += Time.deltaTime;
        if(currentTime>=maxComboTime)
        {
            conbo = 0;
            currentTime = 0.0f;
        }
        Conbo.text = conbo.ToString();
        if(currentScore<Score)
        {
            currentScore++;
        }
        TotalScore.text = currentScore.ToString();

        // do things when socre is bigger than some value
        if(p1&&Score > phase1)
        {
            StartCoroutine(Phase1());
        }
        if (p2 && Score >phase2)
        {
            StartCoroutine(Phase2());
        }
        if (p3 && Score >phase3)
        {
            StartCoroutine(Phase3());
        }
    }

    public void OnTriggerEnter(Collider other)
    {
        conbo++;
        if (other.gameObject.name == "Pizza Variant(Clone)")
        {
            Score += 10;
        }

        if (conbo < 5)
        {
            Score += 10;
        }

        if (conbo >= 5 && conbo < 10)
        {
            Score += 12;
        }

        if(conbo >= 10)
        {
            Score += 15;
        }

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

    IEnumerator Phase1()
    {
        m_launcher.SetPadding(20);
        m_launcher.SetRotSpd(10);
        m_launcher.SetLaunchTime(40);

        yield return new WaitForSeconds(8f);

        m_launcher.SetPadding(0);
        m_launcher.SetRotSpd(10);
        p1 = false;
    }

    IEnumerator Phase2()
    {
        m_launcher.SetLaunchTime(2);


        yield return new WaitForSeconds(8f);

        
        p2 = false;
    }

    IEnumerator Phase3()
    {
        m_launcher.SetLaunchTime(1);
        m_launcher.SetPadding(20);
        m_launcher.SetRotSpd(10);

        yield return new WaitForSeconds(8f);

        m_launcher.SetPadding(0);
        m_launcher.SetRotSpd(10);
        m_launcher.SetLaunchTime(40);

        p3 = false;

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
