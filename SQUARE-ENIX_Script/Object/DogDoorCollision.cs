using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DogDoorCollision : MonoBehaviour {

    public bool isTouched;

    // Use this for initialization
    void Start()
    {
        isTouched = false;
    }

    // Update is called once per frame
    void Update()
    {

    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Player")
        {
            isTouched = true;

        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.tag == "Player")
        {
            isTouched = false;

        }
    }
}
