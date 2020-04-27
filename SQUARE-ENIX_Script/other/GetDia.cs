using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GetDia : MonoBehaviour
{
    public static bool diamond;
    public GameObject dia;
    public GameObject diaIcon;
    
    // Start is called before the first frame update
    void Start()
    {
        diamond = false;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Player") {
            diamond = true;
            dia.SetActive(false);
            diaIcon.SetActive(true);
        }
    }
}
