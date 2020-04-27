using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//using Cinemachine;

public class FindSmell : MonoBehaviour
{

    private float shakeFrequency = 0.0f;
    private float SMELL_MAX_DISTANCE = 6.0f;
    private float SMELL_MIDDLE_DISTANCE = 4.0f;
    private float SMELL_NEAR_DISTANCE = 2.0f;

    RaycastHit hitInfo;
    //public CinemachineVirtualCamera vCam;

    // Use this for initialization
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        Search();
    }
    private void Search()
    {
        if (Physics.SphereCast(this.transform.position, 0.8f, this.transform.forward, out hitInfo, SMELL_MAX_DISTANCE))
        {
            if (hitInfo.collider.CompareTag("Smell"))
            {
                var sqrDistance = (transform.position - hitInfo.transform.position).sqrMagnitude;
                if (sqrDistance < SMELL_NEAR_DISTANCE * SMELL_NEAR_DISTANCE)
                {
                    shakeFrequency = 0.05f;
                    Debug.Log("near");
                }
                else if (sqrDistance < SMELL_MIDDLE_DISTANCE * SMELL_MIDDLE_DISTANCE)
                {
                    shakeFrequency = 0.03f;
                    Debug.Log("middle");
                }
                else if (sqrDistance < SMELL_MAX_DISTANCE * SMELL_MAX_DISTANCE)
                {
                    shakeFrequency = 0.02f;
                    Debug.Log("far");
                }
                else
                {
                    shakeFrequency = 0f;
                    Debug.Log("out1");
                }
            }
            else
            {
                shakeFrequency = 0f;
                Debug.Log("out2");
            }

        }
        else
        {
            shakeFrequency = 0.0f;
            Debug.Log("out3");
        }
        //vCam.GetCinemachineComponent<CinemachineBasicMultiChannelPerlin>().m_FrequencyGain = shakeFrequency;
    }
}