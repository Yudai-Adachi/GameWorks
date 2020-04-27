using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FoodHansya : MonoBehaviour
{
    private Rigidbody m_rigidbody;

    void Start()
    {
        m_rigidbody = GetComponent<Rigidbody>();
    }

    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.CompareTag("Plate"))
        {
            m_rigidbody.velocity = collision.contacts[0].normal * m_rigidbody.velocity.magnitude;
            m_rigidbody.useGravity = false;
        }
        else
        {
           if(m_rigidbody==null)
            {
                return;
            }
            m_rigidbody.useGravity = true;
        }
    }

}
