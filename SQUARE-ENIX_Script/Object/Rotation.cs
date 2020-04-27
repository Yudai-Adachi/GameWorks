using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rotation : MonoBehaviour {

    Quaternion InitRot;
    float rotationStep;
    float doorRotation;
    public bool isOpened;

	// Use this for initialization
	void Start () {
        InitRot = this.transform.rotation;
        doorRotation = 0.0f;
        rotationStep = 30.0f;
        isOpened = false;
	}

    // Update is called once per frame
    void Update() {
        if (isOpened)
        {
            if (doorRotation < 90.0f)
            {
                this.transform.Rotate(-rotationStep * Time.deltaTime, 0.0f, 0.0f);
                doorRotation += rotationStep * Time.deltaTime;
            }
        }
        else
        {
            if (doorRotation > 0.0f) {
                this.transform.Rotate(rotationStep * Time.deltaTime, 0.0f, 0.0f);
                doorRotation -= rotationStep * Time.deltaTime;
            }
        }

        
	}
}
