using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraScript : MonoBehaviour
{
    private const float angle_y_min = -98.0f;
    private const float angle_y_max = 98.0f;

    public Transform target;
    public Vector3 offset;
    private Vector3 lookAt;

    public float distance = 5.0f;
    private float current_x = 0.0f;
    private float current_y = 0.0f;

    private GameObject player;

    void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player");
    }

    void Update()
    {
        if (player.GetComponent<Player>().isSmelling)
        {
            GetComponent<PostEffect>().enabled = true;
        }
        else
        {
            GetComponent<PostEffect>().enabled = false;
        }

        if (Input.GetKey(KeyCode.L))
        {
            current_x +=  0.6f;
        }

        if (Input.GetKey(KeyCode.J))
        {
            current_x -= 0.6f;
        }
        if (Input.GetKey(KeyCode.I))
        {
            current_y += 0.6f;
        }

        if (Input.GetKey(KeyCode.M))
        {
            current_y -= 0.6f;
        }

        current_y = Mathf.Clamp(current_y, angle_y_min, angle_y_max);
    }

    void LateUpdate()
    {
        if(target != null)
        {
            lookAt = target.position + offset;
            Vector3 dir = new Vector3(0, 0, -distance);
            Quaternion rotation = Quaternion.Euler(-current_y,current_x + 180,0);

            transform.position = lookAt + rotation * dir;
            transform.LookAt(lookAt);




        }
    }
}