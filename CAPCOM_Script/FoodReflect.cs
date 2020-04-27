using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FoodReflect : MonoBehaviour
{
    public float m_reflectPower = 1.0f;
    private Rigidbody m_rigidbody;

    void Start()
    {
        m_rigidbody = GetComponent<Rigidbody>();
    }

    public void OnCollisionEnter(Collision collision)
    {
        //反射ベクトルを計算
        Vector3 reflectVec = Vector3.Reflect(m_rigidbody.velocity, collision.contacts[0].normal);
        m_rigidbody.velocity = reflectVec * m_reflectPower;
        if(collision.gameObject.tag == "Player")
        {
            GetComponent<FoodReflect>().enabled = false;
        }
    }

}
