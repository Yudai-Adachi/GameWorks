using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DogDoorManager : MonoBehaviour {

    Transform doorCollision;
    Transform doorPivot;

	// Use this for initialization
	void Start () {
        doorCollision = this.transform.Find("DoorCollision");
        doorPivot = transform.Find("DoorPivot");
	}
	
	// Update is called once per frame
	void Update () {
        if(doorCollision.GetComponent<DogDoorCollision>().isTouched)
        {
            doorPivot.GetComponent<Rotation>().isOpened = true;

        }
        else
        {
            doorPivot.GetComponent<Rotation>().isOpened = false;
        }
	}
}
